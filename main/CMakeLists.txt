cmake_minimum_required(VERSION 3.16)

# 查找 Qt 库
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 添加可执行文件
qt_add_executable(mytxt_executable
    main.cpp
    mainwindow.cpp
    RecentFilesManager.cpp
    TabHandleCSV.cpp
    TabHandleTXT.cpp
    WidgetFunctional.cpp

    mainwindow.h
    RecentFilesManager.h
    TabHandleCSV.h
    TabHandleTXT.h
    WidgetFunctional.h
    TabAbstract.h
    ../resources/res.qrc  # 确保路径正确
)

target_include_directories(mytxt_executable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接所有库
target_link_libraries(mytxt_executable PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    mytxt_filehis
    mytxt_filetag
    mytxt_manager
    mytxt_onlinedoc
    mytxt_schedule
    mytxt_setting
    mytxt_userinfo
)

# 设置可执行文件的属性
set_target_properties(mytxt_executable PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
