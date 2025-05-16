cmake_minimum_required(VERSION 3.5)

# 设置项目名称和版本
project(SmartDesk VERSION 0.1 LANGUAGES CXX)


# 查找 Qt 库 (仅在主目录调用一次)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Sql Network Svg)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Network Svg)

# 启用自动处理 Qt 的 uic, moc, 和 rcc
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 添加子目录
add_subdirectory(manager)
add_subdirectory(FileBackup)
add_subdirectory(FileSystem)
add_subdirectory(OnlineDoc)
add_subdirectory(TagSchedule)
add_subdirectory(Setting)
add_subdirectory(UserInfo)
add_subdirectory(EmailService)
add_subdirectory(MoreFunction)
add_subdirectory(ClipBoard)
add_subdirectory(DisposeAbstract/DisposeTXT)
add_subdirectory(DisposeAbstract/DisposeCSV)
add_subdirectory(DisposeAbstract/DisposeIMG)
add_subdirectory(DisposeAbstract/DisposeXLSX)
add_subdirectory(main)


add_subdirectory(Resources/ThirdParty/simple-mail/
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/ThirdParty/simple-mail)

add_subdirectory(Resources/ThirdParty/QXlsx/
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/ThirdParty/QXlsx)

# add_subdirectory(Resources/ThirdParty/LmsgNotify/
#     ${CMAKE_CURRENT_BINARY_DIR}/Resources/ThirdParty/LmsgNotify)

qt_add_resources(RESOURCES
    Resources/res.qrc
)

qt_add_executable(SmartDesk WIN32 ${RESOURCES}
    DisposeAbstract/DisposeXlsx/TabHandleXLSX.h DisposeAbstract/DisposeXlsx/TabHandleXLSX.cpp)
target_link_libraries(SmartDesk PRIVATE
    mytxt_main
    mytxt_filehis
    mytxt_filetag
    mytxt_onlinedoc
    mytxt_schedule
    mytxt_setting
    mytxt_userinfo
    mytxt_email
    mytxt_txt
    mytxt_csv
    mytxt_img
    mytxt_xlsx
    mytxt_manager
    mytxt_morefunction
    mytxt_clipboard
    SimpleMail::Core
    QXlsx::QXlsx
    # LmsgNotify::LmsgNotify
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 安装规则
include(GNUInstallDirs)
install(TARGETS SmartDesk
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 如果使用 Qt6，则需要调用 qt_finalize_executable
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartDesk)
endif()
