cmake_minimum_required(VERSION 3.16)

# 设置项目名称
project(UserInfo)

# 查找 Qt 库
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Network)

# 查找 Qt6 库
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# 设置源文件和头文件
set(USERINFO_SOURCES
    DInfo.cpp
    DLogin.cpp
    FlaskInfo.cpp
)

set(USERINFO_HEADERS
    include/DInfo.h
    include/DLogin.h
    include/FlaskInfo.h
)

set(USERINFO_UIS
    ui/DInfo.ui
    ui/DLogin.ui
)

# 添加 Qt 库
qt_add_library(mytxt_userinfo STATIC
    ${USERINFO_SOURCES}
    ${USERINFO_HEADERS}
    ${USERINFO_UIS}
    ${RESOURCE_FILES}
)

# 链接 Qt 库
target_link_libraries(mytxt_userinfo PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

# 添加头文件路径
target_include_directories(mytxt_userinfo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
