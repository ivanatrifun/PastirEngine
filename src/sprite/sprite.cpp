#include <sprite/sprite.hpp>


void Sprite::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

float2 Sprite::getPosition() const {
    return position;
}
float Sprite::getX() const {
    return position.x;
}
float Sprite::getY() const {
    return position.y;
}

float2 operator+(float2 a, float2 b) {
    return {a.x+b.x, a.y+b.y};
}

float2 Sprite::getFullPosition() const {
    return getPosition() + getTranslate();
}

void Sprite::setTranslate(float tx, float ty) {
    translate.x = tx;
    translate.y = ty;
}
float2 Sprite::getTranslate() const {
    return translate;
}

void Sprite::move(float dx, float dy) {
    translate.x += dx;
    translate.y += dy;
}


void Sprite::setTexturesBank(bank::textureBank bnk) {
    _bank = bnk;
}
bank::textureBank Sprite::getTexturesBank() const {
    return _bank;
}

void Sprite::setTextureID(TextureID tex) {
    textureID = tex;
}

TextureID Sprite::getTextureID() const {
    return textureID;
}

void Sprite::setTile(const Rectu& rect) {
    tileRect = rect;
}
void Sprite::setTile(uint mx, uint my, uint w, uint h) {
    tileRect.min.x = mx;
    tileRect.min.y = my;
    tileRect.size.x = w;
    tileRect.size.y = h;
}
Rectu Sprite::getTile() const {
    return tileRect;
}


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
void Sprite::drawWhole(){
    ALLEGRO_BITMAP* bitmap = bank::getBank(_bank).getTexture(textureID).getAllegroBitmap();
    if (!bitmap) return;
    // al_draw_tinted_scaled_rotated_bitmap(bitmap, al_map_rgba(100,100,100, 100), cx, cy, dx, dy, xscale, yscale, angle,  flags);
    al_draw_bitmap(bitmap, position.x+translate.x, position.y+translate.y, 0);
}

void Sprite::draw() {
    ALLEGRO_BITMAP* bitmap = bank::getBank(_bank).getTexture(textureID).getAllegroBitmap();
    if (!bitmap) return;
    al_draw_bitmap_region(bitmap,
        (float)tileRect.min.x, (float)tileRect.min.y,
        (float)tileRect.size.x, (float)tileRect.size.y,
        position.x+translate.x, position.y+translate.y,
        0
    );
}