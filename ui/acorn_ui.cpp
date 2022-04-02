#include "/usr/include/x86_64-linux-gnu/qt5/QtWidgets/QApplication"
#include "/usr/include/x86_64-linux-gnu/qt5/QtWidgets/QMainWindow"

#include "mainwindow.hpp"

using namespace std;

int main(int argc, char **argv)
{
	
        QApplication app(argc, argv);
        QMainWindow *window = new QMainWindow;
        Ui::MainWindow ui;
        ui.setupUi(window);

        window -> show();
        return app.exec();
	
}
