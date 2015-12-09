#include "logicform.h"
#include "ui_logicform.h"
#include "productdialog.h"
#include "productlist.h"
#include "product.h"
#include "pronounceNum.h"
#include <QMessageBox>

LogicForm::LogicForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogicForm)
{
    ui->setupUi(this);
    m_productList = new ProductList();
}

LogicForm::~LogicForm()
{
    delete ui;
}

void LogicForm::refreshProductList ()
{
    ui->productList->clear();
    int number = m_productList->getProductNum();
    for (int i = 0; i < number; ++i)
    {
        Product* p = m_productList->getProduct(i);

        QTreeWidgetItem* pItem = new QTreeWidgetItem(ui->productList);
        pItem->setText(0, QString::number(i));
        pItem->setText(1, p->getName());
        pItem->setText(2, QString::number(p->getPakNumber()));
        pItem->setText(3, QString::number(p->getNumber()));
        pItem->setText(4, QString::number(p->getPriceIn(), 'f', 2));
        pItem->setText(5, QString::number(p->getPriceOut(), 'f', 2));
		
        pItem->setText(6, QString::number(p->zTax(), 'f', 2));
        pItem->setText(7, QString::number(p->xTax(), 'f', 2));
        pItem->setText(8, QString::number(p->tTax(), 'f', 2));
        pItem->setText(9, QString::number(p->getMWeight(), 'f', 2));
        pItem->setText(10, QString::number(p->getJWeight(), 'f', 2));
        pItem->setText(11, QString::number(p->getVolume(), 'f', 2));
		
        pItem->setText(12, QString::number(p->getTotalPriceIn(), 'f', 2));
        pItem->setText(13, QString::number(p->getTotalPriceOut(), 'f', 2));
        pItem->setText(14, QString::number(p->getTotalMWeight(), 'f', 2));
        pItem->setText(15, QString::number(p->getTotalVolume(), 'f', 2));
    }

    ui->totalPriceIn->setValue(m_productList->getTotalPriceIn());
    ui->totalPriceOut->setValue(m_productList->getTotalPriceOut());
    ui->totalMWeight->setValue(m_productList->getTotalMWeight());
    ui->totalVolume->setValue(m_productList->getTotalVolume());
    ui->totalPakNumber->setValue(m_productList->getTotalPakNumber());
    ui->totalProductNumber->setValue(m_productList->getTotalProductNumber());
    PronounceNum p;
    ui->totalPriceOutEn->setText(p.numToString(m_productList->getTotalPriceOut()).c_str());
    ui->totalPakNumberEn->setText(p.numToString(m_productList->getTotalPakNumber()).c_str());
}

float LogicForm::getCostCIF () const
{
    bool isFOBMode = ui->t0_0->isChecked();
    bool isCFRMode = ui->t0_1->isChecked();
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    float s = getRealShipCost();
    float b = getRealInsurance();
    if (isCFRMode) {
        c += b;
    } else if (isFOBMode) {
        c += s + b;
    }
    return c;
}

float LogicForm::getCostCFR () const
{
    bool isFOBMode = ui->t0_0->isChecked();
    bool isCIFMode = ui->t0_2->isChecked();
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    float s = getRealShipCost();
    float b = getRealInsurance();
    if (isFOBMode) {
        c += s;
    } else if (isCIFMode) {
        c -= b;
    }
    return c;
}

float LogicForm::getCostFOB () const
{
    bool isCFRMode = ui->t0_1->isChecked();
    bool isCIFMode = ui->t0_2->isChecked();
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    float s = getRealShipCost();
    float b = getRealInsurance();
    if (isCFRMode) {
        c -= s;
    } else if (isCIFMode) {
        c -= (s + b);
    }
    return c;
}

float LogicForm::getShipCost () const
{
    bool isShipP = ui->t4_0->isChecked();
    bool isShip20 = ui->t4_1->isChecked();
    bool isShip40 = ui->t4_2->isChecked();
    float shipCost = 999999999.99f;
    if (isShipP) {
        shipCost = getShipPCost();
    } else if (isShip20) {
        shipCost = getShip20Cost();
    } else if (isShip40) {
        shipCost = getShip40Cost();
    }
    return shipCost;
}

