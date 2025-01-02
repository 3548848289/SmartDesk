set(FILEHIS_SOURCES
    FileRestoreWid.cpp
    FileBackupView.cpp
    FileBackupWid.cpp
)

set(FILEHIS_HEADERS
    include/FileRestoreWid.h
    include/FileBackupView.h
    include/FileBackupWid.h
)

set(FILEHIS_UIS
    ui/FileRestoreWid.ui
    ui/FileBackupView.ui
    ui/FileBackupWid.ui
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
