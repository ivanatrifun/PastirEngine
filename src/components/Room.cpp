#include <components/Room.hpp>

void Room::setTranslate(float x, float y) {
    translate.x = x;
    translate.y = y;
}
float2 Room::getTranslate() const {
    return translate;
}
void Room::move(float dx, float dy) {
    translate.x += dx;
    translate.y += dy;
}

void Room::draw() {
    for (Drawable::DrawableData& data : objects) {
        Drawable::drawData(data, translate);
    }
}