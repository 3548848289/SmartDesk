# 设置 Qt 的 CMake 配置路径（根据你的 Qt 安装位置）
set(CMAKE_PREFIX_PATH "D:/Qt/6.8.0/mingw_64/lib/cmake/Qt6")

# 启用当前目录的包含路径
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置源文件和头文件
set(MANAGER_SOURCES
    DBMySQL.cpp
    DBSQlite.cpp
    myJson.cpp
    ServerManager.cpp

    include/myJson.h
    include/DBMySQL.h
    include/DBSQlite.h
    include/ServerManager.h
)

# 查找 Qt 库
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql Widgets Network)

# 添加静态库
qt_add_library(mytxt_manager STATIC
    ${MANAGER_SOURCES}
)

# 链接 Qt 库（包括 Network, Sql 和 Widgets）
target_link_libraries(mytxt_manager PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

# 使用 Qt6Network_INCLUDE_DIRS 添加头文件路径
target_include_directories(mytxt_manager PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6Network_INCLUDE_DIRS}  # 从 Qt6Network 获取的头文件路径
)

# 打印调试信息，确认 Qt 网络模块是否被正确找到
message(STATUS "Qt Network found: ${Qt6Network_FOUND}")
message(STATUS "Qt Network include dir: ${Qt6Network_INCLUDE_DIRS}")
