#include "solution.h"
#include "ui_solution.h"
#include <algorithm>
#include <QFileDialog>
#include <QMessageBox>

Solution::Solution(QWidget *parent, double coefs[3][3], double terms[3], int method) :
    QDialog(parent),
    ui(new Ui::Solution)
{
    ui->setupUi(this);
    solution_text = "";
    connect(ui->closeButton, &QPushButton::clicked, this, &Solution::close);
    connect(ui->saveToFileButton, &QPushButton::clicked, this, &Solution::save_to_file);
    switch (method){
    case 0: cramer(coefs, terms); break;
    case 1: gauss(coefs, terms); break;
    case 2: inverse_matrix(coefs, terms); break;
    }
}

QString Solution::double_to_str(double in){
    QString result = QString::fromStdString(std::to_string(in));
    double intpart;
    while (result.back() == '0'){
        result.remove(result.length() - 1, 1);
    }
    if (modf(in, &intpart) == 0.0){
        result.remove(result.length() - 1, 1);
    }
    return result;
}

double Solution::print_alg_dop(int pos1, int pos2, double matrix[2][2]){
    QString matrix_to_print[2][2];
    QString separators[2][2];
    int max_size[2];
    QString space_separator = "";
    double alg_dop = std::pow((-1),(pos1+pos2)) *
            (matrix[0][0]*matrix[1][1] - matrix[0][1] * matrix[1][0]);
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            matrix_to_print[i][j] = double_to_str(matrix[i][j]);
        }
    }
    for (int i = 0; i < 2; ++i){
        max_size[i] = std::max(matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length());
    }
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            separators[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separators[i][j] += ' ';
            }
        }
    }
    for (int i = 0; i < max_size[0] + max_size[1] + 2; ++i){
        space_separator += ' ';
    }
    solution_text += "                     |" + matrix_to_print[0][0] + "  " +
            separators[0][0] + matrix_to_print[1][0] + separators[0][1] + "|\n";
    solution_text += "A" + double_to_str(pos1 * 10 + pos2) +" = (-1)^(" +
            double_to_str(pos1) + " + " + double_to_str(pos2) + ") * |" +
            space_separator + "| = " + double_to_str(alg_dop) + '\n';
    solution_text += "                     |" + matrix_to_print[0][1] + "  "  +
            separators[1][0] + matrix_to_print[1][1] + separators[1][1] + "|\n\n\n";
    return alg_dop;
}

void Solution::print_system(double coefs[3][3], double terms[3]){
    QString system_to_print[4][3];
    QString system_separetion[3][4];
    int max_size[4];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            system_to_print[i][j] = double_to_str(coefs[i][j]);
        }
    }
    system_to_print[3][0] = double_to_str(terms[0]);
    system_to_print[3][1] = double_to_str(terms[1]);
    system_to_print[3][2] = double_to_str(terms[2]);
    for (int i = 0; i < 4; ++i){
        max_size[i] = std::max({system_to_print[i][0].length(),
                system_to_print[i][1].length(),
                system_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 4; ++j){
            system_separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - system_to_print[j][i].length(); ++k){
                system_separetion[i][j] += ' ';
            }
        }
    }
    solution_text +=system_to_print[0][0] + ' ' + system_separetion[0][0] +
            system_to_print[1][0] + ' ' + system_separetion[0][1] +
            system_to_print[2][0] + system_separetion[0][2] + " | " +
            system_to_print[3][0] + system_separetion[0][3] +'\n';
    solution_text +=system_to_print[0][1] + ' ' + system_separetion[1][0] +
            system_to_print[1][1] + ' ' + system_separetion[1][1] +
            system_to_print[2][1] + system_separetion[1][2] + " | " +
            system_to_print[3][1] + system_separetion[1][3] +'\n';
    solution_text +=system_to_print[0][2] + ' ' + system_separetion[2][0] +
            system_to_print[1][2] + ' ' + system_separetion[2][1] +
            system_to_print[2][2] + system_separetion[2][2] + " | " +
            system_to_print[3][2] + system_separetion[2][3] +"\n\n\n";
}

