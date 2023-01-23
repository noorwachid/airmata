#include "Core/EntryPoint.h"

void EntryPoint::run() {
    context.tty.setMode(IO::TTYMode::Raw);

    context.tty.write(
        context.sequence.get(UI::SequenceString::enterCAMode) +
        context.sequence.get(UI::SequenceString::clearScreen) + 
        "\x1b[>u\x1b[=" + std::to_string(0b1111) + "u"
    );

    context.tty.read([this](const String& data, int status) {
        if (data[0] == '\x1B')
            parseInputSequence(data);
        else
            parseInputRaw(data);
    });

    context.loop.run();

    context.tty.write(
        "\x1b[<u" + context.sequence.get(UI::SequenceString::clearScreen) +
        context.sequence.get(UI::SequenceString::exitCAMode)
    );

    context.tty.resetMode();
}

void EntryPoint::on(Event& event) { buffer.on(event); }

void EntryPoint::parseInputRaw(const String& data) {}

void EntryPoint::parseInputSequence(const String& data) {
    UintSize cursor = 1;

    if (data[cursor] == '[') {
        parseInputSequenceKeyboard(data, cursor);
    }
}

void EntryPoint::parseInputSequenceKeyboard(const String& data, UintSize& cursor) {
    KeyEvent event;
    event.type = EventType::key;
    event.subtype = EventSubtype::keyPressed;

    ++cursor;

    if (Utility::isIntegerByte(data[cursor])) {
        event.key = static_cast<Key>(Utility::findIntegerSubBytes(data, cursor));
        event.codepoint = static_cast<int>(event.key);

        if (data[cursor] == ':') {
            ++cursor;

            if (Utility::isIntegerByte(data[cursor])) {
                event.codepoint = Utility::findIntegerSubBytes(data, cursor);
            } else if (data[cursor] == ':') {
                ++cursor;
                int idk = Utility::findIntegerSubBytes(data, cursor);
            }
        }

        if (data[cursor] == ';') {
            ++cursor;

            event.modifierKey = static_cast<ModifierKey>(Utility::findIntegerSubBytes(data, cursor) - 1);

            if (data[cursor] == ':') {
                ++cursor;

                event.subtype = static_cast<EventSubtype>(Utility::findIntegerSubBytes(data, cursor));
            }
        }
    }

    on(event);
}
