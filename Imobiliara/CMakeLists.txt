cmake_minimum_required(VERSION 3.21)
project(Imobiliara C)

set(CMAKE_C_STANDARD 99)

add_executable(Imobiliara main.c agentie.c agentie.h oferta.c oferta.h service.c service.h user_interface.c user_interface.h tests.c tests.h)
