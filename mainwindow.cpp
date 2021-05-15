#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_doubleValidator(-1000000000, 1000000000, 6, this)
{
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            coefs[i][j] = 0;
        }
        terms[i] = 0;
    }
    numberOfMembers = 1;
    activated = false;
    ui->setupUi(this);
    m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
    ui->XCoef1->setValidator(&m_doubleValidator);
    ui->XCoef2->setValidator(&m_doubleValidator);
    ui->XCoef3->setValidator(&m_doubleValidator);
    ui->YCoef1->setValidator(&m_doubleValidator);
    ui->YCoef2->setValidator(&m_doubleValidator);
    ui->YCoef3->setValidator(&m_doubleValidator);
    ui->ZCoef1->setValidator(&m_doubleValidator);
    ui->ZCoef2->setValidator(&m_doubleValidator);
    ui->ZCoef3->setValidator(&m_doubleValidator);
    ui->Term1->setValidator(&m_doubleValidator);
    ui->Term2->setValidator(&m_doubleValidator);
    ui->Term3->setValidator(&m_doubleValidator);
    connect(ui->XCoef1, &QLineEdit::textChanged, this, &MainWindow::on_changeX1);
    connect(ui->XCoef2, &QLineEdit::textChanged, this, &MainWindow::on_changeX2);
    connect(ui->XCoef3, &QLineEdit::textChanged, this, &MainWindow::on_changeX3);
    connect(ui->YCoef1, &QLineEdit::textChanged, this, &MainWindow::on_changeY1);
    connect(ui->YCoef2, &QLineEdit::textChanged, this, &MainWindow::on_changeY2);
    connect(ui->YCoef3, &QLineEdit::textChanged, this, &MainWindow::on_changeY3);
    connect(ui->ZCoef1, &QLineEdit::textChanged, this, &MainWindow::on_changeZ1);
    connect(ui->ZCoef2, &QLineEdit::textChanged, this, &MainWindow::on_changeZ2);
    connect(ui->ZCoef3, &QLineEdit::textChanged, this, &MainWindow::on_changeZ3);
    connect(ui->Term1, &QLineEdit::textChanged, this, &MainWindow::on_changeTerm1);
    connect(ui->Term2, &QLineEdit::textChanged, this, &MainWindow::on_changeTerm2);
    connect(ui->Term3, &QLineEdit::textChanged, this, &MainWindow::on_changeTerm3);
    connect(ui->SaveSolutionButton, &QPushButton::clicked, this, &MainWindow::clickSaveButton);
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(get_item(QListWidgetItem*)));
    connect(ui->ShowSolutionButton, &QPushButton::clicked, this, &MainWindow::show_solution);
    setStyleSheet("QWidget {background-color:#44556E}");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickSaveButton(){
    if (activated){
        ui->listWidget->addItem(QString::fromStdString(std::to_string(numberOfMembers) +
                                                       ". " + ui->XCoef1->text().toStdString() + "X + " +
                                                       ui->YCoef1->text().toStdString() + "Y + " +
                                                       ui->ZCoef1->text().toStdString() + "Z = " +
                                                       ui->Term1->text().toStdString() + '\n' +
                                                       ui->XCoef2->text().toStdString() + "X + " +
                                                       ui->YCoef2->text().toStdString() + "Y + " +
                                                       ui->ZCoef2->text().toStdString() + "Z = " +
                                                       ui->Term2->text().toStdString() + '\n' +
                                                       ui->XCoef3->text().toStdString() + "X + " +
                                                       ui->YCoef3->text().toStdString() + "Y + " +
                                                       ui->ZCoef3->text().toStdString() + "Z = " +
                                                       ui->Term3->text().toStdString() + '\n' +
                                                       "Ответ: " + ui->textBrowser->toPlainText().toStdString()));
        QString str_coefs[3][3];
        QString str_terms[3];
        str_coefs[0][0] = ui->XCoef1->text();
        str_coefs[0][1] = ui->XCoef2->text();
        str_coefs[0][2] = ui->XCoef3->text();
        str_coefs[1][0] = ui->YCoef1->text();
        str_coefs[1][1] = ui->YCoef2->text();
        str_coefs[1][2] = ui->YCoef3->text();
        str_coefs[2][0] = ui->ZCoef1->text();
        str_coefs[2][1] = ui->ZCoef2->text();
        str_coefs[2][2] = ui->ZCoef3->text();
        str_terms[0] = ui->Term1->text();
        str_terms[1] = ui->Term2->text();
        str_terms[2] = ui->Term3->text();
        history.push_back(linear_system(str_coefs, str_terms, ui->textBrowser->toPlainText()));
        ++numberOfMembers;
    }
}

void MainWindow::on_changeX1(){
    activated = true;
    coefs[0][0] = ui->XCoef1->text().toDouble();
    solve();
}

void MainWindow::on_changeX2(){
    activated = true;
    coefs[0][1] = ui->XCoef2->text().toDouble();
    solve();
}

void MainWindow::on_changeX3(){
    activated = true;
    coefs[0][2] = ui->XCoef3->text().toDouble();
    solve();
}

