cmake_minimum_required(VERSION 3.9)
project(tAItris C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fgnu89-inline -std=c99 -O0 -g3")

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

include_directories(${SDL_INCLUDE_DIR}
        ${SDL_IMAGE_INCLUDE_DIR}
        ${SDL_TTF_INCLUDE_DIR})

add_executable(tAItris
        src/tAItris.c src/tAItris.h

        src/utils/list.c src/utils/list.h
        src/utils/matrix.c src/utils/matrix.h
        src/utils/random.c src/utils/random.h
        src/utils/timing.c src/utils/timing.h
        src/core/game_state.c src/core/game_state.h
        src/core/piece.c src/core/piece.h
        src/core/motion.c src/core/motion.h
        src/core/board.c src/core/board.h
        src/core/event.c src/core/event.h
        src/core/game.c src/core/game.h
        src/core/input.c src/core/input.h
        src/ui/gui.c src/ui/gui.h
        src/ui/render.c src/ui/render.h
        src/ai/genetic/tools.c src/ai/genetic/tools.h
        src/ai/genetic/engine.c src/ai/genetic/engine.h
        src/ai/genetic/tools.c src/ai/genetic/tools.h
        src/ai/genetic/engine.c src/ai/genetic/engine.h)

target_link_libraries(tAItris ${SDL_LIBRARY}
        ${SDL_IMAGE_LIBRARIES}
        ${SDL_TTF_LIBRARIES})
