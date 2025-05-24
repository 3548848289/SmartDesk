set(ONLINEDOC_SOURCES
    SharedView.cpp
    DownloadView.cpp
    EditedLog.cpp
    WOnlineDoc.cpp
)

set(ONLINEDOC_HEADERS
    include/SharedView.h
    include/DownloadView.h
    include/EditedLog.h
    include/WOnlineDoc.h
)

set(ONLINEDOC_UIS
    ui/SharedView.ui
    ui/DownloadView.ui
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
