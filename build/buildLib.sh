export LIBS_DIR="/opt/homebrew/lib"
export LIBS="-lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_color"
export CFLAGS="-fdiagnostics-color=always -std=c++17 -fPIC"
export SRC="../src/*.cpp ../src/**/*.cpp"
#    \
#            src/**/*.cpp"
export INCLUDE="-I../include -I../deps"

# /usr/bin/g++ ${CFLAGS} -c ${SRC} ${INCLUDE} -L${LIBS_DIR} ${LIBS}
g++ ${CFLAGS} ${SRC} ${INCLUDE} -shared -o libPastir.dylib -L${LIBS_DIR} ${LIBS}
rm *.o
# install_name_tool -add_rpath ${LIBS_DIR} a.out