
cmake_minimum_required(VERSION 3.6)
project(BalanceScale)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
	set(CMAKE_CXX_FLAGS "/WX- /Wall /O2 /Ob2")
else()
	set(CMAKE_CXX_FLAGS "-pthread -Wall - Wextra -O3")
endif()

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/example/)

set(SOURCE_FILES
  ${SOURCE_PATH}/main.cpp) 

add_executable(BalanceScaleExample ${SOURCE_FILES})

