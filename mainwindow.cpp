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

    networkManager = new NetworkManager (this, userName);

    connect(networkManager, SIGNAL(messageRecieved(int,QString)), this, SLOT(messageRecieved(int,QString)));
    connect(networkManager, SIGNAL(userNickChanged(int,QString)), this, SLOT(userNickChanged(int,QString)));
    connect(networkManager, SIGNAL(connectedToServer()), this, SLOT(connectedToServer()));
    connect(networkManager, SIGNAL(connectingToServer()), this, SLOT(connectingToServer()));
    ui->textEdit->insertPlainText(QDate::currentDate().toString());
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
    if (users[ui->listWidget->item(ui->listWidget->currentRow())->toolTip().toInt()]->privateWindow == NULL){
    PrivateMessage *privateMsgWindow = new PrivateMessage(NULL, "To: " + ui->listWidget->item(ui->listWidget->currentRow())->text());
    users[ui->listWidget->item(ui->listWidget->currentRow())->toolTip().toInt()]->privateWindow = privateMsgWindow;}
    users[ui->listWidget->item(ui->listWidget->currentRow())->toolTip().toInt()]->privateWindow->show();
    qDebug() << ui->listWidget->item(ui->listWidget->currentRow())->text();

}

void MainWindow::on_lineEdit_returnPressed()
{
    networkManager->SendAllMessage(ui->lineEdit->text());
    emit messageRecieved(0, ui->lineEdit->text());
    ui->lineEdit->clear();
}

void MainWindow::messageRecieved(int Id, QString message)
{
    addNewUser(Id);
    QString newMessageSender = (Id == 0) ? "Me: " : ("From " + users[Id]->userName.text()+ ": ");
    QString newMessage = "<br/><b>" + newMessageSender + "</b>";
    newMessage += "(" + QTime::currentTime().toString();
    newMessage += "): " + message;
    newMessage += "<br/>";

    ui->textEdit->insertHtml(newMessage);
}

void MainWindow::userNickChanged(int Id, QString message)
{
    addNewUser(Id);
    users[Id]->userName.setText(message);

}
void MainWindow::addNewUser(int uniqueId)
{
    if (uniqueId == 0)return;
    if(!users.contains(uniqueId)){
    chatUser *newUser = new chatUser();
    newUser->userName.setText(QString::number(uniqueId));
    newUser->userName.setToolTip(QString::number(uniqueId));

    users[uniqueId] = newUser;

    ui->listWidget->addItem(&newUser->userName);

    }
}

void MainWindow::connectedToServer()
{
    ui->statusBar->showMessage("Connected");
}

void MainWindow::connectingToServer()
{
    ui->statusBar->showMessage("Connecting...");
}
