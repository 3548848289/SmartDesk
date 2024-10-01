cmake_minimum_required(VERSION 3.5)

# 设置项目名称和版本
project(mytxt_cmake VERSION 0.1 LANGUAGES CXX)

# 查找 Qt 库
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Sql Network)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Network)

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
add_subdirectory(main)
add_subdirectory(email)




# 安装规则
include(GNUInstallDirs)
install(TARGETS mytxt_executable
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 如果使用 Qt6，则需要调用 qt_finalize_executable
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mytxt_executable
)
endif()
