file(GLOB LMSGNOTIFY_SOURCES
    LmsgNotify/*.cpp
)

file(GLOB LMSGNOTIFY_HEADERS
    LmsgNotify/*.h
)

set(FILETAG_SOURCES
    DTag.cpp
    WSchedule.cpp
    FileItemWidget.cpp
    ${LMSGNOTIFY_SOURCES}
)

set(FILETAG_HEADERS
    include/DTag.h
    include/WSchedule.h
    include/FileItemWidget.h
    ${LMSGNOTIFY_HEADERS}
)

set(FILETAG_UIS
    ui/DTag.ui
    ui/WSchedule.ui
    ui/FileItemWidget.ui

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