void MainWindow::on_changeY1(){
    activated = true;
    coefs[1][0] = ui->YCoef1->text().toDouble();
    solve();
}

void MainWindow::on_changeY2(){
    activated = true;
    coefs[1][1] = ui->YCoef2->text().toDouble();
    solve();
}

void MainWindow::on_changeY3(){
    activated = true;
    coefs[1][2] = ui->YCoef3->text().toDouble();
    solve();
}

void MainWindow::on_changeZ1(){
    activated = true;
    coefs[2][0] = ui->ZCoef1->text().toDouble();
    solve();
}

void MainWindow::on_changeZ2(){
    activated = true;
    coefs[2][1] = ui->ZCoef2->text().toDouble();
    solve();
}

void MainWindow::on_changeZ3(){
    activated = true;
    coefs[2][2] = ui->ZCoef3->text().toDouble();
    solve();
}

void MainWindow::on_changeTerm1(){
    activated = true;
    terms[0] = ui->Term1->text().toDouble();
    solve();
}

void MainWindow::on_changeTerm2(){
    activated = true;
    terms[1] = ui->Term2->text().toDouble();
    solve();
}

void MainWindow::on_changeTerm3(){
    activated = true;
    terms[2] = ui->Term3->text().toDouble();
    solve();
}

double MainWindow::determinant(double matrix[3][3]){
    return matrix[0][0] * matrix[1][1] * matrix[2][2] +
           matrix[0][1] * matrix[1][2] * matrix[2][0] +
           matrix[1][0] * matrix[2][1] * matrix[0][2] -
           matrix[0][2] * matrix[1][1] * matrix[2][0] -
           matrix[0][1] * matrix[1][0] * matrix[2][2] -
           matrix[0][0] * matrix[1][2] * matrix[2][1];
}

void MainWindow::solve(){
    double matrix_tmp[3][3];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_tmp[i][j] = coefs[i][j];
        }
    }
    double base_det = determinant(matrix_tmp);
    for (int i = 0; i < 3; ++i){
        matrix_tmp[0][i] = terms[i];
    }
    double det1 = determinant(matrix_tmp);
    for (int i = 0; i < 3; ++i){
        matrix_tmp[0][i] = coefs[0][i];
    }
    for (int i = 0; i < 3; ++i){
        matrix_tmp[1][i] = terms[i];
    }
    double det2 = determinant(matrix_tmp);
    for (int i = 0; i < 3; ++i){
        matrix_tmp[1][i] = coefs[1][i];
    }
    for (int i = 0; i < 3; ++i){
        matrix_tmp[2][i] = terms[i];
    }
    double det3 = determinant(matrix_tmp);
    if (base_det != 0){
        ui->textBrowser->setText(QString::fromStdString("X = " + std::to_string(det1 / base_det) +
                                 "; Y = " + std::to_string(det2 / base_det) +
                                 "; Z = " + std::to_string(det3 / base_det)));
    } else if(det1 == 0 && det2 == 0 && det3 == 0) {
        ui->textBrowser->setText("Система не определена");
    }
    else {
        ui->textBrowser->setText("Система несовместна");
    }
}

void MainWindow::get_item(QListWidgetItem* item){
    int number = item->text().split('.')[0].toInt() - 1;
    coefs[0][0] = history[number].get_coefX1().toDouble();
    coefs[0][1] = history[number].get_coefX2().toDouble();
    coefs[0][2] = history[number].get_coefX3().toDouble();
    coefs[1][0] = history[number].get_coefY1().toDouble();
    coefs[1][1] = history[number].get_coefY2().toDouble();
    coefs[1][2] = history[number].get_coefY3().toDouble();
    coefs[2][0] = history[number].get_coefZ1().toDouble();
    coefs[2][1] = history[number].get_coefZ2().toDouble();
    coefs[2][2] = history[number].get_coefZ3().toDouble();
    terms[0] = history[number].get_term1().toDouble();
    terms[1] = history[number].get_term2().toDouble();
    terms[2] = history[number].get_term3().toDouble();
    ui->textBrowser->setText(history[number].get_answer());
    ui->XCoef1->setText(history[number].get_coefX1());
    ui->XCoef2->setText(history[number].get_coefX2());
    ui->XCoef3->setText(history[number].get_coefX3());
    ui->YCoef1->setText(history[number].get_coefY1());
    ui->YCoef2->setText(history[number].get_coefY2());
    ui->YCoef3->setText(history[number].get_coefY3());
    ui->ZCoef1->setText(history[number].get_coefZ1());
    ui->ZCoef2->setText(history[number].get_coefZ2());
    ui->ZCoef3->setText(history[number].get_coefZ3());
    ui->Term1->setText(history[number].get_term1());
    ui->Term2->setText(history[number].get_term2());
    ui->Term3->setText(history[number].get_term3());
}

void MainWindow::show_solution(){
    solution_dialog = new Solution(this, coefs, terms, ui->comboBox->currentIndex());
    solution_dialog->show();
}
