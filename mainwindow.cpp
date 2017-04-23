#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(640, 480);
}

MainWindow::MainWindow(QWidget *parent, QString userName):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(640, 480);
    this->userName = userName;
    QStringList usersList;
    usersList << "Ivanov" << "Petrov" << "Sidorov";
    ui->listWidget->addItems(usersList);
    networkManager = new NetworkManager (this, userName);

}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow:: closeEvent (QCloseEvent *event){
    qDebug() << "MainWindow Closed";
}

void MainWindow::on_listWidget_activated(const QModelIndex &index)
{
    privateMsgWindow = new PrivateMessage(NULL, "To: " + ui->listWidget->item(ui->listWidget->currentRow())->text());
    privateMsgWindow->show();

    qDebug() << ui->listWidget->item(ui->listWidget->currentRow())->text();

}
