#include "logicform.h"
#include "ui_logicform.h"
#include "productdialog.h"
#include "productlist.h"
#include "product.h"
#include "pronounceNum.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <math.h>

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

#define TOKEN_FUNC_BEG(name)    QString LogicForm::get_##name(int processIdx) const               \
                                {

#define TOKEN_FUNC_END              return QString::fromWCharArray(L"无法提取信息");  \
                                }

#define TOKEN_FUNC_REG(name)    m_tokenFuns.insert(#name, &LogicForm::get_##name)


#define TOKEN_PRODUCT_BEG(name) QString LogicForm::get_product##name(int idx, const Product* p) const               \
                                {

#define TOKEN_PRODUCT_END           return QString::fromWCharArray(L"无法提取产品信息");  \
                                }

#define TOKEN_PRODUCT_REG(name) m_productFuns.insert(#name, &LogicForm::get_product##name)


#define UI_TEXT(name)           ui->name->text()
#define UI_VALUE(name)          ui->name->value()
#define UI_CHECKED(name)        ui->name->isChecked()

LogicForm::LogicForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogicForm)
{
    ui->setupUi(this);
    m_productList = new ProductList();
    registerFileList();
    registerTokenFunc();
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
    ui->totalJWeight->setValue(m_productList->getTotalJWeight());
    ui->totalVolume->setValue(m_productList->getTotalVolume());
    ui->totalPakNumber->setValue(m_productList->getTotalPakNumber());
    ui->totalProductNumber->setValue(m_productList->getTotalProductNumber());
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
    float wCost = m_productList->getTotalMWeight() * ui->h6->value()* ui->h4->value() / 1000.0f;
    return MAX(vCost, wCost);
}

float LogicForm::getShip20Cost () const
{
    return (ui->h7->value() + ui->h8->value() + ui->h9->value()) * ui->h4->value() * getShip20Number();
}

float LogicForm::getShip40Cost () const
{
    return (ui->h10->value() + ui->h11->value() + ui->h12->value()) * ui->h4->value() * getShip40Number();
}

int LogicForm::getShip20Number () const
{
    int vNumber = (int)ceilf(m_productList->getTotalVolume() / ui->h0->value());
    int wNumber = (int)ceilf(m_productList->getTotalMWeight() / ui->h1->value());
    return MAX(vNumber, wNumber);
}

