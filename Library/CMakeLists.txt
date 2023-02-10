cmake_minimum_required(VERSION 3.21)
project(Library)

set(CMAKE_CXX_STANDARD 14)

add_executable(Library main.cpp Book.cpp Book.h Validator.cpp Validator.h)
