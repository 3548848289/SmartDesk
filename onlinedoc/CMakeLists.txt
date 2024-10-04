set(ONLINEDOC_SOURCES
    csvLinkServer2.cpp
    DLfromNet.cpp
    EditedLog.cpp
    WOnlineDoc.cpp
)

set(ONLINEDOC_HEADERS
    include/csvLinkServer2.h
    include/DLfromNet.h
    include/EditedLog.h
    include/WOnlineDoc.h
)

set(ONLINEDOC_UIS
    ui/csvLinkServer2.ui
    ui/DLfromNet.ui
    ui/WOnlineDoc.ui
)

qt_add_library(mytxt_onlinedoc STATIC
    ${ONLINEDOC_SOURCES}
    ${ONLINEDOC_HEADERS}
    ${ONLINEDOC_UIS}
)

target_link_libraries(mytxt_onlinedoc PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network

)

target_include_directories(mytxt_onlinedoc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}

)
