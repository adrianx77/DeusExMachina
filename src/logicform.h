#ifndef LOGICFORM_H
#define LOGICFORM_H

#include <QWidget>

namespace Ui {
class LogicForm;
}

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

private:
    float getCostCIF () const;
    float getCostCFR () const;
    float getCostFOB () const;

    float getShipCost () const;
    float getRealShipCost () const;
    float getShipPCost () const;
    float getShip20Cost () const;
    float getShip40Cost () const;
    bool ship20Enable () const;
    bool ship40Enable () const;

    float getInsurance () const;
    float getRealInsurance () const;
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
};

#endif // LOGICFORM_H
