cmake_minimum_required(VERSION 3.5)

project(mytxt_cmake VERSION 0.1 LANGUAGES CXX)

# 启用自动处理 Qt 的 uic, moc, 和 rcc
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt 库，支持 Qt5 和 Qt6
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network)

# 源文件和头文件列表
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp          mainwindow.h            mainwindow.ui

)

# 如果使用 Qt6
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mytxt_cmake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        csvLinkServer2.cpp      csvLinkServer2.h        csvLinkServer2.ui
        DatabaseManager.cpp     DatabaseManager.h
        DLfromNet.cpp           DLfromNet.h             DLfromNet.ui
        EditedLog.cpp           EditedLog.h
        myJson.cpp              myJson.h
        RecentFilesManager.cpp  RecentFilesManager.h
        Setting.cpp             Setting.h               Setting.ui

        TabHandleCSV.cpp        TabHandleCSV.h
        TabHandleTXT.cpp        TabHandleTXT.h
        TagItemDelegate.cpp     TagItemDelegate.h
        WFileTag.cpp            WFileTag.h              WFileTag.ui
        WidgetFunctional.cpp    WidgetFunctional.h      WidgetFunctional.ui
        WOnlineDoc.cpp          WOnlineDoc.h            WOnlineDoc.ui
        res.qrc
        TabAbstract.h
    )
else()
    # 如果是 Android 平台
    if(ANDROID)
        add_library(mytxt_cmake SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(mytxt_cmake
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 链接 Qt 库
target_link_libraries(mytxt_cmake PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

# 如果是 macOS 或 iOS，设置应用程序的包信息
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.mytxt_cmake)
endif()

set_target_properties(mytxt_cmake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 安装规则
include(GNUInstallDirs)
install(TARGETS mytxt_cmake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 如果使用 Qt6，则需要调用 qt_finalize_executable
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mytxt_cmake)
endif()
