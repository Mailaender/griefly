#include "MetalWall.h"

#include "Weldingtool.h"
#include "Girder.h"
#include "Floor.h"
#include "Materials.h"

#include "representation/Sound.h"

#include "../ObjectFactory.h"
#include "../Game.h"

MetalWall::MetalWall(size_t id) : ITurf(id)
{
    transparent = false;
    SetPassable(D_ALL, Passable::EMPTY);

    v_level = 2;

    SetSprite("icons/walls.dmi");
    SetState("metal0");

    name = "Metal wall";
}

void MetalWall::AttackBy(id_ptr_on<Item> item)
{
    if (id_ptr_on<Weldingtool> wtool = item)
    {
        if (wtool->Working())
        {
            PlaySoundIfVisible("Welder.ogg", owner.ret_id());
            Create<IOnMapObject>(Girder::T_ITEM_S(), GetOwner());
            Create<IOnMapObject>(Metal::T_ITEM_S(), GetOwner());
            Create<ITurf>(Plating::T_ITEM_S(), GetOwner());
            Delete();
        }
    }
}

ReinforcedWall::ReinforcedWall(size_t id) : ITurf(id)
{
    transparent = false;
    SetPassable(D_ALL, Passable::EMPTY);

    v_level = 2;

    SetSprite("icons/walls.dmi");
    SetState("r_wall");

    name = "Reinforced wall";
}
