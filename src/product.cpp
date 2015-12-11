#include "product.h"
#include <math.h>
#include <QString>

Product::Product()
{
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
QString Product::id() const
{
    return m_id;
}

void Product::setId(const QString &id)
{
    m_id = id;
}
QString Product::nameEn() const
{
    return m_nameEn;
}

void Product::setNameEn(const QString &nameEn)
{
    m_nameEn = nameEn;
}
QString Product::type() const
{
    return m_type;
}

void Product::setType(const QString &type)
{
    m_type = type;
}
QString Product::haiguan() const
{
    return m_haiguan;
}

void Product::setHaiguan(const QString &haiguan)
{
    m_haiguan = haiguan;
}
QString Product::birth() const
{
    return m_birth;
}

void Product::setBirth(const QString &birth)
{
    m_birth = birth;
}
QString Product::pc() const
{
    return m_pc;
}

void Product::setPc(const QString &pc)
{
    m_pc = pc;
}
QString Product::carton() const
{
    return m_carton;
}

void Product::setCarton(const QString &carton)
{
    m_carton = carton;
}
QString Product::descZh() const
{
    return m_descZh;
}

void Product::setDescZh(const QString &descZh)
{
    m_descZh = descZh;
}
QString Product::descEn() const
{
    return m_descEn;
}

void Product::setDescEn(const QString &descEn)
{
    m_descEn = descEn;
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