void Solution::print_matrix(double matrix[3][3]){
    QString matrix_to_print[3][3];
    QString matrix_separetion[3][3];
    int max_size[3];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(matrix[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                matrix_separetion[i][j] += ' ';
            }
        }
    }
    solution_text +=matrix_to_print[0][0] + ' ' + matrix_separetion[0][0] +
            matrix_to_print[1][0] + ' ' + matrix_separetion[0][1] +
            matrix_to_print[2][0] + matrix_separetion[0][2] +'\n';
    solution_text +=matrix_to_print[0][1] + ' ' + matrix_separetion[1][0] +
            matrix_to_print[1][1] + ' ' + matrix_separetion[1][1] +
            matrix_to_print[2][1] + matrix_separetion[1][2] + '\n';
    solution_text +=matrix_to_print[0][2] + ' ' + matrix_separetion[2][0] +
            matrix_to_print[1][2] + ' ' + matrix_separetion[2][1] +
            matrix_to_print[2][2] + matrix_separetion[2][2] +"\n\n\n";
}

double Solution::determinant(double matrix[3][3]){
    return matrix[0][0] * matrix[1][1] * matrix[2][2] +
           matrix[0][1] * matrix[1][2] * matrix[2][0] +
           matrix[1][0] * matrix[2][1] * matrix[0][2] -
           matrix[0][2] * matrix[1][1] * matrix[2][0] -
           matrix[0][1] * matrix[1][0] * matrix[2][2] -
           matrix[0][0] * matrix[1][2] * matrix[2][1];
}

