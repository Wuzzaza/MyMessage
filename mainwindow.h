#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDebug>
#include "filemanager.h"
#include "privatemessage.h"
#include "networkmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent = 0, QString userName = "");
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_listWidget_activated(const QModelIndex &index);

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QString userName;
    PrivateMessage *privateMsgWindow;
    NetworkManager *networkManager;

};

#endif // MAINWINDOW_H
