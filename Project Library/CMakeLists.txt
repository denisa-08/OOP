cmake_minimum_required(VERSION 3.21)
project(Project_Library)

set(CMAKE_CXX_STANDARD 23)

add_executable(Project_Library main.cpp Book.cpp Book.h Validator.cpp Validator.h BookRepo.cpp BookRepo.h BookSrv.cpp BookSrv.h Console.cpp Console.h Cart.cpp Cart.h Map.cpp Map.h Undo.cpp Undo.h)
