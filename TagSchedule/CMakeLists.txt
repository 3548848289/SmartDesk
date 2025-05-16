# set(FILETAG_SOURCES
#     AddTag.cpp
#     ScheduleWid.cpp
#     TagList.cpp
#     TagDetail.cpp
# )

# set(FILETAG_HEADERS
#     include/AddTag.h
#     include/ScheduleWid.h
#     include/TagList.h
#     include/TagDetail.h
# )

# set(FILETAG_UIS
#     ui/AddTag.ui
#     ui/ScheduleWid.ui
#     ui/TagList.ui
#     ui/TagDetail.ui

# )

# qt_add_library(mytxt_schedule
#     STATIC
#     ${FILETAG_SOURCES}
#     ${FILETAG_HEADERS}
#     ${FILETAG_UIS}


# )


# target_link_libraries(mytxt_schedule PRIVATE
#     Qt${QT_VERSION_MAJOR}::Widgets
#     LmsgNotify::LmsgNotify
# )

# target_include_directories(mytxt_schedule PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Resources/ThirdParty/LmsgNotify/include
# )


file(GLOB LMSGNOTIFY_SOURCES
    LmsgNotify/*.cpp
)

file(GLOB LMSGNOTIFY_HEADERS
    LmsgNotify/*.h
)

set(FILETAG_SOURCES
    AddTag.cpp
    ScheduleWid.cpp
    TagList.cpp
    TagDetail.cpp
    ${LMSGNOTIFY_SOURCES}
)

set(FILETAG_HEADERS
    include/AddTag.h
    include/ScheduleWid.h
    include/TagList.h
    include/TagDetail.h
    ${LMSGNOTIFY_HEADERS}
)

set(FILETAG_UIS
    ui/AddTag.ui
    ui/ScheduleWid.ui
    ui/TagList.ui
    ui/TagDetail.ui

)

qt_add_library(mytxt_schedule
    STATIC
    ${FILETAG_SOURCES}
    ${FILETAG_HEADERS}
    ${FILETAG_UIS}


)

target_link_libraries(mytxt_schedule PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(mytxt_schedule PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
