#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    this->setFixedSize(300, 100);

    ui->pushButton->setEnabled(false);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_lineEdit_textChanged(const QString &arg1)
{
    if(ui->lineEdit->text()!="") ui->pushButton->setEnabled(true);
    else ui->pushButton->setEnabled(false);

}

void LoginForm::on_pushButton_clicked()
{
    mainWindow = new MainWindow(NULL, ui->lineEdit->text());
    mainWindow->show();
    this->hide();
}

void LoginForm::on_lineEdit_returnPressed()
{
    if(ui->pushButton->isEnabled())ui->pushButton->clicked();
}
