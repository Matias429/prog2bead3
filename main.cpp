#include "gamemaster.h"

///A menüket (a main menüt és az end game screent) jobb klikkel lehet használni annak érdekében, hogy ne lehessen véletlenül indításkor egybõl bejelölni mezõt...
///vagy adott esetben a játék végén egybõl kiválasztani valamelyik menüpontot.
///A játékosok minden esetben felváltva jelölhetik a mezõket (felülírni nem lehet a másik jelölését), mind a 2 játékos bal klikk segítségével.

using namespace std;
using namespace genv;

int main()
{
    Jatek *jatekmester = new Jatek;
    jatekmester->open();
    event ev;
    while(gin >> ev && ev.keycode != key_escape)
    {
        jatekmester->eventkezelo(ev);
    }
    return 0;
}