int LogicForm::getShip40Number () const
{
    int vNumber = (int)ceilf(m_productList->getTotalVolume() / ui->h2->value());
    int wNumber = (int)ceilf(m_productList->getTotalMWeight() / ui->h3->value());
    return MAX(vNumber, wNumber);
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

float LogicForm::getWaibiInsurance () const
{
    return getInsurance() / UI_VALUE(t3);
}

float LogicForm::getWaibiRealInsurance () const
{
    return getRealInsurance() / UI_VALUE(t3);
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
    ProductDialog* pProductDialog = new ProductDialog(this);
    pProductDialog->initProductDialog(NULL);
    int ret = pProductDialog->exec();
    if (ret) {
        Product* pProduct = new Product();
        pProductDialog->okProductDialog(pProduct);
        m_productList->addProduct(pProduct);
        this->refreshProductList();
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

void LogicForm::registerFileList ()
{
    m_processList.push_back(QString::fromWCharArray(L"合同.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"合同商品明细表.html"));

    m_processList.push_back(QString::fromWCharArray(L"出口预算表.html"));
    m_processProductList.push_back(QString::fromWCharArray(L""));

    m_processList.push_back(QString::fromWCharArray(L"货物出运委托书.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"货物出运委托书商品明细表.html"));

    m_processList.push_back(QString::fromWCharArray(L"出境货物报检单.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"出境货物报检单商品明细表.html"));

    m_processList.push_back(QString::fromWCharArray(L"商业发票.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"商业发票商品明细表.html"));

    m_processList.push_back(QString::fromWCharArray(L"装箱单.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"装箱单商品明细表.html"));

    m_processList.push_back(QString::fromWCharArray(L"货物运输保险投保单.html"));
    m_processProductList.push_back(QString::fromWCharArray(L""));

    m_processList.push_back(QString::fromWCharArray(L"出口收汇核销单.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"出口收汇核销单商品明细表.html"));

    m_processList.push_back(QString::fromWCharArray(L"出口报关单.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"出口报关单商品明细表.html"));

    m_processList.push_back(QString::fromWCharArray(L"装船通知.html"));
    m_processProductList.push_back(QString::fromWCharArray(L""));

    m_processList.push_back(QString::fromWCharArray(L"出口收汇核销单送审登记表.html"));
    m_processProductList.push_back(QString::fromWCharArray(L""));

    m_processList.push_back(QString::fromWCharArray(L"买卖合同.html"));
    m_processProductList.push_back(QString::fromWCharArray(L"买卖合同商品明细表.html"));
}

void LogicForm::registerTokenFunc ()
{
    TOKEN_FUNC_REG(TEMPLATE_CompanyNameEn);
    TOKEN_FUNC_REG(TEMPLATE_CompanyAddressEn);
    TOKEN_FUNC_REG(TEMPLATE_CompanyNameZh);
    TOKEN_FUNC_REG(TEMPLATE_CompanyAddressZh);
    TOKEN_FUNC_REG(TEMPLATE_CompanyIdentifier);
    TOKEN_FUNC_REG(TEMPLATE_ImportCompanyName);
    TOKEN_FUNC_REG(TEMPLATE_ImportCompanyAddress);
    TOKEN_FUNC_REG(TEMPLATE_ContractNo);
    TOKEN_FUNC_REG(TEMPLATE_Date);
    TOKEN_FUNC_REG(TEMPLATE_DeliveryType);
    TOKEN_FUNC_REG(TEMPLATE_DeliveryPortEn);
    TOKEN_FUNC_REG(TEMPLATE_TotalQuantityOfProduct);
    TOKEN_FUNC_REG(TEMPLATE_TotalQuantityType);
    TOKEN_FUNC_REG(TEMPLATE_SellCurrency);
    TOKEN_FUNC_REG(TEMPLATE_TotalSell);
    TOKEN_FUNC_REG(TEMPLATE_TotalSaySell);
    TOKEN_FUNC_REG(TEMPLATE_Payment);
    TOKEN_FUNC_REG(TEMPLATE_QuantityPerCarton);
    TOKEN_FUNC_REG(TEMPLATE_ShipPortEn);
    TOKEN_FUNC_REG(TEMPLATE_DestPortEn);
    TOKEN_FUNC_REG(TEMPLATE_ShipPortZh);
    TOKEN_FUNC_REG(TEMPLATE_DestPortZh);
    TOKEN_FUNC_REG(TEMPLATE_ImportContryEn);
    TOKEN_FUNC_REG(TEMPLATE_ImportContryZh);
    TOKEN_FUNC_REG(TEMPLATE_TotalCarton);
    TOKEN_FUNC_REG(TEMPLATE_TotalSayCarton);
    TOKEN_FUNC_REG(TEMPLATE_TheTypeOfTotalCarton);
    TOKEN_FUNC_REG(TEMPLATE_InsuranceDesc);
    TOKEN_FUNC_REG(TEMPLATE_MyNameEn);
    TOKEN_FUNC_REG(TEMPLATE_MyNameZn);
    TOKEN_FUNC_REG(TEMPLATE_MyPhoneNo);
    TOKEN_FUNC_REG(TEMPLATE_MyChuanzhenNo);
    TOKEN_FUNC_REG(TEMPLATE_MyPostNo);
    TOKEN_FUNC_REG(TEMPLATE_MyHaiguanNo);
    TOKEN_FUNC_REG(TEMPLATE_ShippingMark);
    TOKEN_FUNC_REG(TEMPLATE_TotalMaoWeight);
    TOKEN_FUNC_REG(TEMPLATE_TotalJinWeight);
    TOKEN_FUNC_REG(TEMPLATE_TotalVolume);
    TOKEN_FUNC_REG(TEMPLATE_TotalFOBSell);
    TOKEN_FUNC_REG(TEMPLATE_TotalCFRSell);
    TOKEN_FUNC_REG(TEMPLATE_TotalCIFSell);
    TOKEN_FUNC_REG(TEMPLATE_ProductBigType);

    TOKEN_FUNC_REG(TEMPLATE_BankNo);
    TOKEN_FUNC_REG(TEMPLATE_BankNameEn);
    TOKEN_FUNC_REG(TEMPLATE_BankNameZh);

    TOKEN_FUNC_REG(TEMPLATE_InvoiceNo);
    TOKEN_FUNC_REG(TEMPLATE_CreditNo);
    TOKEN_FUNC_REG(TEMPLATE_TheShipName);
    TOKEN_FUNC_REG(TEMPLATE_TheShipWorkNo);
    TOKEN_FUNC_REG(TEMPLATE_HexiaodanNo);

    TOKEN_FUNC_REG(TEMPLATE_Hetongjine);
    TOKEN_FUNC_REG(TEMPLATE_Caigoucengben);
    TOKEN_FUNC_REG(TEMPLATE_FOBZongjia);
    TOKEN_FUNC_REG(TEMPLATE_Neiluyunfei);
    TOKEN_FUNC_REG(TEMPLATE_Baojianfei);
    TOKEN_FUNC_REG(TEMPLATE_Baoguanfei);
    TOKEN_FUNC_REG(TEMPLATE_Haiyunfei);
    TOKEN_FUNC_REG(TEMPLATE_Baoxianfei);
    TOKEN_FUNC_REG(TEMPLATE_Hexiaofei);
    TOKEN_FUNC_REG(TEMPLATE_Yinhangfeiyong);
    TOKEN_FUNC_REG(TEMPLATE_Qitafeiyong);
    TOKEN_FUNC_REG(TEMPLATE_Tuisuishouru);
    TOKEN_FUNC_REG(TEMPLATE_Lirun);

    TOKEN_FUNC_REG(TEMPLATE_Yunfeiyufu);
    TOKEN_FUNC_REG(TEMPLATE_Yunfeidaofu);

    TOKEN_FUNC_REG(TEMPLATE_WaiBi_Baoxianfei);
    TOKEN_FUNC_REG(TEMPLATE_WaiBi_Haiyunfei);
    TOKEN_FUNC_REG(TEMPLATE_WaiBi_YouJiaGe_Baoxianfei);
    TOKEN_FUNC_REG(TEMPLATE_WaiBi_YouJiaGe_Haiyunfei);
    TOKEN_FUNC_REG(TEMPLATE_ShipContainer);

    TOKEN_FUNC_REG(TEMPLATE_FactoryCompanyName);
    TOKEN_FUNC_REG(TEMPLATE_FactoryCompanyAddress);
    TOKEN_FUNC_REG(TEMPLATE_TotalBuy);
    TOKEN_FUNC_REG(TEMPLATE_TotalSayBuy);
    TOKEN_FUNC_REG(TEMPLATE_MyTaxNo);
    TOKEN_FUNC_REG(TEMPLATE_MyBankNo);

    TOKEN_FUNC_REG(PRODUCT_HERF_LINK);


    /////////////////////////////////////////////////////////////
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductId);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductNameEn);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductNameZh);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductDescEn);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductDescZh);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductQuantity);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductPakNo);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductPC);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductCarton);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductPriceIn);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductTotalPriceIn);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductPriceOut);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductTotalPriceOut);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_SellCurrency);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ShippingMark);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductMaoWeight);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductJinWeight);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductTotalMaoWeight);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductTotalJinWeight);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductHSCode);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductMadeIn);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductVolume);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductTotalVolume);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductType);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ProductIndex);
    TOKEN_PRODUCT_REG(TEAMPLATE_P_ImportContryZh);

}

