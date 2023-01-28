#pragma once

#include "Core/Event/Event.h"
#include "Core/Utility/EnumBitManipulator.h"

enum class ModifierKey
{
    None = 0b0,
    Shift = 0b1,
    Alt = 0b10,
    Ctrl = 0b100,
    Super = 0b1000,
    Hyper = 0b10000,
    Meta = 0b100000,
    CapsLock = 0b1000000,
    NumLock = 0b10000000,
};

ENUM_BIT_MANIPILATOR(ModifierKey);

enum class Key
{
    N0 = '0',
    N1 = '1',
    N2 = '2',
    N3 = '3',
    N4 = '4',
    N5 = '5',
    N6 = '6',
    N7 = '7',
    N8 = '8',
    N9 = '9',

    A = 'a',
    B = 'b',
    C = 'c',
    D = 'd',
    E = 'e',
    F = 'f',
    G = 'g',
    H = 'h',
    I = 'i',
    J = 'j',
    K = 'k',
    L = 'l',
    M = 'm',
    N = 'n',
    O = 'o',
    P = 'p',
    Q = 'q',
    R = 'r',
    S = 's',
    T = 't',
    U = 'u',
    V = 'v',
    W = 'w',
    X = 'x',
    Y = 'y',
    Z = 'z',

    Space = ' ',
    Period = '.',
    Comma = ',',
    Apostrophe = '\'',
    Minus = '-',
    Equal = '=',
    Semicolon = ';',
    Backtick = '`',
    Slash = '/',
    Backslash = '\\',
    LBracket = '[',
    RBracket = ']',

    Escape = 27,
    Return = 13,
    Tab = 9,
    Backspace = 8,
    Delete = 127,

    Left,
    Up,
    Down,
    Right,

    LShift = 57441,
    LCtrl = 57442,
    LAlt = 57443,
    LSuper = 57444,

    RShift = 57447,
    RCtrl = 57448,
    RAlt = 57449,
    RSuper = 57450,
};

String ToString(ModifierKey key);

String ToString(Key key);

struct KeyEvent : Event
{
    Key key;
    ModifierKey modifierKey = ModifierKey::None;
    int codepoint = 0;

    virtual String ToString() override;
};

