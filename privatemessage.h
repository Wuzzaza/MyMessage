#ifndef PRIVATEMESSAGE_H
#define PRIVATEMESSAGE_H

#include <QWidget>

namespace Ui {
class PrivateMessage;
}

class PrivateMessage : public QWidget
{
    Q_OBJECT

public:
    explicit PrivateMessage(QWidget *parent = 0, QString toUser = "");
    ~PrivateMessage();

private:
    Ui::PrivateMessage *ui;
};

#endif // PRIVATEMESSAGE_H
