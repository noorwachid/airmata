#include "Core/UI/Object/Object.h"
#include "Core/Program.h"

namespace UI
{
    Object::Object(Program& referenceProgram) : program{referenceProgram} {
        SetSize(program.tty.GetSize());
    }

    void Object::On(Event& event) {};

    void Object::Render() {};

    const Vector2& Object::GetPosition() const { return position; }

    const Vector2& Object::GetSize() const { return size; }

    void Object::SetPosition(const Vector2& newPosition) { position = newPosition; }

    void Object::SetSize(const Vector2& newSize) { size = newSize; }
}
