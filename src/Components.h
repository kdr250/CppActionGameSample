#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class CTransform
{
public:
    Vec2 position         = {0.0, 0.0};
    Vec2 previoutPosition = {0.0, 0.0};
    Vec2 velocity         = {0.0, 0.0};
    Vec2 scale            = {1.0, 1.0};
    double angle          = 0;

    CTransform(const Vec2& p) : position(p) {}
};

class CLifespan
{
public:
    int remaining = 0;
    int total     = 0;

    CLifespan(int total) : remaining(total), total(total) {}
};

class CInput
{
public:
    bool up    = false;
    bool left  = false;
    bool right = false;
    bool down  = false;
    bool shoot = false;

    CInput() {};
};

class CBoundingBox
{
public:
    Vec2 size;
    Vec2 halfSize;

    CBoundingBox(const Vec2& s) : size(s), halfSize(s.x / 2, s.y / 2) {}
};

class CAnimation
{
};

class CGravity
{
};

class CState
{
};
