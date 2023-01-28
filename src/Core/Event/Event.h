#pragma once

#include "Core/Container/String.h"
#include "Core/Integer.h"

struct Event
{
    String name;

    virtual String ToString() 
    {
        return name;
    };
};
