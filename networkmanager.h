#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>
#include <QDataStream>

#define CMD_HELLO 0
#define CMD_BYE 1
#define CMD_MESSAGE 3
#define CMD_ISTHERE 3
#define CMD_IAMHERE 4
#define CMD_CHANGENICK 2
#define CMD_SENDALLMESSAGE 5
#define CMD_SENDPRIVATEMESSAGE 8
#define CMD_GETUSERNICK 7

#define MAGIC_START 0xaabbccddeeff0011



const QString SERVER_IP = "54.236.42.113";
const int SERVER_PORT = 3333;


class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = 0, QString userName = "");
    bool sendMessage(QString);
    bool SendAllMessage(QString);
    bool ChangeNick(QString);
    int getMyUniqueId(){return this->uniqueID;}

private:
    QTimer *reconnectTimer = NULL;
    QTcpSocket *socket = NULL;
    QString userName;
    int uniqueID;

    int generateUniqueID();
    void sayHello();


signals:
    void messageRecieved(int Id, QString message);
    void userNickChanged(int Id, QString nick);
    void connectedToServer();
    void connectingToServer();

public slots:
    void reconnect();
    void disconnected();
    void connected();
    void readyRead();
};

#endif // NETWORKMANAGER_H
