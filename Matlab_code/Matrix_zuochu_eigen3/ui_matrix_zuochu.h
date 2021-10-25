/********************************************************************************
** Form generated from reading UI file 'matrix_zuochu.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIX_ZUOCHU_H
#define UI_MATRIX_ZUOCHU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Matrix_zuochu
{
public:
    QGridLayout *gridLayout;
    QTextEdit *Edit_show_of_result;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_read_txt_Data;
    QPushButton *btn_zuochu;
    QPushButton *btn_get_matrix;

    void setupUi(QWidget *Matrix_zuochu)
    {
        if (Matrix_zuochu->objectName().isEmpty())
            Matrix_zuochu->setObjectName(QStringLiteral("Matrix_zuochu"));
        Matrix_zuochu->resize(937, 605);
        gridLayout = new QGridLayout(Matrix_zuochu);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Edit_show_of_result = new QTextEdit(Matrix_zuochu);
        Edit_show_of_result->setObjectName(QStringLiteral("Edit_show_of_result"));

        gridLayout->addWidget(Edit_show_of_result, 0, 0, 1, 1);

        widget = new QWidget(Matrix_zuochu);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btn_read_txt_Data = new QPushButton(widget);
        btn_read_txt_Data->setObjectName(QStringLiteral("btn_read_txt_Data"));

        verticalLayout->addWidget(btn_read_txt_Data);

        btn_zuochu = new QPushButton(widget);
        btn_zuochu->setObjectName(QStringLiteral("btn_zuochu"));

        verticalLayout->addWidget(btn_zuochu);

        btn_get_matrix = new QPushButton(widget);
        btn_get_matrix->setObjectName(QStringLiteral("btn_get_matrix"));

        verticalLayout->addWidget(btn_get_matrix);


        gridLayout->addWidget(widget, 0, 1, 1, 1);


        retranslateUi(Matrix_zuochu);

        QMetaObject::connectSlotsByName(Matrix_zuochu);
    } // setupUi

    void retranslateUi(QWidget *Matrix_zuochu)
    {
        Matrix_zuochu->setWindowTitle(QApplication::translate("Matrix_zuochu", "Matrix_zuochu", 0));
        btn_read_txt_Data->setText(QApplication::translate("Matrix_zuochu", "\350\257\273\345\217\226Matlab\346\225\260\346\215\256", 0));
        btn_zuochu->setText(QApplication::translate("Matrix_zuochu", "\351\242\204\347\225\231", 0));
        btn_get_matrix->setText(QApplication::translate("Matrix_zuochu", "\345\267\246\351\231\244", 0));
    } // retranslateUi

};

namespace Ui {
    class Matrix_zuochu: public Ui_Matrix_zuochu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIX_ZUOCHU_H
