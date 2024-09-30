set(FILEHIS_SOURCES
    DPull.cpp
    WFileHis.cpp
)

set(FILEHIS_HEADERS
    DPull.h
    WFileHis.h

)

set(FILEHIS_UIS
    DPull.ui
    WFileHis.ui
)

qt_add_library(mytxt_filehis STATIC
    ${FILEHIS_SOURCES}
    ${FILEHIS_HEADERS}
    ${FILEHIS_UIS}
)

target_link_libraries(mytxt_filehis PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

target_include_directories(mytxt_filehis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
