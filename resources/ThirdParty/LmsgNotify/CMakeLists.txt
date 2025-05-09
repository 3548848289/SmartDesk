cmake_minimum_required(VERSION 3.16)
project(LmsgNotify LANGUAGES CXX)

# 原始目标（没有命名空间）
add_library(LmsgNotify STATIC
    src/arrangedwnd.cpp
    src/notifymanager.cpp
    src/notifywnd.cpp
)

target_include_directories(LmsgNotify
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)


target_link_libraries(LmsgNotify
    PUBLIC Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(LmsgNotify PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# ✅ 给目标创建一个命名空间别名
add_library(LmsgNotify::LmsgNotify ALIAS LmsgNotify)