void Solution::gauss(double coefs[3][3], double terms[3]){
    setWindowTitle("Решение методом Гаусса");
    double matrix_tmp[3][3];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_tmp[i][j] = coefs[i][j];
        }
    }
    QString matrix_to_print[3][3];
    QString separetion[3][3];
    int max_size[3];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(matrix_tmp[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separetion[i][j] += ' ';
            }
        }
    }
    double base_det = determinant(matrix_tmp);
    solution_text += "      |" + matrix_to_print[0][0] + ' ' + separetion[0][0] +
            matrix_to_print[1][0] + ' ' + separetion[0][1] +
            matrix_to_print[2][0] + separetion[0][2] + "|\n";
    solution_text += "det = |" + matrix_to_print[0][1] +
            ' ' + separetion[1][0] + matrix_to_print[1][1] + ' ' + separetion[1][1] +
            matrix_to_print[2][1] + separetion[1][2] +"| = " + double_to_str(base_det) + '\n';
    solution_text += "      |" + matrix_to_print[0][2] +
            ' ' + separetion[2][0] + matrix_to_print[1][2] + ' ' + separetion[2][1] +
            matrix_to_print[2][2] + separetion[2][2] + "|\n\n\n";
    if (base_det == 0){
        solution_text += "det = 0 => система не определена или несовместна";
        ui->solutionBrowser->setText(solution_text);
        return;
    } else {
        solution_text += "det != 0 => система определена\n\n";
    }
    solution_text += "Преобразуем матрицу:\n";
    if (matrix_tmp[0][0] == 0){
        if (matrix_tmp[0][1] != 0){
            double tmp1 = matrix_tmp[0][1], tmp2 = matrix_tmp[1][1], tmp3 = matrix_tmp[2][1], tmp4 = terms[1];
            matrix_tmp[0][1] = matrix_tmp[0][0];
            matrix_tmp[1][1] = matrix_tmp[1][0];
            matrix_tmp[2][1] = matrix_tmp[2][0];
            terms[1] = terms[0];
            matrix_tmp[0][0] = tmp1;
            matrix_tmp[1][0] = tmp2;
            matrix_tmp[2][0] = tmp3;
            terms[0] = tmp4;
        } else {
            double tmp1 = matrix_tmp[0][2], tmp2 = matrix_tmp[1][2], tmp3 = matrix_tmp[2][2], tmp4 = terms[2];
            matrix_tmp[0][2] = matrix_tmp[0][0];
            matrix_tmp[1][2] = matrix_tmp[1][0];
            matrix_tmp[2][2] = matrix_tmp[2][0];
            terms[2] = terms[0];
            matrix_tmp[0][0] = tmp1;
            matrix_tmp[1][0] = tmp2;
            matrix_tmp[2][0] = tmp3;
            terms[0] = tmp4;
        }
        print_system(matrix_tmp, terms);
    }
    if (matrix_tmp[0][1] != 0) {
        double lambda = matrix_tmp[0][1] / matrix_tmp[0][0];
        matrix_tmp[0][1] = 0;
        matrix_tmp[1][1] -= lambda * matrix_tmp[1][0];
        matrix_tmp[2][1] -= lambda * matrix_tmp[2][0];
        terms[1] -= lambda * terms[0];
        print_system(matrix_tmp, terms);
    }
    if (matrix_tmp[0][2] != 0) {
        double lambda = matrix_tmp[0][2] / matrix_tmp[0][0];
        matrix_tmp[0][2] = 0;
        matrix_tmp[1][2] -= lambda * matrix_tmp[1][0];
        matrix_tmp[2][2] -= lambda * matrix_tmp[2][0];
        terms[2] -= lambda * terms[0];
        print_system(matrix_tmp, terms);
    }
    if (matrix_tmp[1][2] != 0) {
        double lambda = matrix_tmp[1][2] / matrix_tmp[1][1];
        matrix_tmp[1][2] = 0;
        matrix_tmp[2][2] -= lambda * matrix_tmp[2][1];
        terms[2] -= lambda * terms[1];
        print_system(matrix_tmp, terms);
    }
    if (matrix_tmp[2][1] != 0){
        double lambda = matrix_tmp[2][1] / matrix_tmp[2][2];
        matrix_tmp[2][1] = 0;
        terms[1] -= lambda * terms[2];
        print_system(matrix_tmp, terms);
    }
    if (matrix_tmp[2][0] != 0){
        double lambda = matrix_tmp[2][0] / matrix_tmp[2][2];
        matrix_tmp[2][0] = 0;
        terms[0] -= lambda * terms[2];
        print_system(matrix_tmp, terms);
    }
    if (matrix_tmp[1][0] != 0){
        double lambda = matrix_tmp[1][0] / matrix_tmp[1][1];
        matrix_tmp[1][0] = 0;
        terms[0] -= lambda * terms[1];
        print_system(matrix_tmp, terms);
    }
    solution_text += "X = " + double_to_str(terms[0]/matrix_tmp[0][0]) +
            "\nY = " + double_to_str(terms[1]/matrix_tmp[1][1]) +
            "\nZ = " + double_to_str(terms[2]/matrix_tmp[2][2]);
    ui->solutionBrowser->setText(solution_text);
}

