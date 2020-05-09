#include "widget.h"
#include "amobawid.h"
#include "graphics.hpp"
#include "gamemaster.h"
#include <cmath>

void Jatek::feliratok(std::vector<std::string> &szovegek1, std::vector<std::string> &szovegek2)
{
    szovegek1.push_back("Main Menu"); szovegek1.push_back("Play Again");szovegek1.push_back("Exit");
    szovegek2.push_back("Play");
}
void Jatek::wincheck(int k, int l, int e)
{
    bool check1 = true;
    bool check2 = true;
    for (int i = -1; i < 2; i++)
    {
        int mellett = 1;
        int lepes = 1;
        while (check1 == true)
        {
            if (board[k-1][l]->ertekret() == e || board[k+1][l]->ertekret() == e)
            {
                if (k-lepes >= 0 && k+lepes < 15 && board[k+lepes][l]->ertekret() == e)
                {
                    mellett++;
                    lepes++;
                }
                else
                {
                    check1 = false;
                    lepes = 1;
                }
            }
            else if (k+i*lepes >= 0 && k+i*lepes < 15 && l-lepes >= 0 && l-lepes < 15 && board[k+i*lepes][l-lepes]->ertekret() == e)
            {
                mellett++;
                lepes++;
            }
            else
            {
                check1 = false;
                lepes = 1;
            }
        }
        while (check2 == true)
        {
            if (board[k-1][l]->ertekret() == e || board[k+1][l]->ertekret() == e)
            {
                if (k-lepes >= 0 && k+lepes < 15 && board[k-lepes][l]->ertekret() == e)
                {
                    mellett++;
                    lepes++;
                }
                else
                {
                    check2 = false;
                    lepes = 1;
                }
            }
            else if (k-i*lepes >= 0 && k-i*lepes < 15 && l+lepes >= 0 && l+lepes < 15 && board[k-i*lepes][l+lepes]->ertekret() == e)
            {
                mellett++;
                lepes++;
            }
            else
            {
                check2 = false;
                lepes = 1;
            }
        }
        if (mellett >= 5)
        {
            endgame = true;
        }
        check1 = true;
        check2 = true;
    }
}
void Jatek::mezovalt(double ex, double ey, int r)
{
    int o = floor(ex/X*15);
    int s = floor(ey/Y*15);
    if (((r == 1 && player == true ) || (r == 2 && player == false)) && board[o][s]->ertekret() == 0)
    {
        board[o][s]->action(r);
        board[o][s]->draw();
        szabadmezok--;
        if (player == true)
        {
            player = false;
            wincheck(o, s, 1);
        }
        else
        {
            player = true;
            wincheck(o, s, 2);
        }
        if (szabadmezok == 0)
        {
            endgame = true;
        }
    }
}
void Jatek::cclear()
{
    genv::gout << genv::move_to(0, 0) << genv::color(0, 0, 0) << genv::box(X, Y);
}
void Jatek::feltolt(std::vector<Amoba*> oszlop)
{
    board.push_back(oszlop);
}
void Jatek::menudraw()
{
    if (menu == true)
    {
        for (size_t i = 0; i < mainmenu.size(); i++)
        {
            mainmenu[i]->draw();
        }
    }
    else if (endgame == true)
    {
        for (size_t i = 0; i < endmenu.size(); i++)
        {
            endmenu[i]->draw();
        }
    }
    genv::gout << genv::refresh;
}
void Jatek::open()
{
    genv::gout.open(X,Y);
    feliratok(endfeliratok, menufeliratok);
    for (size_t i = 0; i < menufeliratok.size(); i++)
    {
        Gomb *button = new Gomb(menufeliratok[i], X/3, Y/(menufeliratok.size()+1)+i*Y/(menufeliratok.size()*2)-Y/16, X/3, Y/8);
        mainmenu.push_back(button);
    }
    for (size_t i = 0; i < endfeliratok.size(); i++)
    {
        Gomb *button = new Gomb(endfeliratok[i], X/3, Y/(endfeliratok.size()+1)+i*Y/(endfeliratok.size()*2)-Y/16, X/3, Y/8);
        endmenu.push_back(button);
    }
    for (size_t i = 0; i < 15; i++)
    {
        std::vector<Amoba*> oszlop;
        for (size_t j = 0; j < 15; j++)
        {
            Amoba *mezo = new Amoba(i*X/15, j*Y/15, X/15, Y/15);
            oszlop.push_back(mezo);
        }
        feltolt(oszlop);
    }
}
void Jatek::gamestart()
{
    cclear();
    szabadmezok = 225;
    for (size_t i = 0; i < 15; i++)
    {
        for (size_t j = 0; j < 15; j++)
        {
            board[i][j]->reset();
            board[i][j]->draw();
        }
    }
    genv::gout << genv::refresh;
    player = true;
}
void Jatek::mainclick(double ex, double ey)
{
    std::vector<double> tmp = mainmenu[0]->koordret();
    if (tmp[0] <= ex && ex <= tmp[0]+tmp[2] && tmp[1] <= ey && ey <= tmp[1]+tmp[3])
    {
        menu = false;
        gamestart();
    }
}
void Jatek::endclick(double ex, double ey)
{
    std::vector<std::vector<double>> tmp;
    for (size_t i = 0; i < 3; i++)
    {
        tmp.push_back(endmenu[i]->koordret());
    }
    if (tmp[0][0] < ex && ex < tmp[0][0]+tmp[0][2] && tmp[0][1] < ey && ey < tmp[0][1]+tmp[0][3])
    {
        cclear();
        menu = true;
        endgame = false;
    }
    if (tmp[1][0] < ex && ex < tmp[1][0]+tmp[1][2] && tmp[1][1] < ey && ey < tmp[1][1]+tmp[1][3])
    {
        gamestart();
        endgame = false;
    }
    if (tmp[2][0] <= ex && ex <= tmp[2][0]+tmp[2][2] && tmp[2][1] <= ey && ey <= tmp[2][1]+tmp[2][3])
    exit(1);
}
void Jatek::eventkezelo(genv::event ev)
{
        if (menu || endgame)
        {
            menudraw();
            if (ev.type == genv::ev_mouse && ev.button == genv::btn_right && menu)
            mainclick(ev.pos_x, ev.pos_y);
            else if (ev.type == genv::ev_mouse && ev.button == genv::btn_right && endgame)
            endclick(ev.pos_x, ev.pos_y);
        }
        if (!menu && !endgame)
        {
            if (ev.type == genv::ev_mouse)
            {
                if (ev.button == genv::btn_left)
                {
                    if (player == true)
                    mezovalt(ev.pos_x, ev.pos_y, 1);
                    else
                    mezovalt(ev.pos_x, ev.pos_y, 2);
                }
            }
        }
}
