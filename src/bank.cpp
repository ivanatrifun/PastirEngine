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

int TextureBank::loadTextures(const char *prefix, const char* (&textureFileNames)[], unsigned int start, unsigned int count, const char *suffix, int allegro_flags) {
    int err=0;
    for (unsigned int i=0; i<count; i++) {
        std::string full="";
        if (prefix) full += prefix;
        //std::cout << textureFileNames[start+i]  << std::endl;
        if (!textureFileNames[start+i]) {
            fprintf(stderr, "[TEXERR] Texture file name at index=%u ==NULL (skipping)\n", start+i);
            err = -1;
            continue;
        }
        //std::cout << textureFileNames[1]  << std::endl;
        full += std::string(textureFileNames[start+i]);
        //std::cout << textureFileNames[2]  << std::endl;
        if (suffix) full += std::string(suffix);
        // std::cout << "## " << full << " size:"<<size << std::endl;
        if (loadTexture(full.c_str(), allegro_flags) < 0) err=-1;
    }
    // std::cout << "bank error: " << err << std::endl;
    return err;
}

TextureID TextureBank::loadTexture(const char* file, int al_flags) {
    if (size>=initialSize) {
        fprintf(stderr, "[BANK::ERROR] Max content size has been reached: %d\n", initialSize);
        return -2;
    }
    if (contents[size++].load(file,al_flags)) return -1;
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
    //std::cout << "Texture bank made global at " << id << std::endl;
    banks[id] = bank;
}
const TextureBank& bank::getBank(unsigned int id) {
    return banks[id];
}