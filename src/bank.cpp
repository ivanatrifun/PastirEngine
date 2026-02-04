#include <bank.hpp>
#include <iostream>
#include <data_types.hpp>
#include <components/utility.hpp>

// ## MULTI TEXTURE BANK ## //

#pragma region MultiTexture Bank

MultiTextureBank::MultiTextureBank(int initial_size) {
    init(initial_size);
}

int MultiTextureBank::init(int size) {
    initialSize = size;
    contents = new Texture[size];
    return contents==NULL;
}

int MultiTextureBank::loadTextures(const char *prefix, const char* (&textureFileNames)[], unsigned int start, unsigned int count, const char *suffix, int allegro_flags) {
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

TextureID MultiTextureBank::loadTexture(const char* file, int al_flags) {
    if (size>=initialSize) {
        fprintf(stderr, "[BANK::ERROR] Max content size has been reached: %d\n", initialSize);
        return -2;
    }
    if (contents[size++].load(file,al_flags)) return -1;
    return size;
}

TextureID MultiTextureBank::loadTextureAt(TextureID id, const char* file, int al_flags) {
    if (id<0 || id>=initialSize) return -1;
    if (contents[id].getAllegroBitmap()) {
        printf("[BANK] Texture already exists at index=%d\n", id);
        return loadTexture(file, al_flags);
    }
    if (contents[id].load(file,al_flags)) return -1;
    return id;
}

void MultiTextureBank::destroy(TextureID id) {
    contents[id].destroy();
}
void MultiTextureBank::destroyAll() {
    for (int i=0; i<initialSize; i++) {
        contents[i].destroy();
    }
    size = 0;
}
void MultiTextureBank::free() {
    delete[] contents;
}


const Texture& MultiTextureBank::getTexture(TextureID id) const {
    return contents[id];
}
#pragma endregion


// ## TILESET BANK ## //
#pragma region Tileset Bank


int TilesetBank::loadTexture(const char* file, int al_flags) {
    if (texture.load(file,al_flags)) return -1;
    return 0;
}
    
int TilesetBank::loadTileRects(const char* tilerectsfile){
    util::loadTiles(tilerectsfile);
}


const Texture& TilesetBank::getTexture() const {
    return texture;
}


Rectu TilesetBank::getTile(int drawableID) const {
    return tileRects[drawableID];
}
   
void TilesetBank::destroy() {

}


#pragma endregion




#pragma region namespace bank::
// #namespace bank

namespace bank {
    template<class T>
    struct bankarr {
        T *banks = NULL;
        unsigned int initialSize=0;
    };
    bankarr<MultiTextureBank> multitex;
    bankarr<TilesetBank> tilesets;
} // namespace bank

void bank::init(unsigned int multitexsize, unsigned int tilesetsize) {
    multitex.initialSize = multitexsize;
    multitex.banks = new MultiTextureBank[multitexsize];

    tilesets.initialSize = multitexsize;
    tilesets.banks = new TilesetBank[tilesetsize];
}
void bank::destroyAll() {
    for (int i=0; i<multitex.initialSize; i++) {
        multitex.banks[i].destroyAll();
        multitex.banks[i].free();
    }
    for (int i=0; i<tilesets.initialSize; i++) {
        tilesets.banks[i].destroy();
    }
}
void bank::free(){
    if (multitex.banks) {
        delete[] multitex.banks;
        multitex.banks = NULL;
    }
    if (tilesets.banks) {
        delete[] tilesets.banks;
        tilesets.banks = NULL;
    }
}
void bank::makeGlobal(MultiTextureBank& bank, unsigned int id) {
    //std::cout << "Texture bank made global at " << id << std::endl;
    multitex.banks[id] = bank;
}
void bank::makeGlobal(TilesetBank& bnk, unsigned int id) {
    //std::cout << "Texture bank made global at " << id << std::endl;
    tilesets.banks[id] = bnk;
}
template<>
const MultiTextureBank& bank::getBank(unsigned int id) {
    // static_assert(std::is_same_v<T, int> || std::is_same_v<T, float>, "Type must be a bank");
    return multitex.banks[id];
}
template<>
const TilesetBank& bank::getBank(unsigned int id) {
    // static_assert(std::is_same_v<T, int> || std::is_same_v<T, float>, "Type must be a bank");
    return tilesets.banks[id];
}

#pragma endregion