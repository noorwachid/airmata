#include "Core/Event/KeyEvent.h"

String ToString(ModifierKey key)
{
    switch (key)
    {
        case ModifierKey::None:
            return "None";
        case ModifierKey::Shift:
            return "Shift";
        case ModifierKey::Alt:
            return "Alt";
        case ModifierKey::Ctrl:
            return "Ctrl";
        case ModifierKey::Super:
            return "Super";
        case ModifierKey::Hyper:
            return "Hyper";
        case ModifierKey::Meta:
            return "Meta";
        case ModifierKey::CapsLock:
            return "CapsLock";
        case ModifierKey::NumLock:
            return "NumLock";
        default:
            return "[Unknown]";
    }
}

String ToString(Key key)
{
    switch (key)
    {
        case Key::N1:
            return "n1";
        case Key::N2:
            return "n2";
        case Key::N3:
            return "n3";
        case Key::N4:
            return "n4";
        case Key::N5:
            return "n5";
        case Key::N6:
            return "n6";
        case Key::N7:
            return "n7";
        case Key::N8:
            return "n8";
        case Key::N9:
            return "n9";
        case Key::N0:
            return "n0";

        case Key::A:
            return "a";
        case Key::B:
            return "b";
        case Key::C:
            return "c";
        case Key::D:
            return "d";
        case Key::E:
            return "e";
        case Key::F:
            return "f";
        case Key::G:
            return "g";
        case Key::H:
            return "h";
        case Key::I:
            return "i";
        case Key::J:
            return "j";
        case Key::K:
            return "k";
        case Key::L:
            return "l";
        case Key::M:
            return "m";
        case Key::N:
            return "n";
        case Key::O:
            return "o";
        case Key::P:
            return "p";
        case Key::Q:
            return "q";
        case Key::R:
            return "r";
        case Key::S:
            return "s";
        case Key::T:
            return "t";
        case Key::U:
            return "u";
        case Key::V:
            return "v";
        case Key::W:
            return "w";
        case Key::X:
            return "x";
        case Key::Y:
            return "y";
        case Key::Z:
            return "z";

        case Key::Space:
            return "space";
        case Key::Period:
            return "period";
        case Key::Comma:
            return "comma";
        case Key::Apostrophe:
            return "apostrophe";
        case Key::Minus:
            return "minus";
        case Key::Equal:
            return "equal";
        case Key::Semicolon:
            return "semicolon";
        case Key::Backtick:
            return "backtick";
        case Key::Slash:
            return "slash";
        case Key::Backslash:
            return "backslash";
        case Key::LBracket:
            return "lBracket";
        case Key::RBracket:
            return "rBracket";

        case Key::Return_:
            return "return";
        case Key::Escape:
            return "escape";
        case Key::Tab:
            return "tab";
        case Key::Backspace:
            return "backspace";
        case Key::Delete_:
            return "delete";

        case Key::LShift:
            return "lShift";
        case Key::LCtrl:
            return "lCtrl";
        case Key::LAlt:
            return "lAlt";
        case Key::LSuper:
            return "lSuper";

        case Key::RShift:
            return "rShift";
        case Key::RCtrl:
            return "rCtrl";
        case Key::RAlt:
            return "rAlt";
        case Key::RSuper:
            return "rSuper";

        default:
            return "[unknown]";
    }
}

String KeyEvent::ToString()
{
    String b;

    b += ::ToString(subtype) + " ";

    if (modifierKey != ModifierKey::None)
    {
        if ((modifierKey & ModifierKey::Ctrl) == ModifierKey::Ctrl)
            b += ::ToString(modifierKey) + " + ";

        if ((modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
            b += ::ToString(modifierKey) + " + ";
    }

    b += ::ToString(key);

    return b;
}
