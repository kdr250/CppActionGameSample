#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Vec2.h"

class Component
{
public:
    bool has = false;
};

class CTransform : public Component
{
public:
    Vec2 position         = {0.0, 0.0};
    Vec2 previoutPosition = {0.0, 0.0};
    Vec2 velocity         = {0.0, 0.0};
    Vec2 scale            = {1.0, 1.0};
    double angle          = 0;

    CTransform() {}
    CTransform(const Vec2& p) : position(p) {}
};

class CLifespan : public Component
{
public:
    int remaining = 0;
    int total     = 0;

    CLifespan() {}
    CLifespan(int total) : remaining(total), total(total) {}
};

class CInput : public Component
{
public:
    bool up    = false;
    bool left  = false;
    bool right = false;
    bool down  = false;
    bool shoot = false;

    CInput() {}
};

class CBoundingBox : public Component
{
public:
    Vec2 size;
    Vec2 halfSize;

    CBoundingBox() {}
    CBoundingBox(const Vec2& s) : size(s), halfSize(s.x / 2, s.y / 2) {}
};

class CAnimation : public Component
{
public:
    Animation animation;

    CAnimation() {}
    CAnimation(const Animation& animation) : animation(animation) {};
};

class CGravity : public Component
{
public:
    CGravity() {}
};

class CState : public Component
{
public:
    CState() {}
};
