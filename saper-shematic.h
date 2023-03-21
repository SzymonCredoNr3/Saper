#include <QDebug>

enum user_mark{
    znak_zapytania = 2,
    flaga = 1,
    null = 0,
    odsloniente = -1
};
struct box{
    char ile_bomb; // pseudo byte int, jeśli bomba 9, w pozostałych przypadkach liczba bomb do okoła
    user_mark oznaczenie;
    box();
    box* otoczenie();
};
enum size{
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
    box* plansza;
    unsigned short int miny;

public:
    Saper();
    box* get_plansza();
    int pozostałe_miny();
    void hit_box(int x, int y);

};