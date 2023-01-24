#include "Core/UI/Component/Component.hpp"

namespace UI {
    Component::Component(Context& newContext) : context{newContext} {}

    void Component::on(Event& event){};

    void Component::render(){};

    const Vector2& Component::getPosition() const { return position; }

    const Vector2& Component::getSize() const { return size; }

    void Component::setPosition(const Vector2& newPosition) { position = newPosition; }

    void Component::setSize(const Vector2& newSize) { size = newSize; }
}