float LogicForm::getRealShipCost () const
{
    bool isFOBMode = ui->t0_0->isChecked();
    if (!isFOBMode) {
        return getShipCost();
    }
    return 0.0f;
}

float LogicForm::getShipPCost () const
{
    float vCost = m_productList->getTotalVolume() * ui->h5->value()* ui->h4->value();
    float wCost = m_productList->getTotalMWeight() * ui->h6->value()* ui->h4->value();
    return vCost > wCost ? vCost : wCost;
}

float LogicForm::getShip20Cost () const
{
    if (ship20Enable()) {
        return (ui->h7->value() + ui->h8->value() + ui->h9->value()) * ui->h4->value();
    }
    return 999999999.99f;
}

float LogicForm::getShip40Cost () const
{
    if (ship40Enable()) {
        return (ui->h10->value() + ui->h11->value() + ui->h12->value()) * ui->h4->value();
    }
    return 999999999.99f;
}

bool LogicForm::ship20Enable () const
{
    return !(m_productList->getTotalVolume() > ui->h0->value() || m_productList->getTotalMWeight() > ui->h1->value());
}

bool LogicForm::ship40Enable () const
{
    return !(m_productList->getTotalVolume() > ui->h2->value() || m_productList->getTotalMWeight() > ui->h3->value());
}

float LogicForm::getInsurance () const
{
    bool isFOBMode = ui->t0_0->isChecked();
    bool isCFRMode = ui->t0_1->isChecked();
    bool isCIFMode = ui->t0_2->isChecked();
    if (isCIFMode) {
        return getInsuranceCIF();
    } else if (isCFRMode) {
        return getInsuranceCFR();
    } else if (isFOBMode) {
        return getInsuranceFOB();
    }
    return 0.0f;
}

float LogicForm::getRealInsurance () const
{
    bool isCIFMode = ui->t0_2->isChecked();
    if (isCIFMode) {
        return getInsuranceCIF();
    } else {
        return 0.0f;
    }
}

float LogicForm::getInsuranceCIF () const
{
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    float a = (1.0f + ui->t5->value() / 100.0f);
    float b = ui->t6->value() / 100.0f;
    return c * a * b;
}

float LogicForm::getInsuranceCFR () const
{
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    float a = (1.0f + ui->t5->value() / 100.0f);
    float b = ui->t5->value() / 100.0f;
    return c * a / (1 - a * b) * b;
}

float LogicForm::getInsuranceFOB () const
{
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    float s = getShipCost();
    float a = (1.0f + ui->t5->value() / 100.0f);
    float b = ui->t5->value() / 100.0f;
    return (c + s) * a / (1 - a * b) * b;
}

float LogicForm::getBank () const
{
    bool isBankTT = ui->t6_0->isChecked();
    bool isBankLC = ui->t6_1->isChecked();
    bool isBankDP = ui->t6_2->isChecked();
    bool isBankDA = ui->t6_3->isChecked();

    if (isBankTT) {
        return 0.0f;
    } else if (isBankLC) {
        return getBankLC();
    } else if (isBankDP) {
        return getBankDP();
    } else if (isBankDA) {
        return getBankDA();
    }
    return 0.0f;
}

float LogicForm::getBankLC () const
{
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    c = c * ui->g15->value() / 100.0f;
    c = (c > ui->g16->value() ? c : ui->g16->value());
    return c + ui->g13->value() * ui->t7->value() + ui->g14->value() * ui->t8->value();
}

float LogicForm::getBankDP () const
{
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    c = ui->g17->value() / 100.0f;
    c = (c < ui->g18->value() ? ui->g18->value() : c);
    c = (c > ui->g19->value() ? ui->g19->value() : c);
    return c;
}

float LogicForm::getBankDA () const
{
    float c = m_productList->getTotalPriceOut() * ui->t3->value();
    c = ui->g17->value() / 100.0f;
    c = (c < ui->g18->value() ? ui->g18->value() : c);
    c = (c > ui->g19->value() ? ui->g19->value() : c);
    return c;
}

float LogicForm::getOtherCost () const
{
    float otherCost = 0.0f;
    otherCost += m_productList->getTotalPriceOut() * ui->t3->value() * ui->g12->value() / 100.0f;
    otherCost += ui->g9->value() * ui->t9->value();
    otherCost += ui->g3->value() * ui->g4->value() * ui->t10->value();
    return otherCost;
}

