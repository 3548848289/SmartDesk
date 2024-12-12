set(FILEHIS_SOURCES
    FileRestoreWid.cpp
    FileBackupList.cpp
    FileBackup.cpp
)

set(FILEHIS_HEADERS
    include/FileRestoreWid.h
    include/FileBackupList.h
    include/FileBackup.h
)

set(FILEHIS_UIS
    ui/FileRestoreWid.ui
    ui/FileBackupList.ui
    ui/FileBackup.ui
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
