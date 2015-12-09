#include "productdialog.h"
#include "ui_productdialog.h"
#include "product.h"

ProductDialog::ProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductDialog)
{
    ui->setupUi(this);
}

ProductDialog::~ProductDialog()
{
    delete ui;
}

void ProductDialog::initProductDialog (const Product* p)
{
    ui->name->setText(p->getName());

    ui->pakUnit->setValue(p->getPakUnit());
    ui->mWeight->setValue(p->getMWeight());
    ui->jWeight->setValue(p->getJWeight());
    ui->volume->setValue(p->getVolume());

    ui->number->setValue(p->getNumber());
    ui->priceIn->setValue(p->getPriceIn());
    ui->priceOut->setValue(p->getPriceOut());

    ui->zTax->setValue(p->zTax());
    ui->xTax->setValue(p->xTax());
    ui->tTax->setValue(p->tTax());
}

void ProductDialog::okProductDialog (Product* p)
{
    p->setName(ui->name->text());

    p->setPakUnit(ui->pakUnit->value());
    p->setMWeight(ui->mWeight->value());
    p->setJWeight(ui->jWeight->value());
    p->setVolume(ui->volume->value());

    p->setNumber(ui->number->value());
    p->setPriceIn(ui->priceIn->value());
    p->setPriceOut(ui->priceOut->value());

    p->setZTax(ui->zTax->value());
    p->setXTax(ui->xTax->value());
    p->setTTax(ui->tTax->value());
}
