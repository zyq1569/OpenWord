/*
 *  Copyright (c) 2005 Bart Coppens <kde@bartcoppens.be>
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _Ko_BASIC_HISTOGRAM_PRODUCERS_
#define _Ko_BASIC_HISTOGRAM_PRODUCERS_

#include "KoHistogramProducer.h"

#include <QVector>

#include <KoConfig.h>

#include "KoColorSpace.h"
#include "KoID.h"
#include "pigment_export.h"
#include "KoColorSpaceRegistry.h"

class PIGMENTCMS_EXPORT KoBasicHistogramProducer : public KoHistogramProducer
{
public:
    explicit KoBasicHistogramProducer(const KoID& id, int channelCount, int nrOfBins);
    explicit KoBasicHistogramProducer(const KoID& id, int nrOfBins, const KoColorSpace *colorSpace);
    ~KoBasicHistogramProducer() override {}

    void clear() override;

    void setView(qreal from, qreal size) override {
        m_from = from; m_width = size;
    }

    const KoID& id() const override {
        return m_id;
    }
    QList<KoChannelInfo *> channels() override {
        return m_colorSpace->channels();
    }
    qint32 numberOfBins() override {
        return m_nrOfBins;
    }
    qreal viewFrom() const override {
        return m_from;
    }
    qreal viewWidth() const override {
        return m_width;
    }

    qint32 count() override {
        return m_count;
    }

    qint32 getBinAt(int channel, int position) override {
        return m_bins.at(externalToInternal(channel)).at(position);
    }

    qint32 outOfViewLeft(int channel) override {
        return m_outLeft.at(externalToInternal(channel));
    }

    qint32 outOfViewRight(int channel) override {
        return m_outRight.at(externalToInternal(channel));
    }

protected:
    /**
     * The order in which channels() returns is not the same as the internal representation,
     * that of the pixel internally. This method converts external usage to internal usage.
     * This method uses some basic assumptions about the layout of the pixel, so _extremely_
     * exotic spaces might want to override this (see makeExternalToInternal source for
     * those assumptions)
     **/
    virtual int externalToInternal(int ext) {
        if (channels().count() > 0 && m_external.count() == 0) // Set up the translation table
            makeExternalToInternal();
        return m_external.at(ext);
    }
    // not virtual since that is useless: we call it from constructor
    void makeExternalToInternal();
    typedef QVector<quint32> vBins;
    QVector<vBins> m_bins;
    vBins m_outLeft, m_outRight;
    qreal m_from, m_width;
    qint32 m_count;
    int m_channels, m_nrOfBins;
    const KoColorSpace *m_colorSpace;
    KoID m_id;
    QVector<qint32> m_external;
};

class PIGMENTCMS_EXPORT KoBasicU8HistogramProducer : public KoBasicHistogramProducer
{
public:
    KoBasicU8HistogramProducer(const KoID& id, const KoColorSpace *colorSpace);
    void addRegionToBin(const quint8 * pixels, const quint8 * selectionMask, quint32 nPixels, const KoColorSpace *colorSpace) override;
    QString positionToString(qreal pos) const override;
    qreal maximalZoom() const override {
        return 1.0;
    }
};

class PIGMENTCMS_EXPORT KoBasicU16HistogramProducer : public KoBasicHistogramProducer
{
public:
    KoBasicU16HistogramProducer(const KoID& id, const KoColorSpace *colorSpace);
    void addRegionToBin(const quint8 * pixels, const quint8 * selectionMask, quint32 nPixels, const KoColorSpace *colorSpace) override;
    QString positionToString(qreal pos) const override;
    qreal maximalZoom() const override;
};

class PIGMENTCMS_EXPORT KoBasicF32HistogramProducer : public KoBasicHistogramProducer
{
public:
    KoBasicF32HistogramProducer(const KoID& id, const KoColorSpace *colorSpace);
    void addRegionToBin(const quint8 * pixels, const quint8 * selectionMask, quint32 nPixels, const KoColorSpace *colorSpace) override;
    QString positionToString(qreal pos) const override;
    qreal maximalZoom() const override;
};


#ifdef HAVE_OPENEXR
class PIGMENTCMS_EXPORT KoBasicF16HalfHistogramProducer : public KoBasicHistogramProducer
{
public:
    KoBasicF16HalfHistogramProducer(const KoID& id, const KoColorSpace *colorSpace);
    virtual void addRegionToBin(const quint8 * pixels, const quint8 * selectionMask, quint32 nPixels, const KoColorSpace *colorSpace);
    virtual QString positionToString(qreal pos) const;
    virtual qreal maximalZoom() const;
};
#endif

