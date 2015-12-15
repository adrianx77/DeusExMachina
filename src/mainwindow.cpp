#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logicform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pLogicForm = new LogicForm();
    ui->scrollArea->setWidget(m_pLogicForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    m_pLogicForm->onOpenTrigger();
}

void MainWindow::on_actionClose_triggered()
{
    m_pLogicForm->onSaveTrigger();
}
