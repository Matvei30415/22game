cmake_minimum_required(VERSION 3.10.0)
project(22game VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(22game card.cpp deck.cpp table.cpp player.cpp rules.cpp consoleIO.cpp human.cpp bot.cpp game.cpp 22game.cpp)

target_compile_options(22game PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

if (WIN32)
    target_link_libraries(22game PRIVATE user32 gdi32)
endif()