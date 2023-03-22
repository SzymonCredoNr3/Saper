#include "Saper.h"
#include <fstream>

#include <QApplication>
#include <QDebug>

#include <QMainWindow>

#include <QMenuBar>
#include <QMenu>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>

#include <QFile>




class SaperGui : protected Saper, public QMainWindow{
public:
    SaperGui(){
        auto *root = new QWidget(this);

        // menu
        auto *menu = new QMenuBar(root);
            menu->addMenu("&Nowa Gra");
        // main content
//        auto *boardWidget = new QWidget(root);
//            boardWidget->setLayout(createBoard(root));
//        auto *rootLayout = new QVBoxLayout(root);
//            rootLayout->addWidget(boardWidget);
        root->setLayout(createBoard(root));


        this->setCentralWidget(root);
        this->show();

    }
private:
    QGridLayout* createBoard(QWidget* root){
        qDebug() << "wlazł";
        auto *l = new QGridLayout(root);
        int width, height;

        if(wielkosc == smal){
            width = 10;
            height = 15;
        }
        else if(wielkosc == S_medium){
            width = 15;
            height = 30;
        }
        else if(wielkosc == big){
            width = 20;
            height = 40;
        }

        for(int i = 0; i< height; i++){
            for(int j = 0; j<width; j++){
                auto tmp = new QPushButton("push");
                l -> addWidget(tmp, i, j);
            }


        }
        return l;
    }
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);


    SaperGui window;

    // Load stylesheets
    ifstream CssFile(R"(C:\Users\szymo\Desktop\SapSapSap\SapSap\style.css)");
    string css_content = "", tmp_string;
    while(getline(CssFile, tmp_string))
        css_content += tmp_string;
    qDebug() << QString::fromStdString(css_content);
    app.setStyleSheet( QString::fromStdString(css_content));


    return app.exec();
}

