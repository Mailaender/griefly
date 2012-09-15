#include "ASpritesClass.h"

GLSprite* ASprClass::returnSpr(std::string type)
{
    if (NODRAW)
        return nullptr;
    if(sprites.find(type) == sprites.end())
        sprites[type] = new GLSprite(type);
    return sprites[type];
}

ASprClass::ASprClass()
{
};