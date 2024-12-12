set(SCHEDULE_SOURCES
   TabHandleIMG.cpp
   ControlFrame.cpp
   PixItem.cpp
)

set(SCHEDULE_HEADERS
    TabHandleIMG.h
    ControlFrame.h
    PixItem.h
)


qt_add_library(mytxt_draw STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
    ControlFrame.ui
)

target_link_libraries(mytxt_draw PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_draw PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