bool LogicForm::copyDir (const QString& fromDir, const QString& toDir)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if (targetDir.exists()) {
        targetDir.removeRecursively();
    }

    if (!targetDir.exists()) {
        if (!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach (QFileInfo fileInfo, fileInfoList) {
        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if (fileInfo.isDir()) {
            if (!copyDir(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))) {
                return false;
            }
        } else {
            if (!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))) {
                return false;
            }
        }
    }
    return true;
}

void LogicForm::doReplaceTemplateDir (const QString& dir)
{
    for (int i = 0; i < m_processList.length(); ++i) {
        const QString& filename = m_processList[i];
        doReplaceTemplateFile(dir + "/" + filename, i);
    }
}

void LogicForm::doReplaceTemplateFile (const QString& file, int processIdx)
{
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&f);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    f.close();
    QMap<QString, LogicFormTokenFunc>::iterator itBeg = m_tokenFuns.begin();
    QMap<QString, LogicFormTokenFunc>::iterator itEnd = m_tokenFuns.end();
    while (itBeg != itEnd) {
        const QString& k = itBeg.key();
        LogicFormTokenFunc v = itBeg.value();
        const QString& result = (this->*v)(processIdx);
        text.replace(k, result);
        ++itBeg;
    }

    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    f.write(text.toUtf8());
    f.close();
}

