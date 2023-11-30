cmake_minimum_required(VERSION 3.5)
project(nasobeni_matic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(core-files
        Matrix.hpp
        Matrix.cpp)


add_executable(nasobeni_matic
        main.cpp
        ${core-files}
)
