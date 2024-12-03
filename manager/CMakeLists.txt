# 启用当前目录的包含路径
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置源文件和头文件
set(MANAGER_SOURCES
    myJson.cpp
    ServerManager.cpp
    dbManager.cpp
    dbFilepath.cpp
    dbBackupRecord.cpp

    include/dbBackupRecord.h
    include/myJson.h
    include/ServerManager.h
    include/dbManager.h
    include/dbFilepath.h
    include/dbService.h
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
