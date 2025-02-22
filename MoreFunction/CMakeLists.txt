cmake_minimum_required(VERSION 3.16)

project(MoreFunction)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Network)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(USERINFO_SOURCES
    MoreFunction.cpp
)

set(USERINFO_HEADERS
    MoreFunction.h
)

set(USERINFO_UIS
    MoreFunction.ui
)

# 添加 Qt 库
qt_add_library(mytxt_morefunction STATIC
    ${USERINFO_SOURCES}
    ${USERINFO_HEADERS}
    ${USERINFO_UIS}
    ${RESOURCE_FILES}
)

# 链接 Qt 库
target_link_libraries(mytxt_morefunction PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

# 添加头文件路径
target_include_directories(mytxt_morefunction PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
