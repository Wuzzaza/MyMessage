#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent, QString userName) : QObject(parent)
{
    this->userName = userName;

    reconnectTimer = new QTimer;
    reconnectTimer->setInterval(5000);

    socket = new QTcpSocket(this);

    connect(reconnectTimer, SIGNAL(timeout()), this, SLOT(reconnect()));

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));

    reconnectTimer->start();
}

bool NetworkManager::sendMessage(QString message)
{
    if (!(socket->ConnectedState)) return false;
    //TODO

    QByteArray byteArr;
    QDataStream dataStream(&byteArr, QIODevice::WriteOnly);

    dataStream << 1234;
    dataStream << userName;
    dataStream << CMD_MESSAGE;
    dataStream << message;

    socket->write(byteArr);

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
}

