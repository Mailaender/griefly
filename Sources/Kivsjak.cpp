#include "Kivsjak.h"
#include "LiquidHolder.h"
#include "MapClass.h"
#include "Turf.h"
#include "sync_random.h"

Kivsjak::Kivsjak()
{
    SetSprite("icons/kivsjak.png");
    imageStateW = dMove;
    v_level = 9;
    tickSpeed = 1;
    max_dmg = 300;
    inside->size = 200;
    inside->addLiquid(hash("liquidblood"), 200);
    food = 0;
    name = "Kivsjak";
}

void Kivsjak::aaMind()
{
    if(get_rand() % 13 == 0)
        checkMove(get_rand() % 4);
    auto i = map->getItem<CWeed>(posx, posy);
    if(i != map->squares[posx][posy].end())
    {
        (*i)->delThis();
        food += 10;
    }
    if(food > 250)
    {
        food = 0;
        //map->newItemOnMap<IOnMapItem>(hash("kivsjak"), posx, posy);
    }
}

void Kivsjak::live()
{
    CAliveMob::live();
    if(inside->amountOf(hash("liquidblood") < 130))
        bloodless++;
    auto i = map->getItem<Pit>(posx, posy);
    if(i != map->squares[posx][posy].end())
    {
        auto li = castTo<Pit>(**i);
        if(li->lhold->amountOfAll() >= li->lhold->size - 10)
            oxyless++;
    }
    if(dmg + bloodless + burn + interior + oxyless > max_dmg)
    {
        fabric->newItemOnMap<IOnMapItem>(hash("meat"), posx, posy);
        delThis();
    }
}

bool Kivsjak::checkMove(Dir direct)
{
    bool retval = CAliveMob::checkMove(direct);
    imageStateW = dMove;
    return retval;
}