#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QObject>

class Product : public QObject
{
    friend QDataStream& operator >> (QDataStream&, Product&);
    friend QDataStream& operator << (QDataStream&, Product&);

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

    QString id() const;
    void setId(const QString &id);

    QString nameEn() const;
    void setNameEn(const QString &nameEn);

    QString type() const;
    void setType(const QString &type);

    QString haiguan() const;
    void setHaiguan(const QString &haiguan);

    QString birth() const;
    void setBirth(const QString &birth);

    QString pc() const;
    void setPc(const QString &pc);

    QString carton() const;
    void setCarton(const QString &carton);

    QString descZh() const;
    void setDescZh(const QString &descZh);

    QString descEn() const;
    void setDescEn(const QString &descEn);

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

	QString		m_id;
	QString     m_nameEn;
	QString		m_type;
	QString     m_haiguan;
	QString		m_birth;
	QString     m_pc;
	QString     m_carton;
	QString     m_descZh;
	QString     m_descEn;
};

#endif // PRODUCT_H
