set(USERINFO_SOURCES
    DInfo.cpp
    DLogin.cpp
)

set(USERINFO_HEADERS
    DInfo.h
    DLogin.h
)

set(USERINFO_UIS
    DInfo.ui
    DLogin.ui
)

qt_add_library(mytxt_userinfo STATIC
    ${USERINFO_SOURCES}
    ${USERINFO_HEADERS}
    ${USERINFO_UIS}
)

target_link_libraries(mytxt_userinfo PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_userinfo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
