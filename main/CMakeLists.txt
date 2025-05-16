cmake_minimum_required(VERSION 3.16)  # 确保 CMake 版本支持此策略
cmake_policy(SET CMP0079 NEW)  # 设置 CMP0079 策略为 NEW


set(MAIN_SOURCES
    main.cpp
    mainwindow.cpp
    RecentFilesManager.cpp
    WidgetFunctional.cpp
    FindDialog.cpp

    include/mainwindow.h
    include/TabAbstract.h
    include/RecentFilesManager.h
    include/WidgetFunctional.h

    include/FindDialog.h

    ui/WidgetFunctional.ui
    ui/mainwindow.ui
    ui/FindDialog.ui

)

# 查找 Qt 库
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg Network)

# 创建静态库
qt_add_library(mytxt_main STATIC
    ${MAIN_SOURCES}
    ../Resources/res.qrc
)

# 添加资源文件
qt_add_resources(TARGET mytxt_main
    RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../Resources/res.qrc
)

# 包含头文件目录
target_include_directories(mytxt_main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include

)

# 链接 Qt 库
target_link_libraries(mytxt_main PRIVATE
    Qt${QT_VERSION_MAJOR}::Core   # 确保链接了 QtCore
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Svg
)
