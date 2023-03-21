#include "saper-shematic.h"

// box
box::box(){
    oznaczenie = null;
    ile_bomb = (char)0;
}
box *box::otoczenie() {

}
// Saper
Saper::Saper() {

}
box* Saper::get_plansza(){
    return plansza;
}
int Saper::pozostałe_miny(){
    return miny;
}

void Saper::hit_box(int x, int y){

}

