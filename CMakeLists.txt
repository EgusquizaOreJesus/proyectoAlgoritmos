cmake_minimum_required(VERSION 3.25)
project(proyectoalgoritmos)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyectoalgoritmos main.cpp)
add_executable(block BlockChain.cpp ChainHash.h ForwardList.h hash.h)
