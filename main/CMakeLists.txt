cmake_minimum_required(VERSION 3.16)

# 查找 Qt 库
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)

# 定义 UI 文件列表
set(UI_FILES
    ui/WidgetFunctional.ui
    ui/mainwindow.ui
)

# 添加可执行文件
qt_add_executable(mytxt_executable
    main.cpp
    mainwindow.cpp
    RecentFilesManager.cpp
    TabHandleCSV.cpp
    TabHandleTXT.cpp
    WidgetFunctional.cpp
#    TabHandleIMG.cpp

    include/mainwindow.h
    include/RecentFilesManager.h
    include/TabHandleCSV.h
    include/TabHandleTXT.h
    include/WidgetFunctional.h
    include/TabAbstract.h
#    include/TabHandleIMG.h

    ${UI_FILES}
    ../resources/res.qrc

)

# 添加 include 目录
target_include_directories(mytxt_executable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../userinfo
    ${CMAKE_CURRENT_SOURCE_DIR}/../manager
)

add_subdirectory(../email/simple-mail ${CMAKE_CURRENT_BINARY_DIR}/email/simple-mail)

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
    mytxt_email
    mytxt_draw
    SimpleMail::Core
)

# 设置可执行文件的属性
set_target_properties(mytxt_executable PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
