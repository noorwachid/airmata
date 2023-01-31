#pragma once

#include "Core/Container/String.h"

struct Event
{
    String name;

    virtual String ToString() 
    {
        return name;
    };
};