void LogicForm::doReplaceProductTemplateDir (const QString& dir, int productIdx)
{
    for (int i = 0; i < m_processProductList.length(); ++i) {
        const QString& filename = m_processProductList[i];
        doReplaceProductTemplateFile(dir + "/" + filename, productIdx);
    }
}

void LogicForm::doReplaceProductTemplateFile (const QString& file, int productIdx)
{
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&f);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    f.close();
    QMap<QString, LogicFormProductFunc>::iterator itBeg = m_productFuns.begin();
    QMap<QString, LogicFormProductFunc>::iterator itEnd = m_productFuns.end();
    Product* p = m_productList->getProduct(productIdx);
    while (itBeg != itEnd) {
        const QString& k = itBeg.key();
        LogicFormProductFunc v = itBeg.value();
        const QString& result = (this->*v)(productIdx, p);
        text.replace(k, result);
        ++itBeg;
    }

    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    f.write(text.toUtf8());
    f.close();
}

QString LogicForm::getDeliveryMode () const
{
    if (UI_CHECKED(t0_0))
        return "FOB";
    if (UI_CHECKED(t0_1))
        return "CFR";
    if (UI_CHECKED(t0_2))
        return "CIF";
    return "";
}

QString LogicForm::getPaymentMode () const
{
    if (UI_CHECKED(t6_0))
        return "T/T";
    if (UI_CHECKED(t6_1))
        return "L/C";
    if (UI_CHECKED(t6_2))
        return "D/P";
    if (UI_CHECKED(t6_3))
        return "D/A";
    return "";
}

void LogicForm::on_exportList_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QString outDir = QString::fromWCharArray(L"单据_") + time.toString(QString::fromWCharArray(L"hh点mm分ss秒"));
    copyDir("template", outDir);
    doReplaceTemplateDir(outDir);
    for (int i = 0; i < m_productList->getProductNum(); ++i) {
        QString productDir = outDir + "/product" + QString::number(i);
        copyDir("template_product", productDir);
        doReplaceProductTemplateDir(productDir, i);
    }
    QMessageBox::warning(this, "", QString::fromWCharArray(L"亲，已经导出成功了！"), QMessageBox::Yes);
}

QString LogicForm::test () const
{
    return "";
}

TOKEN_FUNC_BEG(TEMPLATE_CompanyNameEn)
return UI_TEXT(c3);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_CompanyAddressEn)
return UI_TEXT(c15);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_CompanyNameZh)
return UI_TEXT(c2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_CompanyAddressZh)
return UI_TEXT(c14);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_CompanyIdentifier)
return UI_TEXT(c6);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ImportCompanyName)
return UI_TEXT(e2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ImportCompanyAddress)
return UI_TEXT(e3);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ContractNo)
return UI_TEXT(e0);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Date)
QDateTime time = QDateTime::currentDateTime();
return time.toString("yyyy-MM-dd");
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_DeliveryType)
return this->getDeliveryMode();
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_DeliveryPortEn)
if (UI_CHECKED(t0_0))
    return UI_TEXT(e7);
