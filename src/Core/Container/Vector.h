#pragma once

#include "Core/Container/String.h"

struct Vector2
{
    int x = 0;
    int y = 0;

    String ToString() const;
};

struct Vector3
{
    int x = 0;
    int y = 0;
    int z = 0;

    String ToString() const;
};

struct Vector4
{
    int x = 0;
    int y = 0;
    int z = 0;
    int w = 0;

    String ToString() const;
};
