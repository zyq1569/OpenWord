/*
 *  Copyright (c) 2005 Boudewijn Rempt <boud@valdyas.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#include "KoColorSpace.h"
#include "KoColorSpace_p.h"

#include "KoChannelInfo.h"
#include "DebugPigment.h"
#include "KoCompositeOp.h"
#include "KoColorTransformation.h"
#include "KoColorTransformationFactory.h"
#include "KoColorTransformationFactoryRegistry.h"
#include "KoColorConversionCache.h"
#include "KoColorConversionSystem.h"
#include "KoColorSpaceRegistry.h"
#include "KoColorProfile.h"
#include "KoCopyColorConversionTransformation.h"
#include "KoFallBackColorTransformation.h"
#include "KoUniqueNumberForIdServer.h"
#include "KoMixColorsOp.h"
#include "KoConvolutionOp.h"
#include "KoCompositeOpRegistry.h"

#include <QThreadStorage>
#include <QByteArray>
#include <QBitArray>
#include <QPolygonF>
#include <QPointF>

#include <math.h>

KoColorSpace::KoColorSpace()
    : d(new Private())
{
}

KoColorSpace::KoColorSpace(const QString &id, const QString &name, KoMixColorsOp* mixColorsOp, KoConvolutionOp* convolutionOp)
    : d(new Private())
{
    d->id = id;
    d->idNumber = KoUniqueNumberForIdServer::instance()->numberForId(d->id);
    d->name = name;
    d->mixColorsOp = mixColorsOp;
    d->convolutionOp = convolutionOp;
    d->transfoToRGBA16 = 0;
    d->transfoFromRGBA16 = 0;
    d->transfoToLABA16 = 0;
    d->transfoFromLABA16 = 0;
    d->gamutXYY = QPolygonF();
    d->TRCXYY = QPolygonF();
    d->colorants = QVector <qreal> (0);
    d->lumaCoefficients = QVector <qreal> (0);
    d->deletability = NotOwnedByRegistry;
}

KoColorSpace::~KoColorSpace()
{
    Q_ASSERT(d->deletability != OwnedByRegistryDoNotDelete);

    qDeleteAll(d->compositeOps);
    foreach(KoChannelInfo * channel, d->channels)
    {
        delete channel;
    }
    if (d->deletability == NotOwnedByRegistry)
    {
        KoColorConversionCache* cache = KoColorSpaceRegistry::instance()->colorConversionCache();
        if (cache)
        {
            cache->colorSpaceIsDestroyed(this);
        }
    }
    delete d->mixColorsOp;
    delete d->convolutionOp;
    delete d->transfoToRGBA16;
    delete d->transfoFromRGBA16;
    delete d->transfoToLABA16;
    delete d->transfoFromLABA16;
    delete d;
}

bool KoColorSpace::operator==(const KoColorSpace& rhs) const
{
    const KoColorProfile* p1 = rhs.profile();
    const KoColorProfile* p2 = profile();
    return d->idNumber == rhs.d->idNumber && ((p1 == p2) || (*p1 == *p2));
}

QString KoColorSpace::id() const
{
    return d->id;
}

QString KoColorSpace::name() const
{
    return d->name;
}

//Color space info stuff.
QPolygonF KoColorSpace::gamutXYY() const
{
    if (d->gamutXYY.empty())
    {
        //now, let's decide on the boundary. This is a bit tricky because icc profiles can be both matrix-shaper and cLUT at once if the maker so pleases.
        //first make a list of colors.
        qreal max = 1.0;
        if ((colorModelId().id()=="CMYKA" || colorModelId().id()=="LABA") && colorDepthId().id()=="F32")
        {
            //boundaries for cmyka/laba have trouble getting the max values for Float, and are pretty awkward in general.
            max = this->channels().at(0)->getUIMax();

        }
        int samples = 5;//amount of samples in our color space.
        QString name = KoColorSpaceRegistry::instance()->colorSpaceFactory("XYZAF32")->defaultProfile();
        const KoColorSpace* xyzColorSpace = KoColorSpaceRegistry::instance()->colorSpace("XYZA", "F32", name);
        quint8 *data = new quint8[pixelSize()];
        quint8 data2[16]; // xyza f32 is 4 floats, that is 16 bytes per pixel.
        //QVector <qreal> sampleCoordinates(pow(colorChannelCount(),samples));
        //sampleCoordinates.fill(0.0);

        // This is fixed to 5 since the maximum number of channels are 5 for CMYKA
        QVector <qreal> channelValues(5);//for getting the coordinates.

        for(int x=0; x<samples; x++)
        {
            if (colorChannelCount()==1)  //gray
            {
                channelValues[0]=(max/(samples-1))*(x);
                channelValues[1]=max;
                fromNormalisedChannelsValue(data, channelValues);
                convertPixelsTo(data, data2, xyzColorSpace, 1, KoColorConversionTransformation::IntentAbsoluteColorimetric, KoColorConversionTransformation::adjustmentConversionFlags());
                xyzColorSpace->normalisedChannelsValue(data2, channelValues);
                qreal x = channelValues[0]/(channelValues[0]+channelValues[1]+channelValues[2]);
                qreal y = channelValues[1]/(channelValues[0]+channelValues[1]+channelValues[2]);
                d->gamutXYY << QPointF(x,y);
            }
            else
            {
                for(int y=0; y<samples; y++)
                {
                    for(int z=0; z<samples; z++)
                    {
                        if (colorChannelCount()==4)
                        {
                            for(int k=0; k<samples; k++)
                            {
                                channelValues[0] = (max / (samples - 1)) * (x);
                                channelValues[1] = (max / (samples - 1)) * (y);
                                channelValues[2] = (max / (samples - 1)) * (z);
                                channelValues[3] = (max / (samples - 1)) * (k);
                                channelValues[4] = max;
                                fromNormalisedChannelsValue(data, channelValues);
                                convertPixelsTo(data, data2, xyzColorSpace, 1, KoColorConversionTransformation::IntentAbsoluteColorimetric, KoColorConversionTransformation::adjustmentConversionFlags());
                                xyzColorSpace->normalisedChannelsValue(data2, channelValues);
                                qreal x = channelValues[0] / (channelValues[0] + channelValues[1] + channelValues[2]);
                                qreal y = channelValues[1] / (channelValues[0] + channelValues[1] + channelValues[2]);
                                d->gamutXYY<< QPointF(x,y);
                            }
                        }
                        else
                        {
                            channelValues[0]=(max/(samples-1))*(x);
                            channelValues[1]=(max/(samples-1))*(y);
                            channelValues[2]=(max/(samples-1))*(z);
                            channelValues[3]=max;
                            if (colorModelId().id()!="XYZA")   //no need for conversion when using xyz.
                            {
                                fromNormalisedChannelsValue(data, channelValues);
                                convertPixelsTo(data, data2, xyzColorSpace, 1, KoColorConversionTransformation::IntentAbsoluteColorimetric,         KoColorConversionTransformation::adjustmentConversionFlags());
                                xyzColorSpace->normalisedChannelsValue(data2,channelValues);
                            }
                            qreal x = channelValues[0]/(channelValues[0]+channelValues[1]+channelValues[2]);
                            qreal y = channelValues[1]/(channelValues[0]+channelValues[1]+channelValues[2]);
                            d->gamutXYY<< QPointF(x,y);
                        }
                    }
                }

            }
        }
        delete[] data;
        //if we ever implement a boundary-checking thing I'd add it here.
        return d->gamutXYY;
    }
    else
    {
        return d->gamutXYY;
    }
}

QPolygonF KoColorSpace::estimatedTRCXYY() const
{
    if (d->TRCXYY.empty())
    {
        qreal max = 1.0;
        if ((colorModelId().id()=="CMYKA" || colorModelId().id()=="LABA") && colorDepthId().id()=="F32")
        {
            //boundaries for cmyka/laba have trouble getting the max values for Float, and are pretty awkward in general.
            max = this->channels().at(0)->getUIMax();
        }
        QString name = KoColorSpaceRegistry::instance()->colorSpaceFactory("XYZAF16")->defaultProfile();
        const KoColorSpace* xyzColorSpace = KoColorSpaceRegistry::instance()->colorSpace("XYZA", "F16", name);
        quint8 *data = new quint8[pixelSize()];
        quint8 data2[8]; // xyza is 8 bytes per pixel.

        // This is fixed to 5 since the maximum number of channels are 5 for CMYKA
        QVector <qreal> channelValues(5);//for getting the coordinates.

        for (quint32 i=0; i<colorChannelCount(); i++)
        {
            qreal colorantY=1.0;
            if (colorModelId().id()!="CMYKA")
            {
                for (int j=5; j>0; j--)
                {
                    channelValues.fill(0.0);
                    channelValues[i] = ((max/4)*(5-j));

                    if (colorModelId().id()!="XYZA")   //no need for conversion when using xyz.
                    {
                        fromNormalisedChannelsValue(data, channelValues);
                        convertPixelsTo(data, data2, xyzColorSpace, 1, KoColorConversionTransformation::IntentAbsoluteColorimetric,         KoColorConversionTransformation::adjustmentConversionFlags());
                        xyzColorSpace->normalisedChannelsValue(data2,channelValues);
                    }

                    if (j==0)
                    {
                        colorantY = channelValues[1];
                        if (d->colorants.size()<2)
                        {
                            d->colorants.resize(3*colorChannelCount());
                            d->colorants[i]  = channelValues[0]/(channelValues[0]+channelValues[1]+channelValues[2]);
                            d->colorants[i+1]= channelValues[1]/(channelValues[0]+channelValues[1]+channelValues[2]);
                            d->colorants[i+2]= channelValues[1];
                        }
                    }
                    d->TRCXYY << QPointF(channelValues[1]/colorantY, ((1.0/4)*(5-j)));
                }
            }
            else
            {
                for (int j=0; j<5; j++)
                {
                    channelValues.fill(0.0);
                    channelValues[i] = ((max/4)*(j));

                    fromNormalisedChannelsValue(data, channelValues);

                    convertPixelsTo(data, data2, xyzColorSpace, 1, KoColorConversionTransformation::IntentAbsoluteColorimetric,         KoColorConversionTransformation::adjustmentConversionFlags());

                    xyzColorSpace->normalisedChannelsValue(data2,channelValues);

                    if (j==0)
                    {
                        colorantY = channelValues[1];
                        if (d->colorants.size()<2)
                        {
                            d->colorants.resize(3*colorChannelCount());
                            d->colorants[i]  = channelValues[0]/(channelValues[0]+channelValues[1]+channelValues[2]);
                            d->colorants[i+1]= channelValues[1]/(channelValues[0]+channelValues[1]+channelValues[2]);
                            d->colorants[i+2]= channelValues[1];
                        }
                    }
                    d->TRCXYY << QPointF(channelValues[1]/colorantY, ((1.0/4)*(j)));
                }
            }
        }

        delete[] data;
        return d->TRCXYY;
    }
    else
    {
        return d->TRCXYY;
    }
}

QVector <qreal> KoColorSpace::colorants() const
{
    if (d->colorants.size()>1)
    {
        return d->colorants;
    }
    else if (profile() && profile()->hasColorants())
    {
        d->colorants.resize(3*colorChannelCount());
        d->colorants = profile()->getColorantsxyY();
        return d->colorants;
    }
    else
    {
        estimatedTRCXYY();
        return d->colorants;
    }
}
QVector <qreal> KoColorSpace::lumaCoefficients() const
{
    if (d->lumaCoefficients.size()>1)
    {
        return d->lumaCoefficients;
    }
    else
    {
        d->lumaCoefficients.resize(3);
        if (colorModelId().id()!="RGBA")
        {
            d->lumaCoefficients.fill(0.33);
        }
        else
        {
            colorants();
            if (d->colorants[2]<0 || d->colorants[5]<0 || d->colorants[8]<0)
            {
                d->lumaCoefficients[0]=0.2126;
                d->lumaCoefficients[1]=0.7152;
                d->lumaCoefficients[2]=0.0722;
            }
            else
            {
                d->lumaCoefficients[0]=d->colorants[2];
                d->lumaCoefficients[1]=d->colorants[5];
                d->lumaCoefficients[2]=d->colorants[8];
            }
        }
        return d->lumaCoefficients;
    }
}

QList<KoChannelInfo *> KoColorSpace::channels() const
{
    return d->channels;
}

QBitArray KoColorSpace::channelFlags(bool color, bool alpha) const
{
    QBitArray ba(d->channels.size());
    if (!color && !alpha)
    {
        return ba;
    }

    for (int i = 0; i < d->channels.size(); ++i)
    {
        KoChannelInfo * channel = d->channels.at(i);
        if ((color && channel->channelType() == KoChannelInfo::COLOR) ||
                (alpha && channel->channelType() == KoChannelInfo::ALPHA))
        {
            ba.setBit(i, true);
        }
    }
    return ba;
}

void KoColorSpace::addChannel(KoChannelInfo * ci)
{
    d->channels.push_back(ci);
}
bool KoColorSpace::hasCompositeOp(const QString& id) const
{
    return d->compositeOps.contains(id);
}

QList<KoCompositeOp*> KoColorSpace::compositeOps() const
{
    return d->compositeOps.values();
}

KoMixColorsOp* KoColorSpace::mixColorsOp() const
{
    return d->mixColorsOp;
}


KoConvolutionOp* KoColorSpace::convolutionOp() const
{
    return d->convolutionOp;
}

const KoCompositeOp * KoColorSpace::compositeOp(const QString & id) const
{
    const QHash<QString, KoCompositeOp*>::ConstIterator it = d->compositeOps.constFind(id);
    if (it != d->compositeOps.constEnd())
    {
        return it.value();
    }
    else
    {
        warnPigment << "Asking for non-existent composite operation " << id << ", returning " << COMPOSITE_OVER;
        return d->compositeOps.value(COMPOSITE_OVER);
    }
}

void KoColorSpace::addCompositeOp(const KoCompositeOp * op)
{
    if (op->colorSpace()->id() == id())
    {
        d->compositeOps.insert(op->id(), const_cast<KoCompositeOp*>(op));
    }
}

const KoColorConversionTransformation* KoColorSpace::toLabA16Converter() const
{
    if (!d->transfoToLABA16)
    {
        d->transfoToLABA16 = KoColorSpaceRegistry::instance()->colorConversionSystem()->createColorConverter(this, KoColorSpaceRegistry::instance()->lab16(""), KoColorConversionTransformation::internalRenderingIntent(), KoColorConversionTransformation::internalConversionFlags()) ;
    }
    return d->transfoToLABA16;
}

const KoColorConversionTransformation* KoColorSpace::fromLabA16Converter() const
{
    if (!d->transfoFromLABA16)
    {
        d->transfoFromLABA16 = KoColorSpaceRegistry::instance()->colorConversionSystem()->createColorConverter(KoColorSpaceRegistry::instance()->lab16(""), this, KoColorConversionTransformation::internalRenderingIntent(), KoColorConversionTransformation::internalConversionFlags()) ;
    }
    return d->transfoFromLABA16;
}
const KoColorConversionTransformation* KoColorSpace::toRgbA16Converter() const
{
    if (!d->transfoToRGBA16)
    {
        d->transfoToRGBA16 = KoColorSpaceRegistry::instance()->colorConversionSystem()->createColorConverter(this, KoColorSpaceRegistry::instance()->rgb16(""), KoColorConversionTransformation::internalRenderingIntent(), KoColorConversionTransformation::internalConversionFlags()) ;
    }
    return d->transfoToRGBA16;
}
const KoColorConversionTransformation* KoColorSpace::fromRgbA16Converter() const
{
    if (!d->transfoFromRGBA16)
    {
        d->transfoFromRGBA16 = KoColorSpaceRegistry::instance()->colorConversionSystem()->createColorConverter(KoColorSpaceRegistry::instance()->rgb16(""), this, KoColorConversionTransformation::internalRenderingIntent(), KoColorConversionTransformation::internalConversionFlags()) ;
    }
    return d->transfoFromRGBA16;
}

void KoColorSpace::toLabA16(const quint8 * src, quint8 * dst, quint32 nPixels) const
{
    toLabA16Converter()->transform(src, dst, nPixels);
}

void KoColorSpace::fromLabA16(const quint8 * src, quint8 * dst, quint32 nPixels) const
{
    fromLabA16Converter()->transform(src, dst, nPixels);
}

void KoColorSpace::toRgbA16(const quint8 * src, quint8 * dst, quint32 nPixels) const
{
    toRgbA16Converter()->transform(src, dst, nPixels);
}

void KoColorSpace::fromRgbA16(const quint8 * src, quint8 * dst, quint32 nPixels) const
{
    fromRgbA16Converter()->transform(src, dst, nPixels);
}

KoColorConversionTransformation* KoColorSpace::createColorConverter(const KoColorSpace * dstColorSpace, KoColorConversionTransformation::Intent renderingIntent, KoColorConversionTransformation::ConversionFlags conversionFlags) const
{
    if (*this == *dstColorSpace)
    {
        return new KoCopyColorConversionTransformation(this);
    }
    else
    {
        return KoColorSpaceRegistry::instance()->colorConversionSystem()->createColorConverter(this, dstColorSpace, renderingIntent, conversionFlags);
    }
}

bool KoColorSpace::convertPixelsTo(const quint8 * src,
                                   quint8 * dst,
                                   const KoColorSpace * dstColorSpace,
                                   quint32 numPixels,
                                   KoColorConversionTransformation::Intent renderingIntent,
                                   KoColorConversionTransformation::ConversionFlags conversionFlags) const
{
    if (*this == *dstColorSpace)
    {
        if (src != dst)
        {
            memcpy(dst, src, numPixels * sizeof(quint8) * pixelSize());
        }
    }
    else
    {
        KoCachedColorConversionTransformation cct = KoColorSpaceRegistry::instance()->colorConversionCache()->cachedConverter(this, dstColorSpace, renderingIntent, conversionFlags);
        cct.transformation()->transform(src, dst, numPixels);
    }
    return true;
}


void KoColorSpace::bitBlt(const KoColorSpace* srcSpace, const KoCompositeOp::ParameterInfo& params, const KoCompositeOp* op,
                          KoColorConversionTransformation::Intent renderingIntent,
                          KoColorConversionTransformation::ConversionFlags conversionFlags) const
{
    Q_ASSERT_X(*op->colorSpace() == *this, "KoColorSpace::bitBlt", QString("Composite op is for color space %1 (%2) while this is %3 (%4)").arg(op->colorSpace()->id()).arg(op->colorSpace()->profile()->name()).arg(id()).arg(profile()->name()).toLatin1());

    if(params.rows <= 0 || params.cols <= 0)
    {
        return;
    }

    if(!(*this == *srcSpace))
    {
        if (preferCompositionInSourceColorSpace() &&
                srcSpace->hasCompositeOp(op->id()))
        {

            quint32           conversionDstBufferStride = params.cols * srcSpace->pixelSize();
            QVector<quint8> * conversionDstCache        = threadLocalConversionCache(params.rows * conversionDstBufferStride);
            quint8*           conversionDstData         = conversionDstCache->data();

            for(qint32 row=0; row<params.rows; row++)
            {
                convertPixelsTo(params.dstRowStart + row * params.dstRowStride,
                                conversionDstData  + row * conversionDstBufferStride, srcSpace, params.cols,
                                renderingIntent, conversionFlags);
            }

            // FIXME: do not calculate the otherOp every time
            const KoCompositeOp *otherOp = srcSpace->compositeOp(op->id());

            KoCompositeOp::ParameterInfo paramInfo(params);
            paramInfo.dstRowStart  = conversionDstData;
            paramInfo.dstRowStride = conversionDstBufferStride;
            otherOp->composite(paramInfo);

            for(qint32 row=0; row<params.rows; row++)
            {
                srcSpace->convertPixelsTo(conversionDstData  + row * conversionDstBufferStride,
                                          params.dstRowStart + row * params.dstRowStride, this, params.cols,
                                          renderingIntent, conversionFlags);
            }

        }
        else
        {
            quint32           conversionBufferStride = params.cols * pixelSize();
            QVector<quint8> * conversionCache        = threadLocalConversionCache(params.rows * conversionBufferStride);
            quint8*           conversionData         = conversionCache->data();

            for(qint32 row=0; row<params.rows; row++)
            {
                srcSpace->convertPixelsTo(params.srcRowStart + row * params.srcRowStride,
                                          conversionData     + row * conversionBufferStride, this, params.cols,
                                          renderingIntent, conversionFlags);
            }

            KoCompositeOp::ParameterInfo paramInfo(params);
            paramInfo.srcRowStart  = conversionData;
            paramInfo.srcRowStride = conversionBufferStride;
            op->composite(paramInfo);
        }
    }
    else
    {
        op->composite(params);
    }
}


QVector<quint8> * KoColorSpace::threadLocalConversionCache(quint32 size) const
{
    QVector<quint8> * ba = 0;
    if (!d->conversionCache.hasLocalData())
    {
        ba = new QVector<quint8>(size, '0');
        d->conversionCache.setLocalData(ba);
    }
    else
    {
        ba = d->conversionCache.localData();
        if ((quint8)ba->size() < size)
        {
            ba->resize(size);
        }
    }
    return ba;
}

KoColorTransformation* KoColorSpace::createColorTransformation(const QString & id, const QHash<QString, QVariant> & parameters) const
{
    KoColorTransformationFactory* factory = KoColorTransformationFactoryRegistry::instance()->get(id);
    if (!factory)
    {
        return 0;
    }
    QPair<KoID, KoID> model(colorModelId(), colorDepthId());
    QList< QPair<KoID, KoID> > models = factory->supportedModels();
    if (models.isEmpty() || models.contains(model))
    {
        return factory->createTransformation(this, parameters);
    }
    else
    {
        // Find the best solution
        // TODO use the color conversion cache
        KoColorConversionTransformation* csToFallBack = 0;
        KoColorConversionTransformation* fallBackToCs = 0;
        KoColorSpaceRegistry::instance()->colorConversionSystem()->createColorConverters(this, models, csToFallBack, fallBackToCs);
        Q_ASSERT(csToFallBack);
        Q_ASSERT(fallBackToCs);
        KoColorTransformation* transfo = factory->createTransformation(fallBackToCs->srcColorSpace(), parameters);
        return new KoFallBackColorTransformation(csToFallBack, fallBackToCs, transfo);
    }
}

void KoColorSpace::increaseLuminosity(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    if (profile()->hasTRC())
    {
        //only linearise and crunch the luma if there's a TRC
        profile()->linearizeFloatValue(channelValues);
        qreal hue, sat, luma = 0.0;
        toHSY(channelValues, &hue, &sat, &luma);
        luma = pow(luma, 1/2.2);
        luma = qMin<qreal>(1.0, luma + step);
        luma = pow(luma, 2.2);
        channelValues = fromHSY(&hue, &sat, &luma);
        profile()->delinearizeFloatValue(channelValues);
    }
    else
    {
        qreal hue, sat, luma = 0.0;
        toHSY(channelValues, &hue, &sat, &luma);
        luma = qMin<qreal>(1.0, luma + step);
        channelValues = fromHSY(&hue, &sat, &luma);
    }
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::decreaseLuminosity(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    if (profile()->hasTRC())
    {
        //only linearise and crunch the luma if there's a TRC
        profile()->linearizeFloatValue(channelValues);
        qreal hue, sat, luma = 0.0;
        toHSY(channelValues, &hue, &sat, &luma);
        luma = pow(luma, 1/2.2);
        if (luma-step<0.0)
        {
            luma=0.0;
        }
        else
        {
            luma -= step;
        }
        luma = pow(luma, 2.2);
        channelValues = fromHSY(&hue, &sat, &luma);
        profile()->delinearizeFloatValue(channelValues);
    }
    else
    {
        qreal hue, sat, luma = 0.0;
        toHSY(channelValues, &hue, &sat, &luma);
        if (luma-step<0.0)
        {
            luma=0.0;
        }
        else
        {
            luma -= step;
        }
        channelValues = fromHSY(&hue, &sat, &luma);
    }
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::increaseSaturation(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal hue, sat, luma = 0.0;
    toHSY(channelValues, &hue, &sat, &luma);
    sat += step;
    sat = qBound<qreal>(0.0, sat, 1.0);
    channelValues = fromHSY(&hue, &sat, &luma);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::decreaseSaturation(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal hue, sat, luma = 0.0;
    toHSY(channelValues, &hue, &sat, &luma);
    sat -= step;
    sat = qBound<qreal>(0.0, sat, 1.0);
    channelValues = fromHSY(&hue, &sat, &luma);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::increaseHue(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount(); //doesn't work for cmyka...
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal hue, sat, luma = 0.0;
    toHSY(channelValues, &hue, &sat, &luma);
    if (hue+step>1.0)
    {
        hue=(hue+step)- 1.0;
    }
    else
    {
        hue += step;
    }
    channelValues = fromHSY(&hue, &sat, &luma);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::decreaseHue(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal hue, sat, luma = 0.0;
    toHSY(channelValues, &hue, &sat, &luma);
    if (hue-step<0.0)
    {
        hue=1.0-(step-hue);
    }
    else
    {
        hue -= step;
    }
    channelValues = fromHSY(&hue, &sat, &luma);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}

void KoColorSpace::increaseRed(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal y, u, v = 0.0;
    toYUV(channelValues, &y, &u, &v);
    u += step;
    u = qBound<qreal>(0.0, u, 1.0);
    channelValues = fromYUV(&y, &u, &v);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::increaseGreen(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal y, u, v = 0.0;
    toYUV(channelValues, &y, &u, &v);
    u -= step;
    u = qBound<qreal>(0.0, u, 1.0);
    channelValues = fromYUV(&y, &u, &v);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::increaseBlue(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal y, u, v = 0.0;
    toYUV(channelValues, &y, &u, &v);
    v += step;
    v = qBound<qreal>(0.0, v, 1.0);
    channelValues = fromYUV(&y, &u, &v);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
void KoColorSpace::increaseYellow(quint8 * pixel, qreal step) const
{
    int channelnumber = channelCount();
    QVector <qreal> channelValues(channelnumber);
    normalisedChannelsValue(pixel, channelValues);
    profile()->linearizeFloatValue(channelValues);
    qreal y, u, v = 0.0;
    toYUV(channelValues, &y, &u, &v);
    v -= step;
    v = qBound<qreal>(0.0, v, 1.0);
    channelValues = fromYUV(&y, &u, &v);
    profile()->delinearizeFloatValue(channelValues);
    fromNormalisedChannelsValue(pixel, channelValues);
    setOpacity(pixel, qreal(1.0), 1);
}
QImage KoColorSpace::convertToQImage(const quint8 *data, qint32 width, qint32 height,
                                     const KoColorProfile *dstProfile,
                                     KoColorConversionTransformation::Intent renderingIntent,
                                     KoColorConversionTransformation::ConversionFlags conversionFlags) const

{
    QImage img = QImage(width, height, QImage::Format_ARGB32);

    const KoColorSpace * dstCS = KoColorSpaceRegistry::instance()->rgb8(dstProfile);

    if (data)
    {
        this->convertPixelsTo(const_cast<quint8 *>(data), img.bits(), dstCS, width * height, renderingIntent, conversionFlags);
    }

    return img;
}

bool KoColorSpace::preferCompositionInSourceColorSpace() const
{
    return false;
}
