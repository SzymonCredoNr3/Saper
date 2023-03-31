#include "saper-shematic.h"
#include <random>
#include <iostream>

using namespace std;
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
        widthPlansza = 15;
        heightPlansza = 10;
    }
    else if(w == S_medium){
        widthPlansza = 30;
        heightPlansza = 15;
    }
    else if(w == big){
        widthPlansza = 40;
        heightPlansza = 20;
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

    }
    generateMap();
}

set<box *> Saper::otoczenie(box *target) {
    std::cout << "@@@otoczenie@@@";
    // get location of target
    int coordinate = 0;
    while(plansza.begin() + coordinate < plansza.end()){
        if(target == &plansza[coordinate])
            break;
        coordinate++;
    }
    std::cout << "c:" << coordinate << endl;
    if(plansza.begin() + coordinate >= plansza.end())
        throw SaperError("brak pola na planszy");
    set<box*> wyn;
    bool zg_w = coordinate%widthPlansza != 0, // zachodniej (nie można przy lewej granicy)
         zg_e = coordinate%widthPlansza != widthPlansza-1, // wschodniej (nie można przy prawej granicy)
         zg_s = coordinate < widthPlansza*(heightPlansza-1), // południowej (nie można przy dole planszy)
         zg_n = coordinate >= widthPlansza; // północnej (nie można przy górze planszy)
    if(zg_s) {
        wyn.insert(&plansza[coordinate + widthPlansza]); // y + 1
        cout << coordinate + widthPlansza << endl;
    }
    if(zg_n) {
        wyn.insert(&plansza[coordinate - widthPlansza]); // y - 1
        cout << coordinate - widthPlansza << endl;
    }
    if(zg_w){
        wyn.insert(&plansza[coordinate-1]); // x - 1
        cout << coordinate-1 << endl;
    }

    if(zg_e){
        wyn.insert(&plansza[coordinate+1]); // x + 1
        cout << coordinate+1 << endl;
    }

    if(zg_s && zg_w){
        wyn.insert(&plansza[coordinate+widthPlansza-1]); // y + 1, x - 1
        cout << coordinate+widthPlansza-1 << endl;
    }

    if(zg_s && zg_e){
        wyn.insert(&plansza[coordinate+widthPlansza+1]); // y + 1, x + 1
        cout << coordinate+widthPlansza+1 << endl;
    }

    if(zg_n && zg_w){
        wyn.insert(&plansza[coordinate-widthPlansza-1]); // y - 1, x - 1
        cout << coordinate-widthPlansza-1 << endl;
    }
    if(zg_n && zg_e){
        wyn.insert(&plansza[coordinate-widthPlansza+1]); // y - 1, x + 1
        cout << coordinate-widthPlansza+1 << endl;
    }
    cout << "w sumie: " << wyn.size() << endl;
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
