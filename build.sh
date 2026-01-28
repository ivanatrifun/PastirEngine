export LIBS_DIR="/opt/homebrew/lib"
export LIBS="-lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_color"
export CFLAGS="-fdiagnostics-color=always"
export SRC="src/*.cpp    \
            src/**/*.cpp"
export INCLUDE="include"

/usr/bin/g++ -g src/main.cpp -I${INCLUDE} -L${LIBS_DIR} ${LIBS}