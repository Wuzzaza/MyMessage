#include "loginform.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);


    LoginForm loginForm;
    loginForm.show();

    return a.exec();
}
