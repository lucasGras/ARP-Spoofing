cmake_minimum_required(VERSION 3.13)
project(NWP_myarpspoof_2018 C)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(NWP_myarpspoof_2018
        include/arp.h
        Makefile
        src/main.c src/parser/parser.c)
