#ifndef LOGICFORM_H
#define LOGICFORM_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QMap>

namespace Ui {
class LogicForm;
}

class LogicForm;
typedef QString (LogicForm::*LogicFormTokenFunc)(int processIdx) const;
#define DEF_TOKEN_FUNC(name)    QString get_##name(int processIdx) const

class Product;
typedef QString (LogicForm::*LogicFormProductFunc)(int idx, const Product* p) const;
#define DEF_PRODUCT_FUNC(name)    QString get_product##name(int idx, const Product* p) const

class ProductList;
class LogicForm : public QWidget
{
    Q_OBJECT

public:
    explicit LogicForm(QWidget *parent = 0);
    ~LogicForm();

    void refreshProductList ();
    void refreshFinal ();
private slots:
    void on_addProduct_clicked();

    void on_modifyProduct_clicked();

    void on_deleteProduct_clicked();

    void on_computefinalInformation_clicked();

    void on_exportList_clicked();

private:
    float getCostCIF () const;
    float getCostCFR () const;
    float getCostFOB () const;

    float getShipCost () const;
    float getRealShipCost () const;
    float getShipPCost () const;
    float getShip20Cost () const;
    float getShip40Cost () const;
    int getShip20Number () const;
    int getShip40Number () const;

    float getInsurance () const;
    float getRealInsurance () const;
    float getWaibiInsurance () const;
    float getWaibiRealInsurance () const;
    float getInsuranceCIF () const;
    float getInsuranceCFR () const;
    float getInsuranceFOB () const;

    float getBank () const;
    float getBankLC () const;
    float getBankDP () const;
    float getBankDA () const;

    float getOtherCost () const;
    float getProfit () const;

    float getFinalProfit () const;
    float getFinalProfitRate () const;

    QString getReport0Str () const;
    QString getReport1Str () const;

    Ui::LogicForm *ui;
    ProductList*   m_productList;

    void registerFileList ();
    void registerTokenFunc ();
    bool copyDir (const QString& fromDir, const QString& toDir);
    void doReplaceTemplateDir (const QString& dir);
    void doReplaceTemplateFile (const QString& file, int processIdx);

    void doReplaceProductTemplateDir (const QString& dir, int productIdx);
    void doReplaceProductTemplateFile (const QString& file, int productIdx);

    QString getDeliveryMode () const;
    QString getPaymentMode () const;
private:
    QVector<QString>    m_processList;
    QVector<QString>    m_processProductList;
private:
    QString test () const;

    DEF_TOKEN_FUNC(TEMPLATE_CompanyNameEn);
    DEF_TOKEN_FUNC(TEMPLATE_CompanyAddressEn);
    DEF_TOKEN_FUNC(TEMPLATE_CompanyNameZh);
    DEF_TOKEN_FUNC(TEMPLATE_CompanyAddressZh);
    DEF_TOKEN_FUNC(TEMPLATE_CompanyIdentifier);
    DEF_TOKEN_FUNC(TEMPLATE_ImportCompanyName);
    DEF_TOKEN_FUNC(TEMPLATE_ImportCompanyAddress);
    DEF_TOKEN_FUNC(TEMPLATE_ContractNo);
    DEF_TOKEN_FUNC(TEMPLATE_Date);
    DEF_TOKEN_FUNC(TEMPLATE_DeliveryType);
    DEF_TOKEN_FUNC(TEMPLATE_DeliveryPortEn);
    DEF_TOKEN_FUNC(TEMPLATE_TotalQuantityOfProduct);
    DEF_TOKEN_FUNC(TEMPLATE_TotalQuantityType);
    DEF_TOKEN_FUNC(TEMPLATE_SellCurrency);
    DEF_TOKEN_FUNC(TEMPLATE_TotalSell);
    DEF_TOKEN_FUNC(TEMPLATE_TotalSaySell);
    DEF_TOKEN_FUNC(TEMPLATE_Payment);
    DEF_TOKEN_FUNC(TEMPLATE_QuantityPerCarton);
    DEF_TOKEN_FUNC(TEMPLATE_ShipPortEn);
    DEF_TOKEN_FUNC(TEMPLATE_DestPortEn);
    DEF_TOKEN_FUNC(TEMPLATE_ShipPortZh);
    DEF_TOKEN_FUNC(TEMPLATE_DestPortZh);
    DEF_TOKEN_FUNC(TEMPLATE_ImportContryEn);
    DEF_TOKEN_FUNC(TEMPLATE_ImportContryZh);
    DEF_TOKEN_FUNC(TEMPLATE_TotalCarton);
    DEF_TOKEN_FUNC(TEMPLATE_TotalSayCarton);
    DEF_TOKEN_FUNC(TEMPLATE_TheTypeOfTotalCarton);
    DEF_TOKEN_FUNC(TEMPLATE_InsuranceDesc);
    DEF_TOKEN_FUNC(TEMPLATE_MyNameEn);
    DEF_TOKEN_FUNC(TEMPLATE_MyNameZn);
    DEF_TOKEN_FUNC(TEMPLATE_MyPhoneNo);
    DEF_TOKEN_FUNC(TEMPLATE_MyChuanzhenNo);
    DEF_TOKEN_FUNC(TEMPLATE_MyPostNo);
    DEF_TOKEN_FUNC(TEMPLATE_MyHaiguanNo);
    DEF_TOKEN_FUNC(TEMPLATE_ShippingMark);
    DEF_TOKEN_FUNC(TEMPLATE_TotalMaoWeight);
    DEF_TOKEN_FUNC(TEMPLATE_TotalJinWeight);
    DEF_TOKEN_FUNC(TEMPLATE_TotalVolume);
    DEF_TOKEN_FUNC(TEMPLATE_TotalFOBSell);
    DEF_TOKEN_FUNC(TEMPLATE_TotalCFRSell);
    DEF_TOKEN_FUNC(TEMPLATE_TotalCIFSell);
    DEF_TOKEN_FUNC(TEMPLATE_ProductBigType);

