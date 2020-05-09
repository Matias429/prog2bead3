#ifndef GAMEMASTER_H_INCLUDED
#define GAMEMASTER_H_INCLUDED

#include "graphics.hpp"
#include "amobawid.h"
#include "gombwid.h"


class Jatek
{
private:
    bool player = true;
    bool menu = true;
    bool endgame = false;
    std::vector<std::vector<Amoba*>> board;
    std::vector<std::string> menufeliratok;
    std::vector<std::string> endfeliratok;
    std::vector<Gomb*> mainmenu;
    std::vector<Gomb*> endmenu;
    int szabadmezok = 225;
public:
    void open();
    void gamestart();
    void valaszt();
    void mezovalt(double ex, double ey, int r);
    void cclear();
    void feltolt(std::vector<Amoba*> oszlop);
    void gameover();
    void menudraw();
    void mainclick(double ex, double ey);
    void endclick(double ex, double ey);
    void menufeltolt(Gomb *button, int r);
    void wincheck(int k, int l, int e);
    void feliratok(std::vector<std::string> &szovegek1, std::vector<std::string> &szovegek2);
    void eventkezelo(genv::event ev);
};



#endif // GAMEMASTER_H_INCLUDED