void Solution::cramer(double coefs[3][3], double terms[3]){
    setWindowTitle("Решение методом Крамера");
    double matrix_tmp[3][3];
    QString matrix_to_print[3][3];
    QString separetion[3][3];
    int max_size[3];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_tmp[i][j] = coefs[i][j];
        }
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(matrix_tmp[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separetion[i][j] += ' ';
            }
        }
    }
    double base_det = determinant(matrix_tmp);
    solution_text += "      |" + matrix_to_print[0][0] + ' ' + separetion[0][0] +
            matrix_to_print[1][0] + ' ' + separetion[0][1] +
            matrix_to_print[2][0] + separetion[0][2] + "|\n";
    solution_text += "det = |" + matrix_to_print[0][1] +
            ' ' + separetion[1][0] + matrix_to_print[1][1] + ' ' + separetion[1][1] +
            matrix_to_print[2][1] + separetion[1][2] +"| = " + double_to_str(base_det) + '\n';
    solution_text += "      |" + matrix_to_print[0][2] +
            ' ' + separetion[2][0] + matrix_to_print[1][2] + ' ' + separetion[2][1] +
            matrix_to_print[2][2] + separetion[2][2] + "|\n\n\n";
    for (int i = 0; i < 3; ++i){
        matrix_tmp[0][i] = terms[i];
    }
    double det1 = determinant(matrix_tmp);
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(matrix_tmp[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separetion[i][j] += ' ';
            }
        }
    }
    solution_text += "       |" + matrix_to_print[0][0] + ' ' + separetion[0][0] +
            matrix_to_print[1][0] + ' ' + separetion[0][1] +
            matrix_to_print[2][0] + separetion[0][2] + "|\n";
    solution_text += "det1 = |" + matrix_to_print[0][1] +
            ' ' + separetion[1][0] + matrix_to_print[1][1] + ' ' + separetion[1][1] +
            matrix_to_print[2][1] + separetion[1][2] +"| = " + double_to_str(det1) + '\n';
    solution_text += "       |" + matrix_to_print[0][2] +
            ' ' + separetion[2][0] + matrix_to_print[1][2] + ' ' + separetion[2][1] +
            matrix_to_print[2][2] + separetion[2][2] + "|\n\n\n";
    for (int i = 0; i < 3; ++i){
        matrix_tmp[0][i] = coefs[0][i];
    }
    for (int i = 0; i < 3; ++i){
        matrix_tmp[1][i] = terms[i];
    }
    double det2 = determinant(matrix_tmp);
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(matrix_tmp[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separetion[i][j] += ' ';
            }
        }
    }
    solution_text += "       |" + matrix_to_print[0][0] + ' ' + separetion[0][0] +
            matrix_to_print[1][0] + ' ' + separetion[0][1] +
            matrix_to_print[2][0] + separetion[0][2] + "|\n";
    solution_text += "det2 = |" + matrix_to_print[0][1] +
            ' ' + separetion[1][0] + matrix_to_print[1][1] + ' ' + separetion[1][1] +
            matrix_to_print[2][1] + separetion[1][2] +"| = " + double_to_str(det2) + '\n';
    solution_text += "       |" + matrix_to_print[0][2] +
            ' ' + separetion[2][0] + matrix_to_print[1][2] + ' ' + separetion[2][1] +
            matrix_to_print[2][2] + separetion[2][2] + "|\n\n\n";
    for (int i = 0; i < 3; ++i){
        matrix_tmp[1][i] = coefs[1][i];
    }
    for (int i = 0; i < 3; ++i){
        matrix_tmp[2][i] = terms[i];
    }
    double det3 = determinant(matrix_tmp);
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(matrix_tmp[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separetion[i][j] += ' ';
            }
        }
    }
    solution_text += "       |" + matrix_to_print[0][0] + ' ' + separetion[0][0] +
            matrix_to_print[1][0] + ' ' + separetion[0][1] +
            matrix_to_print[2][0] + separetion[0][2] + "|\n";
    solution_text += "det3 = |" + matrix_to_print[0][1] +
            ' ' + separetion[1][0] + matrix_to_print[1][1] + ' ' + separetion[1][1] +
            matrix_to_print[2][1] + separetion[1][2] +"| = " + double_to_str(det3) + '\n';
    solution_text += "       |" + matrix_to_print[0][2] +
            ' ' + separetion[2][0] + matrix_to_print[1][2] + ' ' + separetion[2][1] +
            matrix_to_print[2][2] + separetion[2][2] + "|\n\n\n";
    if (base_det != 0){
        solution_text += "X = det1/det = " + double_to_str(det1/base_det);
        solution_text += "\nY = det2/det = " + double_to_str(det2/base_det);
        solution_text += "\nZ = det3/det = " + double_to_str(det3/base_det);
    } else if (det1 == 0 && det2 == 0 && det3 == 0){
        solution_text += "det = 0; det1 = 0; det2 = 0; det3 = 0 => система не определена";
    } else{
        solution_text += "det = 0 и хотя бы одна из det1, det2, det3 не равна нулю => система несовместна";
    }
    ui->solutionBrowser->setText(solution_text);
}

