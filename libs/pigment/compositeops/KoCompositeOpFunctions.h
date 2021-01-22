/*
 *  Copyright (c) 2011 Silvio Heinrich <plassy@web.de>
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

#ifndef KOCOMPOSITEOP_FUNCTIONS_H_
#define KOCOMPOSITEOP_FUNCTIONS_H_

#include <KoColorSpaceMaths.h>

template<class HSXType, class TReal>
inline void cfReorientedNormalMapCombine(TReal srcR, TReal srcG, TReal srcB, TReal& dstR, TReal& dstG, TReal& dstB)
{
    // see http://blog.selfshadow.com/publications/blending-in-detail/ by Barre-Brisebois and Hill
    TReal tx = 2*srcR-1;
    TReal ty = 2*srcG-1;
    TReal tz = 2*srcB;
    TReal ux = -2*dstR+1;
    TReal uy = -2*dstG+1;
    TReal uz = 2*dstB-1;
    TReal k = (tx*ux+ty*uy+tz*uz)/tz; // dot(t,u)/t.z
    TReal rx = tx*k-ux;
    TReal ry = ty*k-uy;
    TReal rz = tz*k-uz;
    k = 1/sqrt(rx*rx+ry*ry+rz*rz); // normalize result
    rx *= k;
    ry *= k;
    rz *= k;
    dstR = rx*0.5+0.5;
    dstG = ry*0.5+0.5;
    dstB = rz*0.5+0.5;
}

template<class HSXType, class TReal>
inline void cfColor(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    TReal lum = getLightness<HSXType>(dr, dg, db);
    dr = sr;
    dg = sg;
    db = sb;
    setLightness<HSXType>(dr, dg, db, lum);
}

template<class HSXType, class TReal>
inline void cfLightness(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    setLightness<HSXType>(dr, dg, db, getLightness<HSXType>(sr, sg, sb));
}

template<class HSXType, class TReal>
inline void cfIncreaseLightness(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    addLightness<HSXType>(dr, dg, db, getLightness<HSXType>(sr, sg, sb));
}

template<class HSXType, class TReal>
inline void cfDecreaseLightness(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    addLightness<HSXType>(dr, dg, db, getLightness<HSXType>(sr, sg, sb) - TReal(1.0));
}

template<class HSXType, class TReal>
inline void cfSaturation(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    TReal sat   = getSaturation<HSXType>(sr, sg, sb);
    TReal light = getLightness<HSXType>(dr, dg, db);
    setSaturation<HSXType>(dr, dg, db, sat);
    setLightness<HSXType>(dr, dg, db, light);
}

template<class HSXType, class TReal>
inline void cfIncreaseSaturation(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    using namespace Arithmetic;
    TReal sat   = lerp(getSaturation<HSXType>(dr,dg,db), unitValue<TReal>(), getSaturation<HSXType>(sr,sg,sb));
    TReal light = getLightness<HSXType>(dr, dg, db);
    setSaturation<HSXType>(dr, dg, db, sat);
    setLightness<HSXType>(dr, dg, db, light);
}

template<class HSXType, class TReal>
inline void cfDecreaseSaturation(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    using namespace Arithmetic;
    TReal sat   = lerp(zeroValue<TReal>(), getSaturation<HSXType>(dr,dg,db), getSaturation<HSXType>(sr,sg,sb));
    TReal light = getLightness<HSXType>(dr, dg, db);
    setSaturation<HSXType>(dr, dg, db, sat);
    setLightness<HSXType>(dr, dg, db, light);
}

template<class HSXType, class TReal>
inline void cfHue(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    TReal sat = getSaturation<HSXType>(dr, dg, db);
    TReal lum = getLightness<HSXType>(dr, dg, db);
    dr = sr;
    dg = sg;
    db = sb;
    setSaturation<HSXType>(dr, dg, db, sat);
    setLightness<HSXType>(dr, dg, db, lum);
}

template<class HSXType, class TReal>
inline void cfTangentNormalmap(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    using namespace Arithmetic;
    TReal half=halfValue<TReal>();
    
    dr = sr+(dr-half);
    dg = sg+(dg-half);
    db = sb+(db-unitValue<TReal>());
} 
    
template<class HSXType, class TReal>
inline void cfDarkerColor(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    
    TReal lum = getLightness<HSXType>(dr, dg, db);
    TReal lum2 = getLightness<HSXType>(sr, sg, sb);
    if (lum<lum2) {
        sr = dr;
        sg = dg;
        sb = db;
    }
    else {
        dr = sr;
        dg = sg;
        db = sb;
    }

}

template<class HSXType, class TReal>
inline void cfLighterColor(TReal sr, TReal sg, TReal sb, TReal& dr, TReal& dg, TReal& db) {
    
    TReal lum = getLightness<HSXType>(dr, dg, db);
    TReal lum2 = getLightness<HSXType>(sr, sg, sb);
    if (lum>lum2) {
        sr = dr;
        sg = dg;
        sb = db;
    }
    else {
        dr = sr;
        dg = sg;
        db = sb;
    }
}

template<class T>
inline T cfColorBurn(T src, T dst) {
    using namespace Arithmetic;
    
    if(dst == unitValue<T>())
        return unitValue<T>();
    
    T invDst = inv(dst);
    
    if(src < invDst)
        return zeroValue<T>();
    
    return inv(clamp<T>(div(invDst, src)));
}

template<class T>
inline T cfLinearBurn(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    return clamp<T>(composite_type(src) + dst - unitValue<T>());
}

template<class T>
inline T cfColorDodge(T src, T dst) {
    using namespace Arithmetic;
    
    if(dst == zeroValue<T>())
        return zeroValue<T>();
    
    T invSrc = inv(src);
    
    if(invSrc < dst)
        return unitValue<T>();
    
    return Arithmetic::clamp<T>(div(dst, invSrc));
}

template<class T>
inline T cfAddition(T src, T dst) {
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    return Arithmetic::clamp<T>(composite_type(src) + dst);
}

template<class T>
inline T cfSubtract(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    return clamp<T>(composite_type(dst) - src);
}

template<class T>
inline T cfInverseSubtract(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    return clamp<T>(composite_type(dst) - inv(src));
}

template<class T>
inline T cfExclusion(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    
    composite_type x = mul(src, dst);
    return clamp<T>(composite_type(dst) + src - (x + x));
}

template<class T>
inline T cfDivide(T src, T dst) {
    using namespace Arithmetic;
    //typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    
    if(src == zeroValue<T>())
        return (dst == zeroValue<T>()) ? zeroValue<T>() : unitValue<T>();
    
    return clamp<T>(div(dst, src));
}

template<class T>
inline T cfHardLight(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    
    composite_type src2 = composite_type(src) + src;
    
    if(src > halfValue<T>()) {
        // screen(src*2.0 - 1.0, dst)
        src2 -= unitValue<T>();
        return T((src2+dst) - (src2*dst / unitValue<T>()));
    }
    
    // multiply(src*2.0, dst)
    return clamp<T>(src2*dst / unitValue<T>());
}

template<class T>
inline T cfSoftLightSvg(T src, T dst) {
    using namespace Arithmetic;

    qreal fsrc = scale<qreal>(src);
    qreal fdst = scale<qreal>(dst);

    if(fsrc > 0.5f) {
        qreal D = (fdst > 0.25f) ? sqrt(fdst) : ((16.0f*fdst - 12.0)*fdst + 4.0f)*fdst;
        return scale<T>(fdst + (2.0f*fsrc - 1.0f) * (D - fdst));
    }

    return scale<T>(fdst - (1.0f - 2.0f * fsrc) * fdst * (1.0f - fdst));
}


template<class T>
inline T cfSoftLight(T src, T dst) {
    using namespace Arithmetic;
    
    qreal fsrc = scale<qreal>(src);
    qreal fdst = scale<qreal>(dst);
    
    if(fsrc > 0.5f) {
        return scale<T>(fdst + (2.0f * fsrc - 1.0f) * (sqrt(fdst) - fdst));
    }
    
    return scale<T>(fdst - (1.0f - 2.0f*fsrc) * fdst * (1.0f - fdst));
}

template<class T>
inline T cfVividLight(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    
    if(src < halfValue<T>()) {
        if(src == zeroValue<T>())
            return (dst == unitValue<T>()) ? unitValue<T>() : zeroValue<T>();

        // min(1,max(0,1-(1-dst) / (2*src)))
        composite_type src2 = composite_type(src) + src;
        composite_type dsti = inv(dst);
        return clamp<T>(unitValue<T>() - (dsti * unitValue<T>() / src2));
    }
    
    if(src == unitValue<T>())
        return (dst == zeroValue<T>()) ? zeroValue<T>() : unitValue<T>();
    
    // min(1,max(0, dst / (2*(1-src)))
    composite_type srci2 = inv(src);
    srci2 += srci2;
    return clamp<T>(composite_type(dst) * unitValue<T>() / srci2);
}

template<class T>
inline T cfPinLight(T src, T dst) {
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    // TODO: verify that the formula is correct (the first max would be useless here)
    // max(0, max(2*src-1, min(dst, 2*src)))
    composite_type src2 = composite_type(src) + src;
    composite_type a    = qMin<composite_type>(dst, src2);
    composite_type b    = qMax<composite_type>(src2-Arithmetic::unitValue<T>(), a);
    return T(b);
}

template<class T>
inline T cfArcTangent(T src, T dst) {
    using namespace Arithmetic;
    
    if(dst == zeroValue<T>())
        return (src == zeroValue<T>()) ? zeroValue<T>() : unitValue<T>();
    
    return scale<T>(2.0 * atan(scale<qreal>(src) / scale<qreal>(dst)) / Arithmetic::pi);
}

template<class T>
inline T cfAllanon(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    // (dst + src) / 2   [or (dst + src) * 0.5]
    return T((composite_type(src) + dst) * halfValue<T>() / unitValue<T>());
}

template<class T>
inline T cfLinearLight(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    
    // min(1,max(0,(dst + 2*src)-1))
    return clamp<T>((composite_type(src) + src + dst) - unitValue<T>());
}

template<class T>
inline T cfParallel(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    
    // min(max(2 / (1/dst + 1/src), 0), 1)
    composite_type unit = unitValue<T>();
    composite_type s    = (src != zeroValue<T>()) ? div<T>(unit, src) : unit;
    composite_type d    = (dst != zeroValue<T>()) ? div<T>(unit, dst) : unit;
    return clamp<T>((unit+unit) * unit / (d+s));
}

template<class T>
inline T cfEquivalence(T src, T dst) {
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    // 1 - abs(dst - src)
    composite_type x = composite_type(dst) - src;
    return (x < Arithmetic::zeroValue<T>()) ? T(-x) : T(x);
}

template<class T>
inline T cfGrainMerge(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    return clamp<T>(composite_type(dst) + src - halfValue<T>());
}

template<class T>
inline T cfGrainExtract(T src, T dst) {
    using namespace Arithmetic;
    typedef typename KoColorSpaceMathsTraits<T>::compositetype composite_type;
    return clamp<T>(composite_type(dst) - src + halfValue<T>());
}

template<class T>
inline T cfHardMix(T src, T dst) {
    return (dst > Arithmetic::halfValue<T>()) ? cfColorDodge(src,dst) : cfColorBurn(src,dst);
}

template<class T>
inline T cfAdditiveSubtractive(T src, T dst) {
    using namespace Arithmetic;
    // min(1,max(0,abs(sqr(CB)-sqr(CT))))
    qreal x = sqrt(scale<qreal>(dst)) - sqrt(scale<qreal>(src));
    return scale<T>((x < 0.0) ? -x : x);
}

template<class T>
inline T cfGammaDark(T src, T dst) {
    using namespace Arithmetic;
    
    if(src == zeroValue<T>())
        return zeroValue<T>();
    
    // power(dst, 1/src)
    return scale<T>(pow(scale<qreal>(dst), 1.0/scale<qreal>(src)));
}

template<class T>
inline T cfGammaLight(T src, T dst) {
    using namespace Arithmetic;
    return scale<T>(pow(scale<qreal>(dst), scale<qreal>(src)));
}

template<class T>
inline T cfGeometricMean(T src, T dst) {
    using namespace Arithmetic;
    return scale<T>(sqrt(scale<qreal>(dst) * scale<qreal>(src)));
}

template<class T>
inline T cfOver(T src, T dst) { Q_UNUSED(dst); return src; }

template<class T>
inline T cfOverlay(T src, T dst) { return cfHardLight(dst, src); }

template<class T>
inline T cfMultiply(T src, T dst) { return Arithmetic::mul(src, dst); }

template<class T>
inline T cfDifference(T src, T dst) { return qMax(src,dst) - qMin(src,dst); }

template<class T>
inline T cfScreen(T src, T dst) { return Arithmetic::unionShapeOpacity(src, dst); }

template<class T>
inline T cfDarkenOnly(T src, T dst) { return qMin(src, dst); }

template<class T>
inline T cfLightenOnly(T src, T dst) { return qMax(src, dst); }

#endif // KOCOMPOSITEOP_FUNCTIONS_H_
