set(FILETAG_SOURCES
    DTag.cpp
    DCommit.cpp
    WFileTag.cpp
    TagItemDelegate.cpp
)

set(FILETAG_HEADERS
    include/DTag.h
    include/DCommit.h
    include/WFileTag.h
    include/TagItemDelegate.h


)

set(FILETAG_UIS
    ui/WFileTag.ui
    ui/DCommit.ui
    ui/DTag.ui

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
