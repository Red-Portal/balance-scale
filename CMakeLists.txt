
cmake_minimum_required(VERSION 3.8)
project(BalanceScale)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/WX- /Wall /O2 /Ob2")
else()
    set(CMAKE_CXX_FLAGS "-g -Og -pthread -Wall -Wextra")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/example)

set(FIB_SOURCE_FILES
    ${SOURCE_PATH}/fibonacci_approx.cpp)

add_executable(example-fibonacci-approx ${FIB_SOURCE_FILES})

set(FIB_SOURCE_FILES
    ${SOURCE_PATH}/fibonacci_simulator.cpp)


add_executable(example-fibonacci-simulator ${FIB_SOURCE_FILES})

set(MULT_SOURCE_FILES
    ${SOURCE_PATH}/multiplication.cpp) 

add_executable(example-multiplication ${MULT_SOURCE_FILES})

# matplotlib dependencies
set(Python_ADDITIONAL_VERSIONS 3.6)
# find_package(PythonLibs 3.6)

# message(${PYTHON_INCLUDE_PATH})

set(PYTHON_LIBRARIES "/usr/lib/libpython3.6m.so")
set(PYTHON_INCLUDE_DIRS "/usr/include/python3.6m")

target_include_directories(
    example-fibonacci-approx
    PRIVATE ${PYTHON_INCLUDE_DIRS})

target_include_directories(
    example-fibonacci-simulator
    PRIVATE ${PYTHON_INCLUDE_DIRS})

target_include_directories(
    example-multiplication
    PRIVATE ${PYTHON_INCLUDE_DIRS})

target_link_libraries(
    example-fibonacci-approx
    ${PYTHON_LIBRARIES})

target_link_libraries(
    example-fibonacci-simulator
    ${PYTHON_LIBRARIES})

target_link_libraries(
    example-multiplication
    ${PYTHON_LIBRARIES})

