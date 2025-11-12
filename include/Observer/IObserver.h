#pragma once

#include "GameObject/GameObject.h" 

class GameObject;

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(const GameObject& subject) = 0;
};