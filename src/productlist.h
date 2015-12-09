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
    float getTotalVolume () const;
    int getTotalPakNumber () const;
    int getTotalProductNumber () const;
    float getTotalTTax () const;
private:
    QVector<Product*> m_productList;
};

#endif // PRODUCTLIST_H
