#ifndef PRIVATEMESSAGE_H
#define PRIVATEMESSAGE_H

#include <QWidget>
#include <networkmanager.h>

namespace Ui {
class PrivateMessage;
}

class PrivateMessage : public QWidget
{
    Q_OBJECT

public:
    explicit PrivateMessage(QWidget *parent = 0, QString toUser = "", NetworkManager *networkManager = NULL);
    ~PrivateMessage();

private:
    Ui::PrivateMessage *ui;
    NetworkManager *networkManager;
};

#endif // PRIVATEMESSAGE_H
