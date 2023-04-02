#include <QDebug>
#include <vector>
#include <set>

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
class EndOfTheGame : exception{
};
enum user_mark{
    znak_zapytania = 2,
    flaga = 1,
    null = 0,
};
struct box{
    char ile_bomb; // pseudo byte int, jeśli bomba 9, w pozostałych przypadkach liczba bomb do okoła
    user_mark oznaczenie;
    box();

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
    void inline generateMap();
protected:
    unsigned short int miny, widthPlansza, heightPlansza;
    difficulty trudnosc;
    vector<box> plansza;

    set<box*> otoczenie(box* target);
public:
    Saper(board_size w, difficulty t);
    void setDifficulty(difficulty d);
    void setSize(board_size b);
    void reset_core();
    int pozostałe_miny();

};