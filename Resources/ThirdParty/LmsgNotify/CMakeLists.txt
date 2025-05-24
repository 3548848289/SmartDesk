cmake_minimum_required(VERSION 3.5)

project(LmsgNotify LANGUAGES CXX)

file(GLOB LMSGNOTIFY_SOURCES
    *.cpp
)

file(GLOB LMSGNOTIFY_HEADERS
    *.h
)

add_library(LmsgNotify STATIC
    ${LMSGNOTIFY_SOURCES}
    ${LMSGNOTIFY_HEADERS}
)

target_include_directories(LmsgNotify PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LmsgNotify PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 给库定义一个别名用于引用
add_library(LmsgNotify::LmsgNotify ALIAS LmsgNotify)
