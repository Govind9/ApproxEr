#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QWebHistory>
#include <QtCore/QFile>
#include <QIODevice>
#include <QtCore/QTextStream>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QWebView *br;
    int t;
    ~MainWindow();

private slots:
    void on_login_clicked();
    void loadComplete();
    void loadComplete2();
    void loadComplete3();

    void on_pushButton_clicked();

    void on_logout_clicked();

    void on_password_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
