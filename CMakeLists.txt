cmake_minimum_required(VERSION 3.10.0)
project(22game VERSION 0.1.0 LANGUAGES C CXX)

add_executable(22game 22game.cpp basic.cpp bot.cpp card.cpp deck.cpp game.cpp hunter.cpp input.cpp output.cpp player.cpp points.cpp)

