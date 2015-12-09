#ifndef PRODUCTDIALOG_H
#define PRODUCTDIALOG_H

#include <QDialog>

namespace Ui {
class ProductDialog;
}

class Product;
class ProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductDialog(QWidget *parent = 0);
    ~ProductDialog();

    void initProductDialog (const Product* p);
    void okProductDialog (Product* p);
private:
    Ui::ProductDialog *ui;
};

#endif // PRODUCTDIALOG_H
