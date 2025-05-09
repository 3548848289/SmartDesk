set(SETTING_SOURCES
    Setting.cpp
    SettingManager.cpp
    AppHelp.cpp

)

set(SETTING_HEADERS
    include/Setting.h
    include/SettingManager.h
    include/AppHelp.h
)

set(SETTING_UIS
    ui/Setting.ui
    ui/AppHelp.ui
)

qt_add_library(mytxt_setting STATIC
    ${SETTING_SOURCES}
    ${SETTING_HEADERS}
    ${SETTING_UIS}
)

target_link_libraries(mytxt_setting PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_setting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
