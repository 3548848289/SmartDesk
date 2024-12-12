file(GLOB LMSGNOTIFY_SOURCES
    LmsgNotify/*.cpp
)

file(GLOB LMSGNOTIFY_HEADERS
    LmsgNotify/*.h
)

set(FILETAG_SOURCES
    AddTag.cpp
    ScheduleWid.cpp
    TagList.cpp
    ${LMSGNOTIFY_SOURCES}
)

set(FILETAG_HEADERS
    include/AddTag.h
    include/ScheduleWid.h
    include/TagList.h
    ${LMSGNOTIFY_HEADERS}
)

set(FILETAG_UIS
    ui/AddTag.ui
    ui/ScheduleWid.ui
    ui/TagList.ui

)

qt_add_library(mytxt_schedule
    STATIC
    ${FILETAG_SOURCES}
    ${FILETAG_HEADERS}
    ${FILETAG_UIS}


)

target_link_libraries(mytxt_schedule PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_schedule PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
