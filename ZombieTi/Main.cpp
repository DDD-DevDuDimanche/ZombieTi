#include "pch.h"
#include "GameState.h"
#include "JsonManager.h"

int main()
{
    TextureLoader textureHolder;
    GameState::getInstance()->run();
    return 0;
}