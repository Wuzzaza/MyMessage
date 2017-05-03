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
    reconnect();

}

bool NetworkManager::sendMessage(QString message)
{
    if (!(socket->ConnectedState)) return false;

    QByteArray byteArr;
    QDataStream dataStream(&byteArr, QIODevice::WriteOnly);


    dataStream << (quint64)MAGIC_START << CMD_SENDALLMESSAGE << uniqueID << message;

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
    if (socket->state() != QAbstractSocket::ConnectedState){
        qDebug()<< "Not Sent";
        return false;
    }
    QByteArray r;
    QDataStream str(&r, QIODevice::WriteOnly);

    str << (quint64)MAGIC_START << CMD_CHANGENICK << uniqueID << name;

    socket->write(r);

    return true;
}

void NetworkManager::reconnect()
{
    emit connectingToServer();
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
    emit connectedToServer();
    sayHello();

}

bool NetworkManager::SendAllMessage(QString message) {
    if (socket->state() != QAbstractSocket::ConnectedState){
        qDebug()<<"Not Send!!!";
        return false;
    }

    QByteArray r;
    QDataStream str(&r, QIODevice::WriteOnly);

    str << (quint64)MAGIC_START << CMD_SENDALLMESSAGE << uniqueID << message;

    socket->write(r);

    return true;
}

void NetworkManager::readyRead()
{
    QByteArray r = socket->readAll();
    QDataStream str(&r, QIODevice::ReadOnly);

    quint64 ms;
    str >> ms;

    int cmd;
    str >> cmd;

    int uniqId;
    str >> uniqId;

    QString message;
    str >> message;

    qDebug()<< "Icomming transmission: type: " << cmd << " from: "<< uniqId << " content: " << message;



    if(cmd == CMD_SENDALLMESSAGE) emit messageRecieved(uniqId, message);
    if(cmd == CMD_CHANGENICK) emit userNickChanged(uniqId, message);
    if(cmd == CMD_GETUSERNICK) ChangeNick(userName);

}



