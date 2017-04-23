/********************************************************************************
** Form generated from reading UI file 'privatemessage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIVATEMESSAGE_H
#define UI_PRIVATEMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrivateMessage
{
public:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;

    void setupUi(QWidget *PrivateMessage)
    {
        if (PrivateMessage->objectName().isEmpty())
            PrivateMessage->setObjectName(QStringLiteral("PrivateMessage"));
        PrivateMessage->resize(400, 300);
        textEdit = new QTextEdit(PrivateMessage);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 381, 241));
        lineEdit = new QLineEdit(PrivateMessage);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 260, 381, 31));

        retranslateUi(PrivateMessage);

        QMetaObject::connectSlotsByName(PrivateMessage);
    } // setupUi

    void retranslateUi(QWidget *PrivateMessage)
    {
        PrivateMessage->setWindowTitle(QApplication::translate("PrivateMessage", "PrivateMsg", 0));
    } // retranslateUi

};

namespace Ui {
    class PrivateMessage: public Ui_PrivateMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVATEMESSAGE_H
