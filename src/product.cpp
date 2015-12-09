#include "product.h"
#include <math.h>
#include <QString>

Product::Product()
{
    m_number = 0;
    m_priceIn = .0f;
    m_priceOut = .0f;
    m_pakUnit = 0;
    m_mWeight = .0f;
    m_jWeight = .0f;
    m_volume = .0f;
    m_zTax = 17.0f;
    m_xTax = .0f;
    m_tTax = .0f;
}

Product::~Product()
{
}

int Product::getNumber () const
{
    return m_number;
}

void Product::setNumber (int number)
{
    m_number = number;
}

float Product::getPriceIn () const
{
    return m_priceIn;
}

void Product::setPriceIn (float priceIn)
{
    m_priceIn = priceIn;
}

float Product::getPriceOut () const
{
    return m_priceOut;
}

void Product::setPriceOut (float priceOut)
{
    m_priceOut = priceOut;
}

QString Product::getName () const
{
    return m_name;
}

void Product::setName (const QString& name)
{
    m_name = name;
}

int Product::getPakUnit () const
{
    return m_pakUnit;
}

void Product::setPakUnit (int pakUnit)
{
    m_pakUnit = pakUnit;
}

float Product::getMWeight () const
{
    return m_mWeight;
}

void Product::setMWeight (float mWeight)
{
    m_mWeight = mWeight;
}

float Product::getJWeight () const
{
    return m_jWeight;
}

void Product::setJWeight (float jWeight)
{
    m_jWeight = jWeight;
}

float Product::getVolume () const
{
    return m_volume;
}

void Product::setVolume (float volume)
{
    m_volume = volume;
}

float Product::getTotalPriceIn () const
{
    return m_priceIn * m_number;
}

float Product::getTotalPriceOut () const
{
    return m_priceOut * m_number;
}

float Product::getTotalMWeight () const
{
    if (m_pakUnit == 0)
        return .0f;
    return m_mWeight * m_number / m_pakUnit;
}

float Product::getTotalJWeight () const
{
    if (m_pakUnit == 0)
        return .0f;
    return m_jWeight * m_number / m_pakUnit;
}

float Product::getTotalVolume () const
{
    return m_volume * getPakNumber();
}

int Product::getPakNumber () const
{
    if (m_pakUnit == 0)
        return 0;
    return (int)ceil((float)m_number / (float)m_pakUnit);
}
float Product::zTax() const
{
    return m_zTax;
}

void Product::setZTax(float zTax)
{
    m_zTax = zTax;
}
float Product::xTax() const
{
    return m_xTax;
}

void Product::setXTax(float xTax)
{
    m_xTax = xTax;
}
float Product::tTax() const
{
    return m_tTax;
}

void Product::setTTax(float tTax)
{
    m_tTax = tTax;
}



