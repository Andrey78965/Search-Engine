cmake_minimum_required(VERSION 3.17) #версия CMake
project("Search Engine" VERSION 1.0) #название проекта и версия

set(CMAKE_CXX_STANDARD 17) #устанавливаем версию стандарта С++
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)


include(FetchContent) #подключение модуля для автоматического скачивания внешних библиотек из интернета
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
) #объявляем, что нужно скачать. googletest - имя скаченному файлу
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest) #скачаивается библиотека Google Test
enable_testing() #указываем что в проекте будут применяться тесты


set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

add_subdirectory(src)

target_link_libraries(app PRIVATE nlohmann_json::nlohmann_json) 

add_subdirectory(test)
