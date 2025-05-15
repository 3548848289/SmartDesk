set(SCHEDULE_SOURCES
   TabHandleIMG.cpp
   ControlFrame.cpp
   PixItem.cpp
   WaterMark.cpp
)

set(SCHEDULE_HEADERS
    include/TabHandleIMG.h
    include/ControlFrame.h
    include/PixItem.h
    include/WaterMark.h
)


qt_add_library(mytxt_img STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
    ui/ControlFrame.ui

)


target_link_libraries(mytxt_img PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::SvgWidgets
)

target_include_directories(mytxt_img PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
