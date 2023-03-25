cmake_minimum_required(VERSION 3.24)
project(CalTrain)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CalTrain
        caltrain-runner.c
        caltrain.c
        caltrain.h
        Makefile
        README.md
        repeat.sh caltrain.c)
