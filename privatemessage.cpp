#include "privatemessage.h"
#include "ui_privatemessage.h"

PrivateMessage::PrivateMessage(QWidget *parent, QString toUser) :
    QWidget(parent),
    ui(new Ui::PrivateMessage)
{
    ui->setupUi(this);
    this->setFixedSize(400, 300);
    this->setWindowTitle(toUser);
}

PrivateMessage::~PrivateMessage()
{
    delete ui;
}
