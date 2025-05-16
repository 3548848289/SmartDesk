set(SCHEDULE_SOURCES
   SendEmail.cpp
)

set(SCHEDULE_HEADERS
    SendEmail.h
)

qt_add_library(mytxt_email STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
    SendEmail.ui
)

target_link_libraries(mytxt_email PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(mytxt_email PRIVATE
    SimpleMail::Core
)

target_include_directories(mytxt_email PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Resources/ThirdParty/simple-mail/src
)

target_include_directories(mytxt_email PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# cmake_minimum_required(VERSION 3.16)

# # 设置项目名称
# project(Email)

# # 查找 Qt 库
# find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# # 添加源文件
# set(SOURCES
#     SendEmail.cpp
# )

# set(HEADERS
#     SendEmail.h
# )

# set(UI_SOURCES
#    SendEmail.ui
# )

# # 添加库文件（静态或共享库）
# qt_add_library(mytxt_email
#     ${SOURCES}
#     ${HEADERS}
#     ${UI_SOURCES}  # 包含处理后的 UI 源代码
# )

# # 包含目录
# target_include_directories(mytxt_email PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# # 链接 Qt 库
# target_link_libraries(mytxt_email PRIVATE
#     Qt${QT_VERSION_MAJOR}::Widgets
# )

# # 设置库的属性
# set_target_properties(mytxt_email PROPERTIES
#     CXX_STANDARD 17
#     CXX_STANDARD_REQUIRED ON
# )

# # 链接 SimpleMail 库
# target_link_libraries(mytxt_email PRIVATE SimpleMail::Core)

