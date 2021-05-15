#include "linear_system.h"

linear_system::linear_system(){}

linear_system::linear_system(QString in_coefs[3][3], QString in_terms[3], QString in_answer){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            coefs[i][j] = in_coefs[i][j];
        }
        terms[i] = in_terms[i];
    }
    answer = in_answer;
}

QString linear_system::get_answer(){
    return answer;
}

QString linear_system::get_coefX1(){
    return coefs[0][0];
}

QString linear_system::get_coefX2(){
    return coefs[0][1];
}

QString linear_system::get_coefX3(){
    return coefs[0][2];
}

QString linear_system::get_coefY1(){
    return coefs[1][0];
}

QString linear_system::get_coefY2(){
    return coefs[1][1];
}

QString linear_system::get_coefY3(){
    return coefs[1][2];
}

QString linear_system::get_coefZ1(){
    return coefs[2][0];
}

QString linear_system::get_coefZ2(){
    return coefs[2][1];
}

QString linear_system::get_coefZ3(){
    return coefs[2][2];
}

QString linear_system::get_term1(){
    return terms[0];
}

QString linear_system::get_term2(){
    return terms[1];
}

QString linear_system::get_term3(){
    return terms[2];
}
