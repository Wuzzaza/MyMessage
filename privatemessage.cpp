#include "privatemessage.h"
#include "ui_privatemessage.h"

PrivateMessage::PrivateMessage(QWidget *parent, QString toUser, NetworkManager *networkManager) :
    QWidget(parent),
    ui(new Ui::PrivateMessage)
{
    ui->setupUi(this);
    this->setFixedSize(400, 300);
    this->setWindowTitle(toUser);
    this->networkManager = networkManager;


}

PrivateMessage::~PrivateMessage()
{
    delete ui;
}
