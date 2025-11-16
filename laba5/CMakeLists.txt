cmake_minimum_required(VERSION 3.16)

# Название проекта и стандарт C++
project(laba5 VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опционально: унифицировать тип выводов для Debug/Release (Visual Studio)
if(MSVC)
  # Разнести бинарники по конфигурациям (по желанию)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/Debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
endif()

# Пути к исходникам и заголовкам (относительно корня, где лежит этот CMakeLists.txt)
set(SOURCES
  ${CMAKE_SOURCE_DIR}/laba5/sources/main.cpp
  ${CMAKE_SOURCE_DIR}/laba5/sources/menu.cpp
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/laba5/headers/menu.h
  ${CMAKE_SOURCE_DIR}/laba5/headers/utils.h
)

# Автоматически добавить все .cpp в sources (альтернатива ручному перечислению)
# file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/sources/*.cpp)

# Создать исполняемый target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Добавить include-путь к заголовкам
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/laba5/headers
)

# Рекомендации: дополнительные опции компилятора (по желанию)
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX-)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Если нужны дополнительные библиотеки, добавьте их здесь, например:
# target_link_libraries(${PROJECT_NAME} PRIVATE someLib)

# Если вы используете CMake из подпроектов, можно сделать target path относительным:
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
