#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>
#include <QDataStream>

#define CMD_HELLOW 1
#define CMD_MESSAGE 3


const QString SERVER_IP = "54.236.42.113";
const int SERVER_PORT = 3333;


class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = 0, QString userName = "");
    bool sendMessage(QString message);



private:
    QTimer *reconnectTimer = NULL;
    QTcpSocket *socket = NULL;
    QString userName;
    int uniqueID;

    int generateUniqueID();
    void sayHello();


signals:

public slots:
    void reconnect();
    void disconnected();
    void connected();
    void readyRead();
};

#endif // NETWORKMANAGER_H
