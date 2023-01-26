#pragma once

#include "Core/Event/Event.hpp"
#include "Core/Utility/EnumBitManipulator.hpp"

enum class ModifierKey {
    none = 0b0,
    shift = 0b1,
    alt = 0b10,
    ctrl = 0b100,
    super = 0b1000,
    hyper = 0b10000,
    meta = 0b100000,
    capsLock = 0b1000000,
    numLock = 0b10000000,
};

ENUM_BIT_MANIPILATOR(ModifierKey);

enum class Key {
    n0 = '0',
    n1 = '1',
    n2 = '2',
    n3 = '3',
    n4 = '4',
    n5 = '5',
    n6 = '6',
    n7 = '7',
    n8 = '8',
    n9 = '9',

    a = 'a',
    b = 'b',
    c = 'c',
    d = 'd',
    e = 'e',
    f = 'f',
    g = 'g',
    h = 'h',
    i = 'i',
    j = 'j',
    k = 'k',
    l = 'l',
    m = 'm',
    n = 'n',
    o = 'o',
    p = 'p',
    q = 'q',
    r = 'r',
    s = 's',
    t = 't',
    u = 'u',
    v = 'v',
    w = 'w',
    x = 'x',
    y = 'y',
    z = 'z',

    space = ' ',
    period = '.',
    comma = ',',
    apostrophe = '\'',
    minus = '-',
    equal = '=',
    semicolon = ';',
    backtick = '`',
    slash = '/',
    backslash = '\\',
    lBracket = '[',
    rBracket = ']',

    escape = 27,
    return_ = 13,
    tab = 9,
    backspace = 8,
    delete_ = 127,

    lShift = 57441,
    lCtrl = 57442,
    lAlt = 57443,
    lSuper = 57444,

    rShift = 57447,
    rCtrl = 57448,
    rAlt = 57449,
    rSuper = 57450,
};

String toString(ModifierKey key);

String toString(Key key);

struct KeyEvent : Event {
    Key key;
    ModifierKey modifierKey = ModifierKey::none;
    int codepoint = 0;

    KeyEvent() : Event(EventType::key) {}

    virtual String toString() override;
};
