#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sqlite_create_open_db();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sqlite_create_open_db(){
    //此处的第一个参数为所调用的数据库，因为在QT中有QMYSQL，QODBC等数据库，所以在此需要声明，第二个参数为本地数据库的路径和名字，如果在某个文件夹下，可以如下写:res\note.db
    m_db =QSqlDatabase::addDatabase("QSQLITE");

    // 打开数据库
    m_db.setDatabaseName("./dataBase.db");
    if(m_db.isOpen() != true){
        m_db.open();//此处可以添加bool变量判断打开状态
    }

    m_query=QSqlQuery(m_db);//声明Query语句，方便以后的调用，并且绑定数据库为m_db

    /*bool ok = m_query.exec("CREATE TABLE IF NOT EXISTS  people (id VARCHAR(20) PRIMARY KEY AUTOINCREMENT,"
                                           "name VARCHAR(20) NOT NULL,"
                                           "age INTEGER NULL)");*/

    bool ok = m_query.exec("CREATE TABLE IF NOT EXISTS  people (id VARCHAR(20) PRIMARY KEY,"
                                           "name VARCHAR(20) NOT NULL,"
                                           "age INTEGER NULL)");

    if (ok)
        {
            qDebug()<<"ceate table partition success/n";
        }
        else
        {
            qDebug()<<"ceate table partition failed/n";
        }
        for (int i = 0; i< 20; ++i)
        {
            m_query.prepare("INSERT INTO people (id, name, age) VALUES (:id, :name, :age)");
            m_query.bindValue(":id", QString("2016313%1").arg(i+1));
            m_query.bindValue(":name", QString("smith_%1").arg(i+1));
            m_query.bindValue(":age", 20+i*5);
            m_query.exec();
        }

  //    QSqlQuery query;
        m_query.exec("SELECT id, name, age FROM people");
        while (m_query.next())
        {
            qDebug()<<"people("<<m_query.value(0).toInt()<<")  name:"<<m_query.value(1).toString()<<"  age:"<<m_query.value(2).toInt();
        }
}
