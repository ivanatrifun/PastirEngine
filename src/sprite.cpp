#include <sprite.hpp>


void Sprite::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

float2 Sprite::getPosition() const {
    return position;
}

void Sprite::setTextureID(TextureID tex) {
    textureID = tex;
}

TextureID Sprite::getTextureID() const {
    return textureID;
}


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
void Sprite::draw(){
    ALLEGRO_BITMAP* bitmap = bank::getBank(BANK_MAP_DRAWABLE_TEXTUREBANK).getTexture(0).getAllegroBitmap();
    // al_draw_tinted_scaled_rotated_bitmap(bitmap, al_map_rgba(100,100,100, 100), cx, cy, dx, dy, xscale, yscale, angle,  flags);
    al_draw_bitmap(bitmap, position.x, position.y, 0);
}