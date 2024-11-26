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
add_subdirectory(filehis)
add_subdirectory(filetag)
add_subdirectory(onlinedoc)
add_subdirectory(schedule)
add_subdirectory(setting)
add_subdirectory(userinfo)
add_subdirectory(email)
add_subdirectory(draw)
add_subdirectory(main)

# 添加 SimpleMail 库（已经在 email/CMakeLists.txt 中处理）
add_subdirectory(email/simple-mail ${CMAKE_CURRENT_BINARY_DIR}/email/simple-mail)

# 添加资源文件
qt_add_resources(RESOURCES
    resources/res.qrc
)

#定义最终的可执行文件
qt_add_executable(SmartDesk ${RESOURCES})

# 链接所有库，包括 mytxt_email（从 email 子目录构建的库）
target_link_libraries(SmartDesk PRIVATE
    mytxt_main           # main 子目录生成的静态库
    mytxt_filehis
    mytxt_filetag
    mytxt_manager
    mytxt_onlinedoc
    mytxt_schedule
    mytxt_setting
    mytxt_userinfo
    mytxt_email          # 确保链接到 mytxt_email
    mytxt_draw
    SimpleMail::Core     # 链接 SimpleMail 核心库
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
