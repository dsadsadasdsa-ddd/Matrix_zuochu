#ifndef MATRIX_ZUOCHU_H
#define MATRIX_ZUOCHU_H

#include <QWidget>
#include "eigen3/Eigen/Eigen"
#include <iostream>
#include "eigen3/Eigen/Dense"
#include <Eigen/core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <QList>
#include<Eigen/SVD>
#include <math.h>
#include <vector>
#include <string>
#include <QList>
#include <QStringList>
#include <QFile>

using namespace std;

using namespace Eigen;

namespace Ui {
class Matrix_zuochu;
}

class Matrix_zuochu : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix_zuochu(QWidget *parent = 0);
    ~Matrix_zuochu();



public:
    QList<double>data_list_d;//返回的d矩阵

    Matrix <double,6840,1>d;//创建一个d矩阵


    QList<double>data_list_Hj_1;//  Hj的第一行
    QList<double>data_list_Hj_2;//  Hj的第二行
    QList<double>data_list_Hj_3;//  Hj的第三行
    QList<double>data_list_Hj_4;//  Hj的第四行
    QList<double>data_list_Hj_5;//  Hj的第五行
    QList<double>data_list_Hj_6;//  Hj的第六行
    QList<double>data_list_Hj_7;//  Hj的第七行
    QList<double>data_list_Hj_8;//  Hj的第八行
    QList<double>data_list_Hj_9;//  Hj的第九行
    // Matrix <double,6840,3>Hj;//创建一个Hj矩阵


    Matrix <double,9,1>XM_matrix;//创建一个xm矩阵


    //读取txt数据
    QStringList list_d;
    QList<double>List_data_d;

    QStringList list_Hj_1;
    QList<double>List_data_Hj_1;

    QStringList list_Hj_2;
    QList<double>List_data_Hj_2;

    QStringList list_Hj_3;
    QList<double>List_data_Hj_3;

    QStringList list_Hj_4;
    QList<double>List_data_Hj_4;

    QStringList list_Hj_5;
    QList<double>List_data_Hj_5;

    QStringList list_Hj_6;
    QList<double>List_data_Hj_6;

    QStringList list_Hj_7;
    QList<double>List_data_Hj_7;

    QStringList list_Hj_8;
    QList<double>List_data_Hj_8;

    QStringList list_Hj_9;
    QList<double>List_data_Hj_9;






private slots:
    void on_btn_zuochu_clicked();

    void on_btn_get_matrix_clicked();

    void on_btn_read_txt_Data_clicked();

private:
    Ui::Matrix_zuochu *ui;
};

#endif // MATRIX_ZUOCHU_H
