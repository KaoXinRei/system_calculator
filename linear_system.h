#ifndef SYSTEM_H
#define SYSTEM_H
#include <QString>

class linear_system
{
public:
    linear_system();
    linear_system(QString[3][3], QString[3], QString);
    QString get_coefX1();
    QString get_coefX2();
    QString get_coefX3();
    QString get_coefY1();
    QString get_coefY2();
    QString get_coefY3();
    QString get_coefZ1();
    QString get_coefZ2();
    QString get_coefZ3();
    QString get_term1();
    QString get_term2();
    QString get_term3();
    QString get_answer();

private:
    QString coefs[3][3];
    QString terms[3];
    QString answer;
};

#endif // SYSTEM_H
