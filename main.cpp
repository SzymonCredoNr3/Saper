#include "Saper.h"
#include <fstream>
#include <QThread>

#include <QApplication>
#include <QDebug>

#include <QMainWindow>

#include <QMenuBar>
#include <QMenu>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QIcon>

#include <QMouseEvent>

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
class ResetButton : public QPushButton{
public:
    ResetButton() : QPushButton(":D"){
        setFixedSize(50, 50);
    }
    void mousePressEvent(QMouseEvent *e); // declared after SaperGui
};
class GuiBox : public QPushButton{
private:
    bool clicked;
public:
    box* master;
    GuiBox(box* master){
        this->master = master;
        clicked = false;
        setText(" ");
        setFixedSize(30, 30);
    }
    void mousePressEvent(QMouseEvent *e); // declared after SaperGui
    void reset(){
        clicked = false;
        setText(" ");
        setFlat(false);
    }
};

class SaperGui : protected Saper, public QMainWindow{
    vector<GuiBox*> box_list;
public:
    SaperGui(board_size w, difficulty t) : Saper(w, t), QMainWindow(){
        setFixedSize(size());
        auto *menu = new QMenuBar(this);
            menu->addMenu("Obcje Nowej Gry");

        auto root = new QWidget(this);
        auto rootLayout = new QGridLayout(root);
            rootLayout->setSpacing(0);
            rootLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);

            // tool bar
            rootLayout->addWidget(new QLabel("1"), 0, 0);
            rootLayout->addWidget(new ResetButton(), 0, 1);
            rootLayout->addWidget(new QLabel("3"), 0, 2);
            // board
            auto boardWidget = new QWidget(root);
                boardWidget->setLayout(createBoard(boardWidget));
            rootLayout->addWidget(boardWidget, 1, 0, 1, 3);
        this->setCentralWidget(root);
        this->show();
    }
    void reset(){
        cout << "reset" << endl;
        reset_core();
        for(auto i : box_list)
            i->reset();
    }
    void click_around(GuiBox* target){
        set<int> around;
        set<box*> master_otoczenie = this->otoczenie(target->master);

        int max_amount = master_otoczenie.size();
        int i = 0;
        while(max_amount != 0 || i > plansza.size()){
            if(master_otoczenie.find(&plansza[i]) != master_otoczenie.end()){
                box_list[i]->mousePressEvent(nullptr);
                max_amount--;
            }
            i++;
        }
    }
private:
    QGridLayout* createBoard(QWidget *root){
        cout << "create board" << endl;
        auto *l = new QGridLayout(root);
        l->setContentsMargins(1,30,1,1);
        l->setSpacing(0);
        for(int i = 0; i< heightPlansza; i++){
            for(int j = 0; j<widthPlansza; j++){
                GuiBox* tmp = new GuiBox(&plansza[i*widthPlansza+j]);
                box_list.push_back(tmp);
                l -> addWidget(tmp, i, j);
            }
        }
        return l;
    }
};

SaperGui* main_window;
// mouse press detctions
void ResetButton::mousePressEvent(QMouseEvent *e){
    this->setText(":O");
    main_window->reset();
    this->setText(":D");
}
void GuiBox::mousePressEvent(QMouseEvent *e = nullptr) {
     if(e != nullptr && e -> button() == Qt::RightButton){
        if(master->oznaczenie == null){
            master->oznaczenie = flaga;
            setText("⚑");
        }
        else if(master->oznaczenie == flaga){
            master->oznaczenie = znak_zapytania;
            setText("?");
        }
        else if(master->oznaczenie == znak_zapytania){
            master->oznaczenie = null;
            setText("");
        }
    }
    else if((e == nullptr || e->button() == Qt::LeftButton) && !clicked && master->oznaczenie != flaga){
        clicked = true;
        setFlat(true);
        if(master->ile_bomb >=9)
            setText("X");
        else if(master->ile_bomb != 0)
            setText(QString::fromStdString(to_string((int)(master->ile_bomb))));
        else{ // if(master->ile_bomb == 0)
            main_window->click_around(this);
        }
        master->hit();
    }
}
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    main_window = new SaperGui(smal, eazy);

    // Load stylesheets
    ifstream CssFile(R"(C:\Users\szymo\CLionProjects\SapSapSap\SapSap\style.css)");
    string css_content, tmp_string;
    while(getline(CssFile, tmp_string))
        css_content += tmp_string;
    app.setStyleSheet( QString::fromStdString(css_content));


    return app.exec();
}


