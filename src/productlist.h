#ifndef PRODUCTLIST_H
#define PRODUCTLIST_H

#include <QVector>

class Product;
class ProductList
{
public:
    ProductList();
    ~ProductList();

    void addProduct (Product* p);
    void deleteProduct (int idx);
    Product* getProduct (int idx);
    const Product* getProduct (int idx) const;

    int getProductNum () const;

    float getTotalPriceIn () const;
    float getTotalPriceOut () const;
    float getTotalMWeight () const;
    float getTotalJWeight () const;
    float getTotalVolume () const;
    int getTotalPakNumber () const;
    int getTotalProductNumber () const;
    float getTotalTTax () const;

    QString getProductPakType () const;
    QString getProductQuantityType () const;
    QString getProductBigType () const;
    QString getPakInfoEn () const;
    QString getProductNameEn () const;
private:
    QVector<Product*> m_productList;
};

#endif // PRODUCTLIST_H
