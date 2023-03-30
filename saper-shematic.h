#include <QDebug>
#include <vector>

#define byte char
using namespace std;

class SaperError : exception{
    string msg;
public:
    explicit SaperError(string msg){
        this->msg = msg;
    }
    const char* what(){
        return msg.c_str();
    }
};
enum user_mark{
    znak_zapytania = 2,
    flaga = 1,
    null = 0,
    odsloniente = -1
};
struct box{
    byte ile_bomb; // pseudo byte int, jeśli bomba 9, w pozostałych przypadkach liczba bomb do okoła
    user_mark oznaczenie;
    box();

    void hit();
};
enum board_size{
    smal = 1,
    S_medium = 2,
    big = 3
};
enum difficulty{
    eazy = 1,
    D_medium = 2,
    hard = 3
};

class Saper{
    unsigned short int miny;
    void inline generateMap();
    vector<box*> otoczenie(box* target);
protected:
    vector<box> plansza;
    unsigned short int widthPlansza, heightPlansza;
    difficulty trudnosc;
public:

    Saper(board_size w, difficulty t);
    int pozostałe_miny();

};