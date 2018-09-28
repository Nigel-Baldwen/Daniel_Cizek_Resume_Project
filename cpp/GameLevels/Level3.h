#pragma once

// Level3:
// This class defines the third level of the game.  In this level each of the
// nine targets is moving along closed paths and can be hit
// in any order.

#include "GameLevels/Level.h"

ref class Level3: public Level
{
internal:
    Level3();
    virtual void Initialize(std::vector<GameObject^> objects) override;
};
