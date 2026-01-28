#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

void assertInit(int ret, const char* name){
    if (!ret){
        std::cerr << name << " nece da radi >:c\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Ucitao " << name << std::endl;
}

void init(){
    assertInit(al_init(), "allegro");
    assertInit(al_init_primitives_addon(), "primitives addon");
    assertInit(al_init_image_addon(), "image addon");
    assertInit(al_init_font_addon(), "font addon");
    assertInit(al_install_keyboard(), "keyboard");
    assertInit(al_install_mouse(), "mouse");
    assertInit(al_install_audio(), "audio addon");
}

void uninstall(){
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_uninstall_audio();
}

// ovo allegro sranje ne da mi da prdnem bez ovih parametara. jebiga
int main(int argc, char** argv) {
    std::cout << "hallo\n";
    init();

    uninstall();

    return 0;
}
