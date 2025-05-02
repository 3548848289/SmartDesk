set(SCHEDULE_SOURCES
   TabHandleXLSX.cpp
)

set(SCHEDULE_HEADERS
    TabHandleXLSX.h
)

qt_add_library(mytxt_xlsx STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
)

target_link_libraries(mytxt_xlsx PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(mytxt_xlsx PRIVATE
    QXlsx::QXlsx
)

target_include_directories(mytxt_xlsx PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Resources/ThirdParty/QXlsx/header
)

target_include_directories(mytxt_xlsx PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