float LogicForm::getProfit () const
{
    float profit = 0.0f;
    profit += ui->t3->value() * m_productList->getTotalPriceOut();
    profit += m_productList->getTotalTTax();
    profit -= m_productList->getTotalPriceIn();
    profit -= ui->g7->value() * m_productList->getTotalVolume();
    profit -= ui->g8->value() * ui->t1->value();
    profit -= ui->g10->value() * ui->t2->value();
    profit -= ui->g11->value() * ui->t11->value();
    profit -= getRealShipCost();
    profit -= getRealInsurance();
    profit -= getBank();
    profit -= getOtherCost();
    return profit;
}

float LogicForm::getFinalProfit () const
{
    float profit = getProfit();
    profit -= ui->g5->value() * ui->t12->value();
    profit -= ui->g6->value() * ui->t13->value();
    profit -= ui->g0->value() * ui->t14->value() / 100.0f;
    if (ui->t15->value() > 0.0f) {
        float hk = ui->t15->value() * ui->g1->value() / 100.0f;
        hk = (hk > ui->g2->value() ? hk : ui->g2->value());
        profit -= hk;
    }
    profit -= ui->t16->value();
    return profit;
}

float LogicForm::getFinalProfitRate () const
{
    float finalProfit = getFinalProfit();
    float totalCost = 0.0f;
    totalCost += m_productList->getTotalPriceIn();
    totalCost += ui->g7->value() * m_productList->getTotalVolume();
    totalCost += ui->g8->value() * ui->t1->value();
    totalCost += ui->g10->value() * ui->t2->value();
    totalCost += ui->g11->value() * ui->t11->value();
    totalCost += getRealShipCost();
    totalCost += getRealInsurance();
    totalCost += getBank();
    totalCost += getOtherCost();
    totalCost += ui->g5->value() * ui->t12->value();
    totalCost += ui->g6->value() * ui->t13->value();
    totalCost += ui->g0->value() * ui->t14->value() / 100.0f;
    if (ui->t15->value() > 0.0f) {
        float hk = ui->t15->value() * ui->g1->value() / 100.0f;
        hk = (hk > ui->g2->value() ? hk : ui->g2->value());
        totalCost += hk;
    }
    totalCost += ui->t16->value();

    if (totalCost != 0.0f) {
        return finalProfit / totalCost * 100.0f;
    }
    return 0.0f;
}

QString LogicForm::getReport0Str () const
{
    float finalProfitRate = getFinalProfitRate();
    QString report0;
    if (finalProfitRate < 0.0f) {
        report0 = QString::fromWCharArray(L"亲，你是不是傻，这样做是赔钱的哦！/(ㄒoㄒ)/~~");
    } else if (finalProfitRate < 7.5f) {
        report0 = QString::fromWCharArray(L"亲，根据计算结果好像不怎么赚钱！╮(╯﹏╰）╭");
    } else if (finalProfitRate < 15.0f) {
        report0 = QString::fromWCharArray(L"亲，这笔买卖还不错，可以赚不少钱了！O(∩_∩)O~");
    } else {
        report0 = QString::fromWCharArray(L"亲，你真是出口天才，这笔买卖可以大赚特赚！O(∩_∩)O~");
    }
    return report0;
}

