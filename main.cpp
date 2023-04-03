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
#include <QPushButton>
#include <QLabel>
#include <QIcon>

#include <QMouseEvent>

#include <QFile>
#include <QStyle>

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
        QFont tmp;
        tmp.setBold(true);
        setFont(tmp);
    }
    void mousePressEvent(QMouseEvent *e); // declared after SaperGui
};
class GuiBox : public QPushButton{
public:
    bool clicked;
    box* master;
    GuiBox(box* master){
        this->master = master;
        clicked = false;

        QFont tmp;
        tmp.setBold(true);
        setFont(tmp);
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
    short int now_miny;
    unsigned int clicked_count;

    vector<GuiBox*> box_list;
    ResetButton* resetButton;
    QLabel* mine_count;
public:
    bool hasEnded;
    SaperGui(board_size w, difficulty t) : Saper(w, t), QMainWindow(){
        hasEnded = false;
        clicked_count = 0;
        now_miny = miny;
        setFixedSize(size());

        auto *menu = new QMenuBar(this);
            menu->addMenu("Obcje Nowej Gry");


        auto root = new QWidget(this);
        auto rootLayout = new QGridLayout(root);
            rootLayout->setSpacing(0);
            rootLayout->setAlignment(Qt::AlignmentFlag::AlignHCenter);

            // tool bar
            mine_count = new QLabel(QString::fromStdString(to_string(miny)));
                mine_count->setAlignment(Qt::AlignmentFlag::AlignHCenter);
                rootLayout->addWidget(mine_count, 0, 0);
            resetButton = new ResetButton();
                rootLayout->addWidget(resetButton, 0, 1);
            rootLayout->addWidget(new QLabel("3"), 0, 2);
            // board
            auto boardWidget = new QWidget(root);
                boardWidget->setLayout(createBoard(boardWidget));
            rootLayout->addWidget(boardWidget, 1, 0, 1, 3);
        this->setCentralWidget(root);
        this->show();
    }
    void reset(){
        reset_core();
        hasEnded = false;
        clicked_count = 0;
        now_miny = miny;
        mine_count->setText(QString::fromStdString(to_string(miny)));
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
    int minus_mine(){
        mine_count->setText(QString::fromStdString(to_string(--now_miny)));
        return now_miny;
    }
    int plus_mine(){
        mine_count->setText(QString::fromStdString(to_string(++now_miny)));
        return now_miny;
    }
    void field_clicked(){
        clicked_count++;
        if(clicked_count+miny==widthPlansza*heightPlansza){
            hasEnded = true;
            resetButton->setText("^^");
        }
    }
    void lost(){
        hasEnded = true;
        resetButton->setText("X(");
        for(auto i : box_list)
            i->mousePressEvent(nullptr);
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
    if(!clicked){
         if(e != nullptr && e -> button() == Qt::RightButton){
            if(master->oznaczenie == null){
                master->oznaczenie = flaga;
                main_window->minus_mine();
                setText("⚑");
            }
            else if(master->oznaczenie == flaga){
                master->oznaczenie = znak_zapytania;
                setText("?");
                main_window->plus_mine();
            }
            else if(master->oznaczenie == znak_zapytania){
                master->oznaczenie = null;
                setText("");
            }
        }
        else if(((e == nullptr || e->button() == Qt::LeftButton) && (master->oznaczenie != flaga || main_window->hasEnded))) {
             clicked = true;
             if (!main_window->hasEnded)
                 setFlat(true);
             if (master->ile_bomb >= 9)
                 setText("☀");
             else if (master->ile_bomb != 0)
                 setText(QString::fromStdString(to_string((int) (master->ile_bomb))));
             else { // if(master->ile_bomb == 0)
                 main_window->click_around(this);
             }
             if (!main_window->hasEnded && master->ile_bomb >= 9) {
                 main_window->lost();
             }
             else if(!main_window->hasEnded)
                 main_window->field_clicked();
         }
    }
}
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    main_window = new SaperGui(smal, eazy);

    return app.exec();
}


