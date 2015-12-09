#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product ();
    ~Product();

    int getNumber () const;
    void setNumber (int number);

    float getPriceIn () const;
    void setPriceIn (float priceIn);

    float getPriceOut () const;
    void setPriceOut (float priceOut);

    QString getName () const;
    void setName (const QString& name);

    int getPakUnit () const;
    void setPakUnit (int pakUnit);

    float getMWeight () const;
    void setMWeight (float mWeight);

    float getJWeight () const;
    void setJWeight (float jWeight);

    float getVolume () const;
    void setVolume (float volume);

    float zTax() const;
    void setZTax(float zTax);

    float xTax() const;
    void setXTax(float xTax);

    float tTax() const;
    void setTTax(float tTax);

    float getTotalPriceIn () const;
    float getTotalPriceOut () const;
    float getTotalMWeight () const;
    float getTotalJWeight () const;
    float getTotalVolume () const;
    int getPakNumber () const;

private:
    int         m_number;
    float       m_priceIn;
    float       m_priceOut;

    QString     m_name;
    int         m_pakUnit;
    float       m_mWeight;
    float       m_jWeight;
    float       m_volume;

    float       m_zTax;
    float       m_xTax;
    float       m_tTax;
};

#endif // PRODUCT_H