QString LogicForm::getReport1Str () const
{
    bool isShipP = ui->t4_0->isChecked();
    bool isShip20 = ui->t4_1->isChecked();
    bool isShip40 = ui->t4_2->isChecked();

    QString report1;
    if (isShip20 && !ship20Enable()) {
        report1 = QString::fromWCharArray(L"翔哥亲情提示，亲，二十的集装箱装不下那么多货哦！o(>﹏<)o");
    } else if (isShip40 && !ship40Enable()) {
        report1 = QString::fromWCharArray(L"翔哥亲情提示，亲，四十的集装箱装不下那么多货哦！(+﹏+)~");
    } else {
        bool isSP = false;
        bool is20 = false;
        bool is40 = false;
        float min = 0.0f;
        float sp = getShipPCost();
        float s20 = getShip20Cost();
        float s40 = getShip40Cost();
        if (sp < s20) {
            isSP = true;
            is20 = false;
            min = sp;
        } else {
            isSP = false;
            is20 = true;
            min = s20;
        }
        if (min < s40) {
            is40 = false;
        } else {
            isSP = false;
            is20 = false;
            is40 = true;
        }

        bool shouldChange = false;
        if (isShipP && !isSP) {
            shouldChange = true;
        } else if (isShip20 && !is20) {
            shouldChange = true;
        } else if (isShip40 && !is40) {
            shouldChange = true;
        }

        if (shouldChange) {
            if (isSP) {
                report1 = QString::fromWCharArray(L"翔哥亲情提示，亲，拼装会更省钱哦！(^o^)");
            } else if (is20) {
                report1 = QString::fromWCharArray(L"翔哥亲情提示，亲，用二十的集装箱更省钱哦！(∩_∩)");
            } else if (is40) {
                report1 = QString::fromWCharArray(L"翔哥亲情提示，亲，用四十的集装箱更省钱哦！O(∩_∩)O~");
            }
        }
    }
    return report1;
}

void LogicForm::refreshFinal ()
{
    ui->f0->setValue(getCostCFR());
    ui->f1->setValue(getCostCIF());
	ui->f2->setValue(ui->t3->value() * m_productList->getTotalPriceOut());
    ui->f3->setValue(m_productList->getTotalPriceIn());
    ui->f4->setValue(getCostFOB());
    ui->f5->setValue(ui->g7->value() * m_productList->getTotalVolume());
    ui->f6->setValue(ui->g8->value() * ui->t1->value());
    ui->f7->setValue(ui->g10->value() * ui->t2->value());
    ui->f18->setValue(ui->g11->value() * ui->t11->value());
    ui->f8_0->setValue(getRealShipCost());
    ui->f8_1->setValue(getShipCost());
    ui->f9_0->setValue(getRealInsurance());
    ui->f9_1->setValue(getInsurance());
    ui->f10->setValue(getBank());
    ui->f11->setValue(getOtherCost());
    ui->f12->setValue(m_productList->getTotalTTax());
    ui->f13->setValue(getProfit());
    ui->f14->setValue(getFinalProfit());
    ui->f15->setValue(getFinalProfitRate());
    ui->f16->setText(getReport0Str());
    ui->f17->setText(getReport1Str());
}

void LogicForm::on_addProduct_clicked()
{
    Product* pProduct = new Product();
    ProductDialog* pProductDialog = new ProductDialog(this);
    pProductDialog->initProductDialog(pProduct);
    int ret = pProductDialog->exec();
    if (ret) {
        pProductDialog->okProductDialog(pProduct);
        m_productList->addProduct(pProduct);
        this->refreshProductList();
    } else {
        delete pProduct;
    }
    delete pProductDialog;
}

void LogicForm::on_modifyProduct_clicked()
{
    QTreeWidgetItem* item = ui->productList->currentItem();
    if (item) {
        int index = item->text(0).toInt();

        Product* pProduct = m_productList->getProduct(index);

        ProductDialog* pProductDialog = new ProductDialog(this);
        pProductDialog->initProductDialog(pProduct);
        int ret = pProductDialog->exec();

        if (ret) {
            pProductDialog->okProductDialog(pProduct);
            this->refreshProductList();
        }
    } else {
        QMessageBox::warning(this, "", QString::fromWCharArray(L"亲，请选择要修改的商品！(⊙o⊙)…"), QMessageBox::Yes);
    }
}

void LogicForm::on_deleteProduct_clicked()
{
    QTreeWidgetItem* item = ui->productList->currentItem();
    if (item) {
        int index = item->text(0).toInt();
        int ret = QMessageBox::question(this, "", QString::fromWCharArray(L"亲，你确定要删除该商品吗？(＞﹏＜)"));
        if (ret) {
            m_productList->deleteProduct(index);
            this->refreshProductList();
        }
    } else {
        QMessageBox::warning(this, "", QString::fromWCharArray(L"亲，请选择要删除的商品！(╯3╰)"), QMessageBox::Yes);
    }
}

void LogicForm::on_computefinalInformation_clicked()
{
    this->refreshFinal();
}
