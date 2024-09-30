# manager/CMakeLists.txt

set(MANAGER_SOURCES
    DBMySQL.cpp
    DBMySQL.h
    DBSQlite.cpp
    DBSQlite.h
    myJson.cpp
    myJson.h
    ServerManager.cpp
    ServerManager.h

)

# 查找 Qt 库

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql Widgets)

# 添加库
qt_add_library(mytxt_manager STATIC
    ${MANAGER_SOURCES}
)

# 链接 Qt SQL 和 Widgets 库
target_link_libraries(mytxt_manager PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

# 包含头文件目录
target_include_directories(mytxt_manager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
