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
            return "N1";
        case Key::N2:
            return "N2";
        case Key::N3:
            return "N3";
        case Key::N4:
            return "N4";
        case Key::N5:
            return "N5";
        case Key::N6:
            return "N6";
        case Key::N7:
            return "N7";
        case Key::N8:
            return "N8";
        case Key::N9:
            return "N9";
        case Key::N0:
            return "N0";

        case Key::A:
            return "A";
        case Key::B:
            return "B";
        case Key::C:
            return "C";
        case Key::D:
            return "D";
        case Key::E:
            return "E";
        case Key::F:
            return "F";
        case Key::G:
            return "G";
        case Key::H:
            return "H";
        case Key::I:
            return "I";
        case Key::J:
            return "J";
        case Key::K:
            return "K";
        case Key::L:
            return "L";
        case Key::M:
            return "M";
        case Key::N:
            return "N";
        case Key::O:
            return "O";
        case Key::P:
            return "P";
        case Key::Q:
            return "Q";
        case Key::R:
            return "R";
        case Key::S:
            return "S";
        case Key::T:
            return "T";
        case Key::U:
            return "U";
        case Key::V:
            return "V";
        case Key::W:
            return "W";
        case Key::X:
            return "X";
        case Key::Y:
            return "Y";
        case Key::Z:
            return "Z";

        case Key::Space:
            return "Space";
        case Key::Period:
            return "Period";
        case Key::Comma:
            return "Comma";
        case Key::Apostrophe:
            return "Apostrophe";
        case Key::Minus:
            return "Minus";
        case Key::Equal:
            return "Equal";
        case Key::Semicolon:
            return "Semicolon";
        case Key::Backtick:
            return "Backtick";
        case Key::Slash:
            return "Slash";
        case Key::Backslash:
            return "Backslash";
        case Key::LBracket:
            return "LBracket";
        case Key::RBracket:
            return "RBracket";

        case Key::Return:
            return "Return";
        case Key::Escape:
            return "Escape";
        case Key::Tab:
            return "Tab";
        case Key::Backspace:
            return "Backspace";
        case Key::Delete:
            return "Delete";

        case Key::LShift:
            return "LShift";
        case Key::LCtrl:
            return "LCtrl";
        case Key::LAlt:
            return "LAlt";
        case Key::LSuper:
            return "LSuper";

        case Key::RShift:
            return "RShift";
        case Key::RCtrl:
            return "RCtrl";
        case Key::RAlt:
            return "RAlt";
        case Key::RSuper:
            return "RSuper";

        case Key::Left:
            return "Left";
        case Key::Right:
            return "Right";
        case Key::Up:
            return "Up";
        case Key::Down:
            return "Down";

        default:
            return "[Unknown]";
    }
}

String KeyEvent::ToString()
{
    String b = name + " ";

    if (modifierKey != ModifierKey::None)
    {
        if ((modifierKey & ModifierKey::Ctrl) == ModifierKey::Ctrl)
            b += ::ToString(ModifierKey::Ctrl) + " + ";

        if ((modifierKey & ModifierKey::Alt) == ModifierKey::Alt)
            b += ::ToString(ModifierKey::Alt) + " + ";

        if ((modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
            b += ::ToString(ModifierKey::Shift) + " + ";
    }

    b += ::ToString(key);

    return b;
}
