cmake_minimum_required(VERSION 3.17)



add_executable(app main.cpp converter_json.cpp inverted_index.cpp search_server.cpp
                ${MY_INCLUDE_DIR}/converter_json.h
                ${MY_INCLUDE_DIR}/inverted_index.h
                ${MY_INCLUDE_DIR}/search_server.h)

target_include_directories(app PRIVATE ${MY_INCLUDE_DIR})