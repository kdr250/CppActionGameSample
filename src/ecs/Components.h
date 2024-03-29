#pragma once

#include <SFML/Graphics.hpp>
#include "../asset/Animation.h"
#include "../physics/Vec2.h"

class Component
{
public:
    bool has = false;
};

class CTransform : public Component
{
public:
    Vec2 position         = {0.0, 0.0};
    Vec2 previousPosition = {0.0, 0.0};
    Vec2 velocity         = {0.0, 0.0};
    Vec2 scale            = {1.0, 1.0};
    double angle          = 0;

    CTransform() {}
    CTransform(const Vec2& p, const Vec2& s) : position(p), previousPosition(p), scale(s) {}
    CTransform(const Vec2& p, const Vec2& v, const Vec2& s) :
        position(p), previousPosition(p), velocity(v), scale(s)
    {
    }
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
    bool up                           = false;
    bool left                         = false;
    bool right                        = false;
    bool down                         = false;
    bool shoot                        = false;
    bool canShoot                     = true;
    int upCount                       = 0;
    static constexpr int MAX_UP_COUNT = 5;

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
    bool repeat = false;

    CAnimation() {}
    CAnimation(const Animation& a, bool r = false) : animation(a), repeat(r) {};
};

class CGravity : public Component
{
public:
    float gravity = 0;

    CGravity() {}
    CGravity(float g) : gravity(g) {}
};

class CState : public Component
{
public:
    std::string state = "idle";

    CState() {}
    CState(const std::string& s) : state(s) {}
};
