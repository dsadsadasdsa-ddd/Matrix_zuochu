#include "matrix_zuochu.h"
#include "ui_matrix_zuochu.h"
#include <QDebug>



template<typename _Matrix_Type_>
_Matrix_Type_ pseudoInverse(const _Matrix_Type_ &a, double epsilon =
        std::numeric_limits<double>::epsilon())
{
    Eigen::JacobiSVD< _Matrix_Type_ > svd(a ,Eigen::ComputeThinU | Eigen::ComputeThinV);
    double tolerance = epsilon * std::max(a.cols(), a.rows()) *svd.singularValues().array().abs()(0);
    return svd.matrixV() *  (svd.singularValues().array().abs() > tolerance).select(svd.singularValues().array().inverse(), 0).matrix().asDiagonal() * svd.matrixU().adjoint();
}


Matrix_zuochu::Matrix_zuochu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix_zuochu)
{
    ui->setupUi(this);

    //初始化数据
    for(int i=0;i<6840;i++)
    {
        data_list_d.push_back(i);
    }


    for(int i=0;i<6840;i++)
    {
        data_list_Hj_1.push_back(i);
    }



    for(int i=0;i<6840;i++)
    {
        data_list_Hj_2.push_back(2);
    }



    for(int i=0;i<6840;i++)
    {
        data_list_Hj_3.push_back(3);
    }

    for(int i=0;i<6840;i++)
    {
        data_list_Hj_4.push_back(4);
    }

    for(int i=0;i<6840;i++)
    {
        data_list_Hj_5.push_back(5);
    }

    for(int i=0;i<6840;i++)
    {
        data_list_Hj_6.push_back(6);
    }

    for(int i=0;i<6840;i++)
    {
        data_list_Hj_7.push_back(7);
    }

    for(int i=0;i<6840;i++)
    {
        data_list_Hj_8.push_back(8);
    }

    for(int i=0;i<6840;i++)
    {
        data_list_Hj_9.push_back(9);
    }


    // ui->btn_zuochu->setEnabled(false);
    ui->btn_get_matrix->setEnabled(false);

}

Matrix_zuochu::~Matrix_zuochu()
{
    delete ui;
}

//左除
void Matrix_zuochu::on_btn_zuochu_clicked()
{

    MatrixXf A1 = MatrixXf::Random(3, 2);
    std::cout << "Here is the matrix A:\n" << A1 << std::endl;
    VectorXf b1 = VectorXf::Random(3);
    std::cout << "Here is the right hand side b:\n" << b1 << std::endl;
    //jacobiSvd 方式:Slow (but fast for small matrices)
    std::cout << "The least-squares solution is:\n"
              << A1.jacobiSvd(ComputeThinU | ComputeThinV).solve(b1) << std::endl;
    //colPivHouseholderQr方法:fast
    std::cout << "The least-squares solution is:\n"
              << A1.colPivHouseholderQr().solve(b1) << std::endl;

}
//获取数据
void Matrix_zuochu::on_btn_get_matrix_clicked()
{
    //获取datalist中的数据
    for(int i=0;i<6840;i++)
    {
        for(int j=0;j<1;j++)
        {
            d(i,j)=(i,List_data_d.at(i));
        }
    }





    Eigen::MatrixXd Hj(6840,9);



    cout<<Hj.size()<<endl;
    cout<<Hj.rows()<<endl;
    cout<<Hj.cols()<<endl;

    //获取datalist中的数据
    for(int i=0;i<6840;i++)
    {
        for(int j=0;j<1;j++)
        {
            Hj(i,j)=(i,List_data_Hj_1.at(i));
        }

        for(int j=1;j<2;j++)
        {
            Hj(i,j)=(i,List_data_Hj_2.at(i));
        }


        for(int j=2;j<3;j++)
        {
            Hj(i,j)=(i,List_data_Hj_3.at(i));
        }

        for(int j=3;j<4;j++)
        {
            Hj(i,j)=(i,List_data_Hj_4.at(i));
        }

        for(int j=4;j<5;j++)
        {
            Hj(i,j)=(i,List_data_Hj_5.at(i));
        }

        for(int j=5;j<6;j++)
        {
            Hj(i,j)=(i,List_data_Hj_6.at(i));
        }

        for(int j=6;j<7;j++)
        {
            Hj(i,j)=(i,List_data_Hj_7.at(i));
        }

        for(int j=7;j<8;j++)
        {
            Hj(i,j)=(i,List_data_Hj_8.at(i));
        }

        for(int j=8;j<9;j++)
        {
            Hj(i,j)=(i,List_data_Hj_9.at(i));
        }

    }

    cout<<"d="<<endl<<d<<endl;
    cout<<"Hj="<<endl<<Hj<<endl;


    //    cout<<"Pinv(Hj)="<<endl<<pseudoInverse(Hj)<<endl;

    //    Eigen::MatrixXd Hj_pinv(9,6840);

    //    Hj_pinv=pseudoInverse(Hj);


    //    cout<<"Hj*d="<<endl<<Hj_pinv*d<<endl;

    std::cout << "The least-squares solution is:\n"
              << Hj.jacobiSvd(ComputeThinU | ComputeThinV).solve(d) << std::endl;


    ui->btn_zuochu->setEnabled(true);
}




