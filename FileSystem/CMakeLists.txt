set(FILETAG_SOURCES
    FileSystem.cpp
    TagItemDelegate.cpp
)

set(FILETAG_HEADERS

    include/FileSystem.h
    include/TagItemDelegate.h


)

set(FILETAG_UIS
    ui/FileSystem.ui

)

qt_add_library(mytxt_filetag
    STATIC
    ${FILETAG_SOURCES}
    ${FILETAG_HEADERS}
    ${FILETAG_UIS}

)

target_link_libraries(mytxt_filetag PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_filetag PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
