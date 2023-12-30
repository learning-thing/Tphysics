cmake_minimum_required(VERSION 3.28)
project(TPhysics)

add_executable(main src/main.cpp)
target_link_libraries(main raylib)
target_include_directories(main PUBLIC src/lib/ )