void Solution::inverse_matrix(double coefs[3][3], double terms[3]){
    setWindowTitle("Решение методом обратной матрицы");
    double matrix_tmp[3][3];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_tmp[i][j] = coefs[i][j];
        }
    }
    QString matrix_to_print[3][3];
    QString separetion[3][3];
    int max_size[3];
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(matrix_tmp[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separetion[i][j] += ' ';
            }
        }
    }
    double base_det = determinant(matrix_tmp);
    solution_text += "      |" + matrix_to_print[0][0] + ' ' + separetion[0][0] +
            matrix_to_print[1][0] + ' ' + separetion[0][1] +
            matrix_to_print[2][0] + separetion[0][2] + "|\n";
    solution_text += "det = |" + matrix_to_print[0][1] +
            ' ' + separetion[1][0] + matrix_to_print[1][1] + ' ' + separetion[1][1] +
            matrix_to_print[2][1] + separetion[1][2] +"| = " + double_to_str(base_det) + '\n';
    solution_text += "      |" + matrix_to_print[0][2] +
            ' ' + separetion[2][0] + matrix_to_print[1][2] + ' ' + separetion[2][1] +
            matrix_to_print[2][2] + separetion[2][2] + "|\n\n\n";
    if (base_det == 0){
        solution_text += "det = 0 => система не определена или несовместна";
        ui->solutionBrowser->setText(solution_text);
        return;
    } else {
        solution_text += "det != 0 => система определена\n\n";
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_tmp[i][j] = coefs[j][i];
        }
    }
    solution_text += "Транспонированная матрица:\n";
    print_matrix(matrix_tmp);
    solution_text += "Алгебраические дополнения:\n";
    double alg_dops[3][3];
    double current_alg_dop[2][2];
    current_alg_dop[0][0] = matrix_tmp[1][1]; current_alg_dop[1][0] = matrix_tmp[2][1];
    current_alg_dop[0][1] = matrix_tmp[1][2]; current_alg_dop[1][1] = matrix_tmp[2][2];
    alg_dops[0][0] = print_alg_dop(1, 1, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[0][1]; current_alg_dop[1][0] = matrix_tmp[2][1];
    current_alg_dop[0][1] = matrix_tmp[0][2]; current_alg_dop[1][1] = matrix_tmp[2][2];
    alg_dops[1][0] = print_alg_dop(1, 2, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[0][1]; current_alg_dop[1][0] = matrix_tmp[1][1];
    current_alg_dop[0][1] = matrix_tmp[0][2]; current_alg_dop[1][1] = matrix_tmp[1][2];
    alg_dops[2][0] = print_alg_dop(1, 3, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[1][0]; current_alg_dop[1][0] = matrix_tmp[2][0];
    current_alg_dop[0][1] = matrix_tmp[1][2]; current_alg_dop[1][1] = matrix_tmp[2][2];
    alg_dops[0][1] = print_alg_dop(2, 1, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[0][0]; current_alg_dop[1][0] = matrix_tmp[2][0];
    current_alg_dop[0][1] = matrix_tmp[0][2]; current_alg_dop[1][1] = matrix_tmp[2][2];
    alg_dops[1][1] = print_alg_dop(2, 2, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[0][0]; current_alg_dop[1][0] = matrix_tmp[1][0];
    current_alg_dop[0][1] = matrix_tmp[0][2]; current_alg_dop[1][1] = matrix_tmp[1][2];
    alg_dops[2][1] = print_alg_dop(2, 3, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[1][0]; current_alg_dop[1][0] = matrix_tmp[2][0];
    current_alg_dop[0][1] = matrix_tmp[1][1]; current_alg_dop[1][1] = matrix_tmp[2][1];
    alg_dops[0][2] = print_alg_dop(3, 1, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[0][0]; current_alg_dop[1][0] = matrix_tmp[2][0];
    current_alg_dop[0][1] = matrix_tmp[0][1]; current_alg_dop[1][1] = matrix_tmp[2][1];
    alg_dops[1][2] = print_alg_dop(3, 2, current_alg_dop);

    current_alg_dop[0][0] = matrix_tmp[0][0]; current_alg_dop[1][0] = matrix_tmp[1][0];
    current_alg_dop[0][1] = matrix_tmp[0][1]; current_alg_dop[1][1] = matrix_tmp[1][1];
    alg_dops[2][2] = print_alg_dop(3, 3, current_alg_dop);
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            alg_dops[i][j] /= base_det;
        }
    }
    solution_text += "Обратная матрица:\n";
    print_matrix(alg_dops);
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            matrix_to_print[i][j] = double_to_str(alg_dops[i][j]);
        }
    }
    for (int i = 0; i < 3; ++i){
        max_size[i] = std::max({matrix_to_print[i][0].length(),
                matrix_to_print[i][1].length(),
                matrix_to_print[i][2].length()});
    }
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            separetion[i][j] = "";
            for (int k = 0; k < max_size[j] - matrix_to_print[j][i].length(); ++k){
                separetion[i][j] += ' ';
            }
        }
    }
    QString terms_to_print[3];
    for (int i = 0; i < 3; ++i){
        terms_to_print[i] = double_to_str(terms[i]);
    }
    double max_term = std::max({terms_to_print[0].length(),
                                 terms_to_print[1].length(),
                                 terms_to_print[2].length()});
    QString term_separators[3];
    for(int i = 0; i < 3; ++i){
        for (int j = 0; j < max_term - terms_to_print[i].length(); ++j){
            term_separators[i] += ' ';
        }
    }
    double answer[3];
    for (int i = 0; i < 3; ++i){
        answer[i] = 0;
        for (int j = 0; j < 3; ++j){
            answer[i] += terms[j] * alg_dops[j][i];
        }
    }
    solution_text += "Умножим получившуюся матрицу на вектор свободных членов:\n";
    solution_text +=matrix_to_print[0][0] + ' ' + separetion[0][0] +
            matrix_to_print[1][0] + ' ' + separetion[0][1] +
            matrix_to_print[2][0] + separetion[0][2] +
            "   " + terms_to_print[0] + term_separators[0] + "   " +double_to_str(answer[0]) +'\n';
    solution_text +=matrix_to_print[0][1] + ' ' + separetion[1][0] +
            matrix_to_print[1][1] + ' ' + separetion[1][1] +
            matrix_to_print[2][1] + separetion[1][2] +
            " * " + terms_to_print[1] + term_separators[1] + " = " + double_to_str(answer[1]) + '\n';
    solution_text +=matrix_to_print[0][2] + ' ' + separetion[2][0] +
            matrix_to_print[1][2] + ' ' + separetion[2][1] +
            matrix_to_print[2][2] + separetion[2][2] +
            "   " + terms_to_print[2] + term_separators[2] + "   " + double_to_str(answer[2]) + "\n\n\n";
    solution_text += "X = " + double_to_str(answer[0]) + "; Y = " + double_to_str(answer[1]) + ": Z = " + double_to_str(answer[2]);
    ui->solutionBrowser->setText(solution_text);
}

void Solution::save_to_file(){
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Сохранить решение"), "",
           tr("Text File (*.txt);;All Files (*)"));
    if (fileName.isEmpty()){
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        file.write(solution_text.toUtf8());
    }
}

void Solution::close(){
    Solution::~Solution();
}

Solution::~Solution()
{
    delete ui;
}
