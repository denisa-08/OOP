cmake_minimum_required(VERSION 3.21)
project(Project_Library)

set(CMAKE_CXX_STANDARD 23)

add_executable(Project_Library main.cpp Book.cpp Book.h Validator.cpp Validator.h BookRepo.cpp BookRepo.h BookSrv.cpp BookSrv.h Console.cpp Console.h DynamicArray.cpp DynamicArray.h Errors.cpp Errors.h)
