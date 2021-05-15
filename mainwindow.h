#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QListWidgetItem>
#include "linear_system.h"
#include "solution.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void on_changeX1();
    void on_changeX2();
    void on_changeX3();
    void on_changeY1();
    void on_changeY2();
    void on_changeY3();
    void on_changeZ1();
    void on_changeZ2();
    void on_changeZ3();
    void on_changeTerm1();
    void on_changeTerm2();
    void on_changeTerm3();
    void solve();
    double determinant(double[3][3]);
    void clickSaveButton();
    void get_item(QListWidgetItem*);
    void show_solution();

private:
    Ui::MainWindow *ui;
    Solution *solution_dialog;
    QDoubleValidator m_doubleValidator;
    double coefs[3][3];
    double terms[3];
    int numberOfMembers;
    bool activated;
    std::vector<linear_system> history;
};
#endif // MAINWINDOW_H
