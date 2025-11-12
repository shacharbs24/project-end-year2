#pragma once

#include "Observer/IObserver.h"

class ISubject {
public:
    virtual ~ISubject() = default;

    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};