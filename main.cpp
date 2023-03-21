#include "Saper.h"

#include <QApplication>
#include <QDebug>

#include <QMainWindow>
#include <QWidget>

class SaperGui : protected Saper, public QMainWindow{
public:
    SaperGui(){

    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SaperGui window;
    window.show();

    return app.exec();
}
