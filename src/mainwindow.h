#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class LogicForm;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;
    LogicForm*      m_pLogicForm;
};

#endif // MAINWINDOW_H
