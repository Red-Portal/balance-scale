
cmake_minimum_required(VERSION 3.6)
project(BalanceScale)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/WX- /Wall /O2 /Ob2")
else()
    set(CMAKE_CXX_FLAGS "-g -pthread -Wall -Wextra")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/example)

set(SOURCE_FILES
    ${SOURCE_PATH}/main.cpp) 

add_executable(balance_scale_example ${SOURCE_FILES})

