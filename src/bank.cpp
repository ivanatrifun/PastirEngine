#include <bank.hpp>
#include <iostream>

// ## TEXTURE BANK ## //

TextureBank::TextureBank(int initial_size) {
    init(initial_size);
}

int TextureBank::init(int size) {
    initialSize = size;
    contents = new Texture[size];
    return contents==NULL;
}

TextureID TextureBank::loadTexture(const char* file, int al_flags) {
    if (size+1>=initialSize) return -1;
    contents[size++].load(file,al_flags);
    return size;
}

TextureID TextureBank::loadTextureAt(TextureID id, const char* file, int al_flags) {
    if (id<0 || id>=initialSize) return -1;
    if (contents[id].getAllegroBitmap()) {
        printf("[BANK] Texture already exists at index=%d\n", id);
        return loadTexture(file, al_flags);
    }
    if (contents[id].load(file,al_flags)) return -1;
    return id;
}

void TextureBank::destroy(TextureID id) {
    contents[id].destroy();
}
void TextureBank::destroyAll() {
    for (int i=0; i<initialSize; i++) {
        contents[i].destroy();
    }
    size = 0;
}
void TextureBank::free() {
    delete[] contents;
}


const Texture& TextureBank::getTexture(TextureID id) const {
    return contents[id];
}




// #namespace bank

namespace bank {
    TextureBank *banks = NULL;
    unsigned int __initialSize;
} // namespace bank

void bank::init(unsigned int size) {
    __initialSize = size;
    banks = new TextureBank[size];
}
void bank::destroyAll() {
    for (int i=0; i<__initialSize; i++) {
        banks[i].destroyAll();
        banks[i].free();
    }
}
void bank::free(){
    delete[] banks;
}
void bank::makeGlobal(TextureBank& bank, unsigned int id) {
    banks[id] = bank;
}
const TextureBank& bank::getBank(unsigned int id) {
    return banks[id];
}