cmake_minimum_required(VERSION 3.17) 


add_executable(TestServer TestSearch_Server.cpp ${MY_SRC_DIR}/search_server.cpp ${MY_SRC_DIR}/inverted_index.cpp)


target_include_directories(TestServer PRIVATE ${MY_INCLUDE_DIR}) #где искать заголовочные файлы
target_link_libraries(TestServer PRIVATE gtest_main nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(TestServer) #находит все тесты в исполняемом файле




