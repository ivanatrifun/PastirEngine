#pragma once
#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <sprite/sprite.hpp>
#include <sprite/texture.hpp>

class Player : Sprite {
public:
    void move(float dx, float dy);
};

#endif