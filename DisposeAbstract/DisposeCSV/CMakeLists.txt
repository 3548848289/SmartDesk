set(SCHEDULE_SOURCES
   ControlWidCSV.cpp
   TabHandleCSV.cpp
)

set(SCHEDULE_HEADERS
    ControlWidCSV.h
    TabHandleCSV.h
)

qt_add_library(mytxt_csv STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
    ControlWidcsv.ui
)

target_link_libraries(mytxt_csv PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_csv PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(mytxt_csv PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