if (UI_CHECKED(t0_1))
    return UI_TEXT(e9);
if (UI_CHECKED(t0_2))
    return UI_TEXT(e9);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalQuantityOfProduct)
return QString::number(m_productList->getTotalProductNumber());
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalQuantityType)
return m_productList->getProductQuantityType();
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_SellCurrency)
return UI_TEXT(e1);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalSell)
return QString::number(m_productList->getTotalPriceOut(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalSaySell)
PronounceNum p;
return UI_TEXT(e1) + ". " + p.numToString(m_productList->getTotalPriceOut()).c_str() + "SAY";
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Payment)
return this->getPaymentMode();
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_QuantityPerCarton)
return m_productList->getPakInfoEn();
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ShipPortEn)
return UI_TEXT(e7);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_DestPortEn)
return UI_TEXT(e9);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ShipPortZh)
return UI_TEXT(e6);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_DestPortZh)
return UI_TEXT(e8);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ImportContryEn)
return UI_TEXT(e5);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ImportContryZh)
return UI_TEXT(e4);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalCarton)
return QString::number(m_productList->getTotalPakNumber());
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalSayCarton)
PronounceNum p;
return (p.numToString(m_productList->getTotalPakNumber()) + "SAY").c_str();
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TheTypeOfTotalCarton)
return m_productList->getProductPakType();
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_InsuranceDesc)
if (UI_CHECKED(t0_0)) {
    return "Insurance effected by buyer";
} else {
    return "The SELLER shall arrange marine insurance covering ALL Risks bearing Institute Cargo Clauses (ALL Risks) plus institute War Clause (Cargo) for 110% of CIF value and provide of claim, if any, payable in U.A.E. with U.S. currency";
}
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyNameEn)
return UI_TEXT(c5);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyNameZn)
return UI_TEXT(c4);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyPhoneNo)
return UI_TEXT(c9);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyChuanzhenNo)
return UI_TEXT(c10);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyPostNo)
return UI_TEXT(c11);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyHaiguanNo)
return UI_TEXT(c8);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ShippingMark)
QString result;
result += m_productList->getProductNameEn();
result += '\n';
result += UI_TEXT(e5);
result += '\n';
result += "C/NO.1-" + QString::number(m_productList->getTotalPakNumber());
result += '\n';
result += "MADE IN CHINA";
return result;
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Hetongjine)
return QString::number(ui->t3->value() * m_productList->getTotalPriceOut(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Caigoucengben)
return QString::number(m_productList->getTotalPriceIn(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_FOBZongjia)
return QString::number(getCostFOB(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Neiluyunfei)
return QString::number(ui->g7->value() * m_productList->getTotalVolume(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Baojianfei)
return QString::number(ui->g8->value() * ui->t1->value(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Baoguanfei)
return QString::number(ui->g10->value() * ui->t2->value(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Haiyunfei)
return QString::number(getRealShipCost(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Baoxianfei)
return QString::number(getRealInsurance(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Hexiaofei)
return QString::number(ui->g11->value() * ui->t11->value(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Yinhangfeiyong)
return QString::number(getBank(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Qitafeiyong)
return QString::number(getOtherCost(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Tuisuishouru)
return QString::number(m_productList->getTotalTTax(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Lirun)
return QString::number(getProfit(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Yunfeiyufu)
return UI_CHECKED(t0_0) ? "NO" : "YES";
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_Yunfeidaofu)
return UI_CHECKED(t0_0) ? "YES" : "NO";
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalMaoWeight)
return QString::number(m_productList->getTotalMWeight(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalJinWeight)
return QString::number(m_productList->getTotalJWeight(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalVolume)
return QString::number(m_productList->getTotalVolume(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalFOBSell)
return QString::number(getCostFOB()/UI_VALUE(t3), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalCFRSell)
return QString::number(getCostCFR()/UI_VALUE(t3), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalCIFSell)
return QString::number(getCostCIF()/UI_VALUE(t3), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_InvoiceNo)
return UI_TEXT(e20);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_CreditNo)
return UI_TEXT(e21);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TheShipName)
return UI_TEXT(e22);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TheShipWorkNo)
return UI_TEXT(e23);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_HexiaodanNo)
return UI_TEXT(e24);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_BankNo)
return UI_TEXT(e10);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_BankNameEn)
return UI_TEXT(e12);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_BankNameZh)
return UI_TEXT(e11);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_WaiBi_Baoxianfei)
return QString::number(getWaibiRealInsurance(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_WaiBi_Haiyunfei)
return QString::number(getRealShipCost()/UI_VALUE(t3), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_WaiBi_YouJiaGe_Baoxianfei)
return QString::number(getWaibiInsurance(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_WaiBi_YouJiaGe_Haiyunfei)
return QString::number(getShipCost()/UI_VALUE(t3), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ShipContainer)
if(UI_CHECKED(t4_0))
    return QString::fromWCharArray(L"参考-配舱通知");
else if(UI_CHECKED(t4_1))
    return QString("20' X ") + QString::number(getShip20Number());
else if(UI_CHECKED(t4_2))
    return QString("40' X ") + QString::number(getShip40Number());
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_ProductBigType)
return m_productList->getProductBigType();
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_FactoryCompanyName)
return UI_TEXT(e30);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_FactoryCompanyAddress)
return UI_TEXT(e31);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalBuy)
return QString::number(m_productList->getTotalPriceIn(), 'f', 2);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_TotalSayBuy)
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyTaxNo)
return UI_TEXT(c7);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(TEMPLATE_MyBankNo)
return UI_TEXT(c1);
TOKEN_FUNC_END

TOKEN_FUNC_BEG(PRODUCT_HERF_LINK)
QString result;
QString productListName = m_processProductList[processIdx];
for (int i = 0; i < m_productList->getProductNum(); ++i) {
    result += "<a href=\"./product" + QString::number(i) + "/" + productListName + "\">" + m_productList->getProduct(i)->getName() + "</a><br>";
}
return result;
TOKEN_FUNC_END

////////////////////////////////////////////////////////////////////////////////////////////
TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductId)
return p->id();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductNameEn)
return p->nameEn();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductNameZh)
return p->getName();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductDescEn)
return p->descEn();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductDescZh)
return p->descZh();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductQuantity)
return QString::number(p->getNumber());
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductPakNo)
return QString::number(p->getPakNumber());
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductPC)
return p->pc();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductCarton)
return p->carton();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductPriceIn)
return QString::number(p->getPriceIn(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductTotalPriceIn)
return QString::number(p->getTotalPriceIn(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductPriceOut)
return QString::number(p->getPriceOut(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductTotalPriceOut)
return QString::number(p->getTotalPriceOut(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_SellCurrency)
return UI_TEXT(e1);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ShippingMark)
QString result;
result += p->nameEn();
result += '\n';
result += UI_TEXT(e5);
result += '\n';
result += "C/NO.1-" + QString::number(p->getPakNumber());
result += '\n';
result += "MADE IN CHINA";
return result;
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductMaoWeight)
return QString::number(p->getMWeight(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductJinWeight)
return QString::number(p->getJWeight(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductTotalMaoWeight)
return QString::number(p->getTotalMWeight(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductTotalJinWeight)
return QString::number(p->getTotalJWeight(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductHSCode)
return p->haiguan();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductMadeIn)
return p->birth();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductVolume)
return QString::number(p->getVolume(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductTotalVolume)
return QString::number(p->getTotalVolume(), 'f', 2);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductType)
return p->type();
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ProductIndex)
return QString::number(idx + 1);
TOKEN_PRODUCT_END

TOKEN_PRODUCT_BEG(TEAMPLATE_P_ImportContryZh)
return UI_TEXT(e4);
TOKEN_PRODUCT_END