/**
 * Parametrized on a specific KoHistogramProducer. Its generated producers
 * will have the same KoID as the factory's. This is acceptable because we can't mix
 * Factories with Producers in the code because they are incompatible types, and
 * in the GUI we actually only need a producer's name, not a factory's.
 */
template<class T> class KoBasicHistogramProducerFactory : public KoHistogramProducerFactory
{
public:
    KoBasicHistogramProducerFactory(const KoID& id, const QString& modelId, const QString& depthId )
            : KoHistogramProducerFactory(id), m_modelId(modelId), m_depthId(depthId) {
    }
    ~KoBasicHistogramProducerFactory() override {}

    KoHistogramProducer *generate() override {
        KoHistogramProducer *producer = 0;
        const KoColorSpace *cs = KoColorSpaceRegistry::instance()->colorSpace(m_modelId, m_depthId, 0);
        if (cs) {
            producer = new T(KoID(id(), name()), cs);
        }
        return producer;

    }
    bool isCompatibleWith(const KoColorSpace* colorSpace) const override {
        return colorSpace->colorModelId().id() == m_modelId || colorSpace->colorDepthId().id() == m_depthId;
    }
    float preferrednessLevelWith(const KoColorSpace* colorSpace) const override {
        return 0.5 * ( (colorSpace->colorModelId().id() == m_modelId) + (colorSpace->colorDepthId().id() == m_depthId) );
    }
protected:
    QString m_modelId, m_depthId;
};

/**
 * This is a Producer (with associated factory) that converts the pixels of the colorspace
 * to RGB8 with toQColor, and then does its counting on RGB. This is NOT registered with the
 * Registry, because it isCompatibleWith all colorspaces, and should only be used in extreme
 * cases (like no other producer being available
 **/
class PIGMENTCMS_EXPORT KoGenericRGBHistogramProducer : public KoBasicHistogramProducer
{
public:
    KoGenericRGBHistogramProducer();
    void addRegionToBin(const quint8 * pixels, const quint8 * selectionMask, quint32 nPixels, const KoColorSpace *colorSpace) override;
    QString positionToString(qreal pos) const override;
    qreal maximalZoom() const override;
    QList<KoChannelInfo *> channels() override;
protected:
    QList<KoChannelInfo *> m_channelsList;
};

/** KoGenericRGBHistogramProducer his special Factory that isCompatibleWith everything. */
class  PIGMENTCMS_EXPORT KoGenericRGBHistogramProducerFactory : public KoHistogramProducerFactory
{
public:
    KoGenericRGBHistogramProducerFactory();

    ~KoGenericRGBHistogramProducerFactory() override {}

    KoHistogramProducer *generate() override {
        return new KoGenericRGBHistogramProducer();
    }

    bool isCompatibleWith(const KoColorSpace*) const override {
        return true;
    }

    float preferrednessLevelWith(const KoColorSpace*) const override {
        return 0.0;
    }
};


/**
 * This is a Producer (with associated factory) that converts the pixels of the colorspace
 * to L*a*b*, and then does its counting.
 * It isCompatibleWith all colorspaces
 **/
class  PIGMENTCMS_EXPORT KoGenericLabHistogramProducer : public KoBasicHistogramProducer
{
public:
    KoGenericLabHistogramProducer();
    ~KoGenericLabHistogramProducer() override;
    void addRegionToBin(const quint8 * pixels, const quint8 * selectionMask, quint32 nPixels, const KoColorSpace *colorSpace) override;
    QString positionToString(qreal pos) const override;
    qreal maximalZoom() const override;
    QList<KoChannelInfo *> channels() override;
protected:
    QList<KoChannelInfo *> m_channelsList;
};

/** KoGenericLabHistogramProducer his special Factory that isCompatibleWith everything. */
class /*PIGMENTCMS_EXPORT*/ KoGenericLabHistogramProducerFactory : public KoHistogramProducerFactory
{
public:
    KoGenericLabHistogramProducerFactory();
    ~KoGenericLabHistogramProducerFactory() override {}

    KoHistogramProducer *generate() override {
        return new KoGenericLabHistogramProducer();
    }

    bool isCompatibleWith(const KoColorSpace*) const override {
        return true;
    }

    float preferrednessLevelWith(const KoColorSpace*) const override {
        return 0.0;
    }
};


#endif // _Ko_BASIC_HISTOGRAM_PRODUCERS_
