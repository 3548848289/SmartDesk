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

# 设置源文件、头文件、UI 文件和资源文件的路径
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(UI_DIR "${CMAKE_SOURCE_DIR}/ui")
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")
set(MANAGER_DIR "${CMAKE_SOURCE_DIR}/manager")

# 源文件列表

set(PROJECT_SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/mainwindow.cpp
    ${SRC_DIR}/csvLinkServer2.cpp
    ${SRC_DIR}/DLfromNet.cpp
    ${SRC_DIR}/EditedLog.cpp
    ${SRC_DIR}/Setting.cpp
    ${SRC_DIR}/TabHandleCSV.cpp
    ${SRC_DIR}/TabHandleTXT.cpp
    ${SRC_DIR}/TagItemDelegate.cpp
    ${SRC_DIR}/WFileTag.cpp
    ${SRC_DIR}/WidgetFunctional.cpp
    ${SRC_DIR}/WOnlineDoc.cpp
    ${SRC_DIR}/DLogin.cpp
    ${SRC_DIR}/WSchedule.cpp

)

# 头文件列表
set(PROJECT_HEADERS
    ${INCLUDE_DIR}/mainwindow.h
    ${INCLUDE_DIR}/csvLinkServer2.h
    ${INCLUDE_DIR}/DLfromNet.h
    ${INCLUDE_DIR}/EditedLog.h
    ${INCLUDE_DIR}/Setting.h
    ${INCLUDE_DIR}/TabAbstract.h
    ${INCLUDE_DIR}/TabHandleCSV.h
    ${INCLUDE_DIR}/TabHandleTXT.h
    ${INCLUDE_DIR}/TagItemDelegate.h
    ${INCLUDE_DIR}/WFileTag.h
    ${INCLUDE_DIR}/WidgetFunctional.h
    ${INCLUDE_DIR}/WOnlineDoc.h
    ${INCLUDE_DIR}/DLogin.h
    ${INCLUDE_DIR}/WSchedule.h
)

# UI 文件列表
set(PROJECT_UIS
    ${UI_DIR}/mainwindow.ui
    ${UI_DIR}/csvLinkServer2.ui
    ${UI_DIR}/DLfromNet.ui
    ${UI_DIR}/Setting.ui
    ${UI_DIR}/WFileTag.ui
    ${UI_DIR}/WidgetFunctional.ui
    ${UI_DIR}/WOnlineDoc.ui
    ${UI_DIR}/DLogin.ui
    ${UI_DIR}/WSchedule.ui
)

# 资源文件列表
set(PROJECT_RESOURCES
    ${RESOURCES_DIR}/res.qrc
)
set (MANAGER_RESOURCES
    ${MANAGER_DIR}/DatabaseManager.h
    ${MANAGER_DIR}/DatabaseManager.cpp
    ${MANAGER_DIR}/myJson.h
    ${MANAGER_DIR}/myJson.cpp
    ${MANAGER_DIR}/RecentFilesManager.h
    ${MANAGER_DIR}/RecentFilesManager.cpp

)

# 如果使用 Qt6
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mytxt_cmake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UIS}
        ${PROJECT_RESOURCES}
        ${MANAGER_RESOURCES}
    )
else()
    # 如果是 Android 平台
    if(ANDROID)
        add_library(mytxt_cmake SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_UIS}
            ${PROJECT_RESOURCES}
        )
    else()
        add_executable(mytxt_cmake
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_UIS}
            ${PROJECT_RESOURCES}
        )
    endif()
endif()

# 链接 Qt 库
target_link_libraries(mytxt_cmake PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

# 包含头文件的目录
target_include_directories(mytxt_cmake PRIVATE ${INCLUDE_DIR})

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