void Matrix_zuochu::on_btn_read_txt_Data_clicked()
{
    QFile file_d("b.txt");
    QFile file_Hj_1("Hj_1.txt");
    QFile file_Hj_2("Hj_2.txt");
    QFile file_Hj_3("Hj_3.txt");
    QFile file_Hj_4("Hj_4.txt");
    QFile file_Hj_5("Hj_5.txt");
    QFile file_Hj_6("Hj_6.txt");
    QFile file_Hj_7("Hj_7.txt");
    QFile file_Hj_8("Hj_8.txt");
    QFile file_Hj_9("Hj_9.txt");

    //d矩阵
    if (file_d.open(QIODevice::ReadOnly))
    {
        while (!file_d.atEnd())
        {
            bool ok;
            list_d<<file_d.readLine();
            ui->Edit_show_of_result->append(list_d.at(list_d.length()-1));
            QString temp_string=list_d.at(list_d.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_d.push_back(temp);
        }

        file_d.close();
    }

    //    for(int i=0;i<list_d.length();i++)
    //    {
    //        qDebug()<<"list_d="<<list_d.at(i);
    //    }


    //    for(int i=0;i<List_data_d.length();i++)
    //    {
    //        qDebug()<<"List_data_d="<<List_data_d.at(i);
    //    }



    //Hj_1矩阵
    if (file_Hj_1.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_1.atEnd())
        {
            bool ok;
            list_Hj_1<<file_Hj_1.readLine();
            ui->Edit_show_of_result->append(list_Hj_1.at(list_Hj_1.length()-1));
            QString temp_string=list_Hj_1.at(list_Hj_1.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_1.push_back(temp);
        }

        file_Hj_1.close();
    }

    //Hj_2矩阵
    if (file_Hj_2.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_2.atEnd())
        {
            bool ok;
            list_Hj_2<<file_Hj_2.readLine();
            ui->Edit_show_of_result->append(list_Hj_2.at(list_Hj_2.length()-1));
            QString temp_string=list_Hj_2.at(list_Hj_2.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_2.push_back(temp);
        }

        file_Hj_2.close();
    }

    //Hj_3矩阵
    if (file_Hj_3.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_3.atEnd())
        {
            bool ok;
            list_Hj_3<<file_Hj_3.readLine();
            ui->Edit_show_of_result->append(list_Hj_3.at(list_Hj_3.length()-1));
            QString temp_string=list_Hj_3.at(list_Hj_3.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_3.push_back(temp);
        }

        file_Hj_3.close();
    }


    //Hj_4矩阵
    if (file_Hj_4.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_4.atEnd())
        {
            bool ok;
            list_Hj_4<<file_Hj_4.readLine();
            ui->Edit_show_of_result->append(list_Hj_4.at(list_Hj_4.length()-1));
            QString temp_string=list_Hj_4.at(list_Hj_4.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_4.push_back(temp);
        }

        file_Hj_4.close();
    }


    //Hj_5矩阵
    if (file_Hj_5.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_5.atEnd())
        {
            bool ok;
            list_Hj_5<<file_Hj_5.readLine();
            ui->Edit_show_of_result->append(list_Hj_5.at(list_Hj_5.length()-1));
            QString temp_string=list_Hj_5.at(list_Hj_5.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_5.push_back(temp);
        }

        file_Hj_5.close();
    }





    //Hj_6矩阵
    if (file_Hj_6.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_6.atEnd())
        {
            bool ok;
            list_Hj_6<<file_Hj_6.readLine();
            ui->Edit_show_of_result->append(list_Hj_6.at(list_Hj_6.length()-1));
            QString temp_string=list_Hj_6.at(list_Hj_6.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_6.push_back(temp);
        }

        file_Hj_6.close();
    }


    //Hj_7矩阵
    if (file_Hj_7.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_7.atEnd())
        {
            bool ok;
            list_Hj_7<<file_Hj_7.readLine();
            ui->Edit_show_of_result->append(list_Hj_7.at(list_Hj_7.length()-1));
            QString temp_string=list_Hj_7.at(list_Hj_7.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_7.push_back(temp);
        }

        file_Hj_7.close();
    }



    //Hj_8矩阵
    if (file_Hj_8.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_8.atEnd())
        {
            bool ok;
            list_Hj_8<<file_Hj_8.readLine();
            ui->Edit_show_of_result->append(list_Hj_8.at(list_Hj_8.length()-1));
            QString temp_string=list_Hj_8.at(list_Hj_8.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_8.push_back(temp);
        }

        file_Hj_8.close();
    }



    //Hj_9矩阵
    if (file_Hj_9.open(QIODevice::ReadOnly))
    {
        while (!file_Hj_9.atEnd())
        {
            bool ok;
            list_Hj_9<<file_Hj_9.readLine();
            ui->Edit_show_of_result->append(list_Hj_9.at(list_Hj_9.length()-1));
            QString temp_string=list_Hj_9.at(list_Hj_9.length()-1);
            double temp=temp_string.toDouble(&ok);
            // qDebug()<<"temp="<<temp;
            List_data_Hj_9.push_back(temp);
        }

        file_Hj_9.close();
    }



    qDebug()<<"List_data_d length="<<List_data_d.length();
    qDebug()<<"List_data_Hj_1="<<List_data_Hj_1.length();
    qDebug()<<"List_data_Hj_2="<<List_data_Hj_2.length();
    qDebug()<<"List_data_Hj_3="<<List_data_Hj_3.length();
    qDebug()<<"List_data_Hj_4="<<List_data_Hj_4.length();
    qDebug()<<"List_data_Hj_5="<<List_data_Hj_5.length();
    qDebug()<<"List_data_Hj_6="<<List_data_Hj_6.length();
    qDebug()<<"List_data_Hj_7="<<List_data_Hj_7.length();
    qDebug()<<"List_data_Hj_8="<<List_data_Hj_8.length();
    qDebug()<<"List_data_Hj_9="<<List_data_Hj_9.length();
    qDebug()<<"data_input_ok";

    ui->btn_get_matrix->setEnabled(true);

}
