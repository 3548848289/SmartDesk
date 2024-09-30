set(SCHEDULE_SOURCES
    WSchedule.cpp
    FileItemWidget.cpp

)

set(SCHEDULE_HEADERS
    WSchedule.h
    FileItemWidget.h

)

set(SCHEDULE_UIS
    WSchedule.ui
    FileItemWidget.ui

)

qt_add_library(mytxt_schedule STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
    ${SCHEDULE_UIS}
)

target_link_libraries(mytxt_schedule PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_schedule PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
