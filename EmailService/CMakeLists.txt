set(SCHEDULE_SOURCES
   SendEmail.cpp
)

set(SCHEDULE_HEADERS
    SendEmail.h
)

qt_add_library(mytxt_email STATIC
    ${SCHEDULE_SOURCES}
    ${SCHEDULE_HEADERS}
    SendEmail.ui
)

target_link_libraries(mytxt_email PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(mytxt_email PRIVATE
    SimpleMail::Core
)

target_include_directories(mytxt_email PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Resources/ThirdParty/simple-mail/src
)

