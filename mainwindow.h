#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDebug>
#include <QListWidgetItem>
#include "filemanager.h"
#include "privatemessage.h"
#include "networkmanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    struct chatUser{
        QListWidgetItem userName;
        PrivateMessage *privateWindow;
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent = 0, QString userName = "");
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_listWidget_activated(const QModelIndex &index);

    void on_lineEdit_returnPressed();
    void messageRecieved(int Id, QString message);
    void userNickChanged(int Id, QString message);
    void addNewUser(int uniqueId);
    void connectedToServer();
    void connectingToServer();

private:
    Ui::MainWindow *ui;
    QString userName;

    NetworkManager *networkManager;

    QHash<int, chatUser*> users;


};

#endif // MAINWINDOW_H
