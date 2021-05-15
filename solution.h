#ifndef SOLUTION_H
#define SOLUTION_H

#include <QDialog>

namespace Ui {
class Solution;
}

class Solution : public QDialog
{
    Q_OBJECT

public:
    explicit Solution(QWidget *parent, double[3][3], double[3], int);
    ~Solution();

private slots:
    void cramer(double[3][3], double[3]);
    void gauss(double[3][3], double[3]);
    void inverse_matrix(double[3][3], double[3]);
    double determinant(double[3][3]);
    QString double_to_str(double);
    void close();
    void print_system(double[3][3], double[3]);
    double print_alg_dop(int, int, double[2][2]);
    void print_matrix(double[3][3]);
    void save_to_file();

private:
    Ui::Solution *ui;
    QString solution_text;
};

#endif // SOLUTION_H
