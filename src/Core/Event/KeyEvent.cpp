#include "Core/Event/KeyEvent.hpp"

String toString(ModifierKey key) {
    switch (key) {
        case ModifierKey::none:
            return "None";
        case ModifierKey::shift:
            return "Shift";
        case ModifierKey::alt:
            return "Alt";
        case ModifierKey::ctrl:
            return "Ctrl";
        case ModifierKey::super:
            return "Super";
        case ModifierKey::hyper:
            return "Hyper";
        case ModifierKey::meta:
            return "Meta";
        case ModifierKey::capsLock:
            return "CapsLock";
        case ModifierKey::numLock:
            return "NumLock";
        default:
            return "[Unknown]";
    }
}

String toString(Key key) {
    switch (key) {
        case Key::n1:
            return "n1";
        case Key::n2:
            return "n2";
        case Key::n3:
            return "n3";
        case Key::n4:
            return "n4";
        case Key::n5:
            return "n5";
        case Key::n6:
            return "n6";
        case Key::n7:
            return "n7";
        case Key::n8:
            return "n8";
        case Key::n9:
            return "n9";
        case Key::n0:
            return "n0";

        case Key::a:
            return "a";
        case Key::b:
            return "b";
        case Key::c:
            return "c";
        case Key::d:
            return "d";
        case Key::e:
            return "e";
        case Key::f:
            return "f";
        case Key::g:
            return "g";
        case Key::h:
            return "h";
        case Key::i:
            return "i";
        case Key::j:
            return "j";
        case Key::k:
            return "k";
        case Key::l:
            return "l";
        case Key::m:
            return "m";
        case Key::n:
            return "n";
        case Key::o:
            return "o";
        case Key::p:
            return "p";
        case Key::q:
            return "q";
        case Key::r:
            return "r";
        case Key::s:
            return "s";
        case Key::t:
            return "t";
        case Key::u:
            return "u";
        case Key::v:
            return "v";
        case Key::w:
            return "w";
        case Key::x:
            return "x";
        case Key::y:
            return "y";
        case Key::z:
            return "z";

        case Key::space:
            return "space";
        case Key::period:
            return "period";
        case Key::comma:
            return "comma";
        case Key::apostrophe:
            return "apostrophe";
        case Key::minus:
            return "minus";
        case Key::equal:
            return "equal";
        case Key::semicolon:
            return "semicolon";
        case Key::backtick:
            return "backtick";
        case Key::slash:
            return "slash";
        case Key::backslash:
            return "backslash";
        case Key::lBracket:
            return "lBracket";
        case Key::rBracket:
            return "rBracket";

        case Key::return_:
            return "return";
        case Key::escape:
            return "escape";
        case Key::tab:
            return "tab";
        case Key::backspace:
            return "backspace";
        case Key::delete_:
            return "delete";

        case Key::lShift:
            return "lShift";
        case Key::lCtrl:
            return "lCtrl";
        case Key::lAlt:
            return "lAlt";
        case Key::lSuper:
            return "lSuper";

        case Key::rShift:
            return "rShift";
        case Key::rCtrl:
            return "rCtrl";
        case Key::rAlt:
            return "rAlt";
        case Key::rSuper:
            return "rSuper";

        default:
            return "[unknown]";
    }
}

String KeyEvent::toString() {
    String b;

    b += ::toString(subtype) + " ";

    if (modifierKey != ModifierKey::none) {
        if ((modifierKey & ModifierKey::ctrl) == ModifierKey::ctrl)
            b += ::toString(modifierKey) + " + ";

        if ((modifierKey & ModifierKey::alt) == ModifierKey::alt)
            b += ::toString(modifierKey) + " + ";

        if ((modifierKey & ModifierKey::shift) == ModifierKey::shift)
            b += ::toString(modifierKey) + " + ";
    }

    b += ::toString(key);

    return b;
}
