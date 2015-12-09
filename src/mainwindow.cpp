#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logicform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LogicForm* logicForm = new LogicForm();
    ui->scrollArea->setWidget(logicForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
