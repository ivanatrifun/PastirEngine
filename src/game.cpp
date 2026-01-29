#include <game.hpp>
#include <iostream>
#include <display.hpp>
#include <logger.hpp>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 640

Display display;

int game::run(){
    unsigned int frames = 0;
    double lastTime = 0.0;
    while (true) {
        Display::swapBuffers();

        /* handle events: */ {
            ALLEGRO_EVENT evt;
            while (display.getEventQueue()->popNext(&evt)) {
                if (evt.type==ALLEGRO_EVENT_DISPLAY_CLOSE) return 0;
            }
        } // end handling events

        // std::cout << al_get_time() << std::endl; // seconds
        frames++;
        if (al_get_time()-lastTime >= 1.0) {
            lastTime = al_get_time();
            std::cout << frames << std::endl;
            display.setTitle(  (std::string("DEMO FPS: ")+std::to_string(frames)).c_str()  );
            frames = 0;
        }
    }

    return 0;
}

int game::init(){
    if (!display.create(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO")) return -1;

    return 0;
}
void game::clean(){
    logger::info("Cleaning game components...");
    display.destroy();
}
