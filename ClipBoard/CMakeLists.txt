set(SETTING_SOURCES
    ClipboardView.cpp
)

set(SETTING_HEADERS
    ClipboardView.h
)

set(SETTING_UIS
    ClipboardView.ui
)

qt_add_library(mytxt_clipboard STATIC
    ${SETTING_SOURCES}
    ${SETTING_HEADERS}
    ${SETTING_UIS}
)

target_link_libraries(mytxt_clipboard PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_clipboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
