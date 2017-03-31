#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSql>//数据库
#include <QSqlDatabase>//数据库
#include <QSqlQuery>//语句
#include <QSqlError>//错误

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase m_db;
    QSqlQuery m_query;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sqlite_create_open_db(void);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
