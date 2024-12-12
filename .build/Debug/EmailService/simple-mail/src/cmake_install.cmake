# Install script for directory: D:/CxxProgram/SmartDesk/EmailService/simple-mail/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/SimpleMail3Qt6")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/QT6/Tools/mingw1310_64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/CxxProgram/SmartDesk/.build/debug/EmailService/simple-mail/src/libSimpleMail3Qt6.dll.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/CxxProgram/SmartDesk/.build/debug/EmailService/simple-mail/src/libSimpleMail3Qt6.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSimpleMail3Qt6.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSimpleMail3Qt6.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/QT6/Tools/mingw1310_64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSimpleMail3Qt6.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/simplemail3-qt6/SimpleMail" TYPE FILE FILES
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/emailaddress.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimeattachment.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimecontentformatter.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimefile.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimehtml.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimeinlinefile.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimemessage.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimemultipart.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimepart.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/mimetext.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/quotedprintable.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/server.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/serverreply.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/smtpexports.h"
    "D:/CxxProgram/SmartDesk/EmailService/simple-mail/src/SimpleMail"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/CxxProgram/SmartDesk/.build/debug/EmailService/simple-mail/src/SimpleMail3Qt6.pc")
endif()

