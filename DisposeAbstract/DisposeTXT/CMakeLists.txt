set(SCHEDULE_SOURCES
   ControlWidTXT.cpp
   TabHandleTXT.cpp
)

set(SCHEDULE_HEADERS
    ControlWidTXT.h
    TabHandleTXT.h
)


qt_add_library(mytxt_txt STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
    ControlWidTXT.ui
)

target_link_libraries(mytxt_txt PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_txt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
