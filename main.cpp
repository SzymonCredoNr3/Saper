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



class SaperGuiError : exception{
    string msg;
public:
    explicit SaperGuiError(string msg){
        this->msg = msg;
    }
    const char* what(){
        return msg.c_str();
    }
};

class GuiBox : public QPushButton{
private:
    bool clicked;
    box* master;
public:
    GuiBox(box* master){
        this->master = master;
        clicked = false;
        setText(" ");
        setFixedSize(30, 30);
        mousePressEvent();
    }
    void mousePressEvent(QMouseEvent *e = nullptr) {
        if(!clicked){
            clicked = true;
            setFlat(true);
            if(master->ile_bomb >=9)
                setText("X");
            else if(master->ile_bomb != 0)
                setText(QString::fromStdString(to_string((int)(master->ile_bomb))));
            master->hit();
        }
    }

};

class SaperGui : protected Saper, public QMainWindow{
public:
    SaperGui(board_size w, difficulty t) : Saper(w, t), QMainWindow(){
        auto *root = new QWidget(this);

        // menu
        auto *menu = new QMenuBar(root);
            menu->addMenu("&Nowa Gra");
        // main content
        auto *boardWidget = new QWidget(root);
            boardWidget->setLayout(createBoard(root));
        auto *rootLayout = new QVBoxLayout(root);
            rootLayout->addWidget(boardWidget);

        root->setLayout(createBoard(root));
        this->setCentralWidget(root);
        this->show();
    }
private:
    QGridLayout* createBoard(QWidget* root){
        auto *l = new QGridLayout(root);
        l->setContentsMargins(1,30,1,1);
        l->setSpacing(0);

        for(int i = 0; i< widthPlansza; i++){
            for(int j = 0; j<heightPlansza; j++){
                l -> addWidget(new GuiBox(&plansza[i*widthPlansza+j]), i, j);
            }
        }
        return l;
    }
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);


    SaperGui window(smal, eazy);

    // Load stylesheets
    ifstream CssFile(R"(C:\Users\szymo\CLionProjects\SapSapSap\SapSap\style.css)");
    string css_content, tmp_string;
    while(getline(CssFile, tmp_string))
        css_content += tmp_string;
    qDebug() << QString::fromStdString(css_content);
    app.setStyleSheet( QString::fromStdString(css_content));


    return app.exec();
}

