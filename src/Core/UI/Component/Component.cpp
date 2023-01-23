#include "Core/UI/Component/Component.h"

namespace UI
{
    Component::Component(Context& context) : _context{context} {}

    void Component::On(Event& event){};

    void Component::Render(){};

    const Vector2& Component::GetPosition() const { return _position; }

    const Vector2& Component::GetSize() const { return _size; }

    void Component::SetPosition(const Vector2& position) { _position = position; }

    void Component::SetSize(const Vector2& size) { _size = size; }
}
