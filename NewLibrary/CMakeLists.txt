cmake_minimum_required(VERSION 3.21)
project(NewLibrary)

set(CMAKE_CXX_STANDARD 14)

add_executable(NewLibrary main.cpp Validator.cpp Validator.h Book.cpp Book.h BookRepo.cpp BookRepo.h BookSrv.cpp BookSrv.h Console.cpp Console.h DynamicArray.cpp DynamicArray.h Errors.cpp Errors.h)
