#include "gamemaster.h"

///A men�ket (a main men�t �s az end game screent) jobb klikkel lehet haszn�lni annak �rdek�ben, hogy ne lehessen v�letlen�l ind�t�skor egyb�l bejel�lni mez�t...
///vagy adott esetben a j�t�k v�g�n egyb�l kiv�lasztani valamelyik men�pontot.
///A j�t�kosok minden esetben felv�ltva jel�lhetik a mez�ket (fel�l�rni nem lehet a m�sik jel�l�s�t), mind a 2 j�t�kos bal klikk seg�ts�g�vel.

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
