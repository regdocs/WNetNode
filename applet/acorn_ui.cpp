#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "mainwindow.hpp"

using namespace std;

int main(int argc, char **argv)
{
        QApplication app(argc, argv);
        jay_io::QtAcorn ui(new QMainWindow);
        return app.exec();
}
