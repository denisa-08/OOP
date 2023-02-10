cmake_minimum_required(VERSION 3.21)
project(Produse)

set(CMAKE_CXX_STANDARD 14)

add_executable(Produse main.cpp Produs.cpp Produs.h RepoProdus.cpp RepoProdus.h Validator.cpp Validator.h)
