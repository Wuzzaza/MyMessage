#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent, QString userName) : QObject(parent)
{
    this->userName = userName;

    reconnectTimer = new QTimer;
    reconnectTimer->setInterval(5000);

    socket = new QTcpSocket(this);

    connect(reconnectTimer, SIGNAL(timeout()), this, SLOT(reconnect()));

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    uniqueID = generateUniqueID();

    reconnectTimer->start();
}

bool NetworkManager::sendMessage(QString message)
{
    if (!(socket->ConnectedState)) return false;
    //TODO

    QByteArray byteArr;
    QDataStream dataStream(&byteArr, QIODevice::WriteOnly);

    dataStream << uniqueID;
    dataStream << userName;
    dataStream << CMD_MESSAGE;
    dataStream << message;

    socket->write(byteArr);

    return true;
}

int NetworkManager::generateUniqueID()
{
    int uniqId = 0;
    while (uniqId == 0) {
        QTime midnight(0,0,0);
        qsrand(midnight.secsTo(QTime::currentTime()));
        uniqId = qrand();
    }

    qDebug()<< "Your uniqID: "<< uniqId;

    return uniqId;

}

void NetworkManager::sayHello()
{
    QByteArray r;
    QDataStream str(&r, QIODevice::WriteOnly);

    str << CMD_HELLO << uniqueID;
    socket->write(r);
    ChangeNick(userName);
}

bool NetworkManager::ChangeNick(QString name) {
    if (socket->state() != QAbstractSocket::ConnectedState)
        return false;

    QByteArray r;
    QDataStream str(&r, QIODevice::WriteOnly);

    str << CMD_CHANGENICK << uniqueID << name;

    socket->write(r);

    return true;
}

void NetworkManager::reconnect()
{
    socket->connectToHost(SERVER_IP, SERVER_PORT);

}

void NetworkManager::disconnected()
{
    reconnectTimer->start();
}

void NetworkManager::connected()
{
    qDebug() << "Connected...";
    reconnectTimer->stop();
    sayHello();

}

bool NetworkManager::SendAllMessage(QString message) {
    if (socket->state() != QAbstractSocket::ConnectedState)
        return false;

    QByteArray r;
    QDataStream str(&r, QIODevice::WriteOnly);

    str << CMD_SENDALLMESSAGE << uniqueID << message;

    socket->write(r);

    return true;
}

void NetworkManager::readyRead()
{
    QByteArray r = socket->readAll();
    QDataStream str(&r, QIODevice::ReadOnly);

    int cmd;
    str >> cmd;

    int uniqId;
    str >> uniqId;

    qDebug()<< "Incomming transmission: type: " << cmd << " from: "<< uniqId;

    if(cmd == CMD_MESSAGE || cmd == CMD_CHANGENICK){
        QString message;
        str >> message;
        qDebug() << message;

    }

}

