cmake_minimum_required(VERSION 3.10.0)
project(22game VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(22game 22game.cpp bot.cpp card.cpp deck.cpp game.cpp console_io.cpp player.cpp points.cpp main_menu.cpp human.cpp)

if (WIN32)
    target_link_libraries(22game PRIVATE user32 gdi32)
endif()