    DEF_TOKEN_FUNC(TEMPLATE_BankNo);
    DEF_TOKEN_FUNC(TEMPLATE_BankNameEn);
    DEF_TOKEN_FUNC(TEMPLATE_BankNameZh);

    DEF_TOKEN_FUNC(TEMPLATE_InvoiceNo);
    DEF_TOKEN_FUNC(TEMPLATE_CreditNo);
    DEF_TOKEN_FUNC(TEMPLATE_TheShipName);
    DEF_TOKEN_FUNC(TEMPLATE_TheShipWorkNo);
    DEF_TOKEN_FUNC(TEMPLATE_HexiaodanNo);

    DEF_TOKEN_FUNC(TEMPLATE_Hetongjine);
    DEF_TOKEN_FUNC(TEMPLATE_Caigoucengben);
    DEF_TOKEN_FUNC(TEMPLATE_FOBZongjia);
    DEF_TOKEN_FUNC(TEMPLATE_Neiluyunfei);
    DEF_TOKEN_FUNC(TEMPLATE_Baojianfei);
    DEF_TOKEN_FUNC(TEMPLATE_Baoguanfei);
    DEF_TOKEN_FUNC(TEMPLATE_Haiyunfei);
    DEF_TOKEN_FUNC(TEMPLATE_Baoxianfei);
    DEF_TOKEN_FUNC(TEMPLATE_Hexiaofei);
    DEF_TOKEN_FUNC(TEMPLATE_Yinhangfeiyong);
    DEF_TOKEN_FUNC(TEMPLATE_Qitafeiyong);
    DEF_TOKEN_FUNC(TEMPLATE_Tuisuishouru);
    DEF_TOKEN_FUNC(TEMPLATE_Lirun);

    DEF_TOKEN_FUNC(TEMPLATE_Yunfeiyufu);
    DEF_TOKEN_FUNC(TEMPLATE_Yunfeidaofu);

    DEF_TOKEN_FUNC(TEMPLATE_WaiBi_Baoxianfei);
    DEF_TOKEN_FUNC(TEMPLATE_WaiBi_Haiyunfei);
    DEF_TOKEN_FUNC(TEMPLATE_WaiBi_YouJiaGe_Baoxianfei);
    DEF_TOKEN_FUNC(TEMPLATE_WaiBi_YouJiaGe_Haiyunfei);
    DEF_TOKEN_FUNC(TEMPLATE_ShipContainer);

    DEF_TOKEN_FUNC(TEMPLATE_FactoryCompanyName);
    DEF_TOKEN_FUNC(TEMPLATE_FactoryCompanyAddress);
    DEF_TOKEN_FUNC(TEMPLATE_TotalBuy);
    DEF_TOKEN_FUNC(TEMPLATE_TotalSayBuy);
    DEF_TOKEN_FUNC(TEMPLATE_MyTaxNo);
    DEF_TOKEN_FUNC(TEMPLATE_MyBankNo);

    DEF_TOKEN_FUNC(PRODUCT_HERF_LINK);

    QMap<QString, LogicFormTokenFunc>   m_tokenFuns;

private:
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductId);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductNameEn);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductNameZh);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductDescEn);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductDescZh);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductQuantity);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductPakNo);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductPC);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductCarton);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductPriceIn);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductTotalPriceIn);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductPriceOut);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductTotalPriceOut);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_SellCurrency);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ShippingMark);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductMaoWeight);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductJinWeight);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductTotalMaoWeight);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductTotalJinWeight);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductHSCode);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductMadeIn);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductVolume);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductTotalVolume);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductType);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ProductIndex);
    DEF_PRODUCT_FUNC(TEAMPLATE_P_ImportContryZh);

    QMap<QString, LogicFormProductFunc>   m_productFuns;
};

#endif // LOGICFORM_H
