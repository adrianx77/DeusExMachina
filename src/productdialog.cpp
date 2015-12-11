#include "productdialog.h"
#include "ui_productdialog.h"
#include "product.h"

#define UI_TEXT(name)           ui->name->text()
#define UI_VALUE(name)          ui->name->value()
#define UI_CHECKED(name)        ui->name->isChecked()

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
    if (!p)
        return;
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

	ui->id->setText(p->id());
	ui->nameEn->setText(p->nameEn());
	ui->type->setText(p->type());
	ui->haiguan->setText(p->haiguan());
	ui->birth->setText(p->birth());
	ui->pc->setText(p->pc());
	ui->carton->setText(p->carton());
	ui->descZh->setText(p->descZh());
	ui->descEn->setText(p->descEn());
}

void ProductDialog::okProductDialog (Product* p)
{
    if (!p)
        return;
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
	
	p->setId(UI_TEXT(id));
	p->setNameEn(UI_TEXT(nameEn));
	p->setType(UI_TEXT(type));
	p->setHaiguan(UI_TEXT(haiguan));
	p->setBirth(UI_TEXT(birth));
	p->setPc(UI_TEXT(pc));
	p->setCarton(UI_TEXT(carton));
    p->setDescZh(ui->descZh->toPlainText());
    p->setDescEn(ui->descEn->toPlainText());
}
