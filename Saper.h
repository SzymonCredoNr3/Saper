#include "saper-shematic.h"
#include <random>
// box
box::box(){
    oznaczenie = null;
    ile_bomb = (byte)0;
}

void box::hit() {

}

// Saper
Saper::Saper(board_size w, difficulty t) {
    if(w == smal){
        widthPlansza = 10;
        heightPlansza = 15;
    }
    else if(w == S_medium){
        widthPlansza = 15;
        heightPlansza = 30;
    }
    else if(w == big){
        widthPlansza = 20;
        heightPlansza = 40;
    }
    {
        int field_size  = widthPlansza*heightPlansza;
        // przygotowuje ilosc min
        miny = field_size*((float)t/10.0f);
        while(field_size-->0){
            // przygotowuje a-wizualną plansze
            box tmp;
            plansza.push_back(tmp);
        }
        qDebug() << plansza.size();

    }
    generateMap();
}

vector<box *> Saper::otoczenie(box *target) {
    // get location of target
    int coordinate = 0;
    while(plansza.begin() + coordinate < plansza.end()){
        if(target == &plansza[coordinate])
            break;
        coordinate++;
    }
    if(plansza.begin() + coordinate >= plansza.end())
        throw SaperError("brak pola na planszy");
    vector<box*> wyn;
    // góra
    if(coordinate >= widthPlansza)
        wyn.push_back(&plansza[coordinate - widthPlansza]);
    if(coordinate >= widthPlansza && coordinate%widthPlansza != 0)
        wyn.push_back(&plansza[coordinate - widthPlansza - 1]);
    if(coordinate >= widthPlansza && coordinate%widthPlansza != widthPlansza-1)
        wyn.push_back(&plansza[coordinate - widthPlansza + 1]);
    //dół
    if(coordinate% widthPlansza != heightPlansza-1)
        wyn.push_back(&plansza[coordinate + widthPlansza]);
    if(coordinate%widthPlansza != heightPlansza-1 && coordinate%widthPlansza != 0)
        wyn.push_back(&plansza[coordinate + widthPlansza - 1]);
    if(coordinate%widthPlansza != heightPlansza-1 && coordinate%widthPlansza != widthPlansza-1)
        wyn.push_back(&plansza[coordinate + widthPlansza + 1]);
    //lewo
    if(coordinate%widthPlansza != 0)
        wyn.push_back(&plansza[coordinate-1]);
    if(coordinate%widthPlansza != widthPlansza-1)
        wyn.push_back(&plansza[coordinate+1]);
    return wyn;
}

void inline Saper::generateMap() {
    // prepare random generator
    random_device dev;
    mt19937 rng(dev());
//
    vector<int> options;
    for(int i=0; i<widthPlansza*heightPlansza; i++)
        options.push_back(i);
    int miny_tmp = miny;
    while(miny_tmp-- > 0){
        uniform_int_distribution<mt19937::result_type> get_mine_coordinate(1,options.size());
        int index = get_mine_coordinate(rng);
        box * tmp_box = &plansza[options[index]];
        tmp_box->ile_bomb = 9;
        for(box* obok : otoczenie(tmp_box))
            obok->ile_bomb += 1;
        options.erase(options.begin()+index);

    }


}

int Saper::pozostałe_miny(){
    return miny;
}
