#include "productlist.h"
#include "product.h"

ProductList::ProductList()
{
}

ProductList::~ProductList()
{
    for (int i = 0; i < m_productList.length(); ++i) {
        delete m_productList[i];
    }
}

void ProductList::addProduct (Product* p)
{
    m_productList.push_back(p);
}

void ProductList::deleteProduct (int idx)
{
    delete m_productList[idx];
    m_productList.removeAt(idx);
}

Product* ProductList::getProduct (int idx)
{
    return m_productList[idx];
}

const Product* ProductList::getProduct (int idx) const
{
    return m_productList[idx];
}

int ProductList::getProductNum () const
{
    return m_productList.length();
}

float ProductList::getTotalPriceIn () const
{
    float total = 0.0f;
    for (int i = 0; i < m_productList.length(); ++i) {
        total += m_productList[i]->getTotalPriceIn();
    }
    return total;
}

float ProductList::getTotalPriceOut () const
{
    float total = 0.0f;
    for (int i = 0; i < m_productList.length(); ++i) {
        total += m_productList[i]->getTotalPriceOut();
    }
    return total;
}

float ProductList::getTotalMWeight () const
{
    float total = 0.0f;
    for (int i = 0; i < m_productList.length(); ++i) {
        total += m_productList[i]->getTotalMWeight();
    }
    return total;
}

float ProductList::getTotalVolume () const
{
    float total = 0.0f;
    for (int i = 0; i < m_productList.length(); ++i) {
        total += m_productList[i]->getTotalVolume();
    }
    return total;
}

int ProductList::getTotalPakNumber () const
{
    int total = 0;
    for (int i = 0; i < m_productList.length(); ++i) {
        total += m_productList[i]->getPakNumber();
    }
    return total;
}

int ProductList::getTotalProductNumber () const
{
    int total = 0;
    for (int i = 0; i < m_productList.length(); ++i) {
        total += m_productList[i]->getNumber();
    }
    return total;
}

float ProductList::getTotalTTax () const
{
    float total = 0.0f;
    for (int i = 0; i < m_productList.length(); ++i) {
        Product* p = m_productList[i];
        total += p->getTotalPriceIn() * (p->tTax() + p->xTax()) / 100.0f / (1.0f + p->zTax());
    }
    return total;
}
