CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(motion)
INCLUDE(GNUInstallDirs)

# Target lib (for backward compatibility, the below old naming is used)
SET(target "core-context-manager")

# Source Lists
FILE(GLOB SRCS src/*.cpp)

SET(inc_subdir "context-service")
SET(dependency "glib-2.0 dlog capi-base-common capi-system-info sensor")

# Options
INCLUDE(FindPkgConfig)
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

ADD_DEFINITIONS(-O2 -Wall -fPIC -fdata-sections -ffunction-sections -fvisibility=hidden)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIC -Wl,--as-needed -Wl,--gc-section -Wl,--print-gc-section")

# Build
pkg_check_modules(pkgs REQUIRED ${dependency})

FOREACH(flag ${pkgs_CFLAGS})
   SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

ADD_LIBRARY(${target} SHARED ${SRCS})
TARGET_LINK_LIBRARIES(${target} ${pkgs_LDFLAGS})
SET_TARGET_PROPERTIES(${target} PROPERTIES COMPILE_FLAGS ${EXTRA_CFLAGS})
SET_TARGET_PROPERTIES(${target} PROPERTIES COMPILE_DEFINITIONS "LOG_TAG=\"CONTEXT-LIB\"")
SET_TARGET_PROPERTIES(${target} PROPERTIES SOVERSION ${MAJORVER})
SET_TARGET_PROPERTIES(${target} PROPERTIES VERSION ${FULLVER})

# Install
INSTALL(TARGETS ${target} DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${inc_subdir}
	FILES_MATCHING PATTERN "*.h"
)

SET(VERSION ${FULLVER})
SET(PC_PREFIX ${CMAKE_INSTALL_PREFIX})
SET(PC_NAME ${PROJECT_NAME})
SET(PC_LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
SET(PC_INCLUDE "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${inc_subdir}")
SET(PC_DESCRIPTION "Tizen Native Motion Recognition API")
SET(PC_REQUIRED ${dependency})
SET(PC_LDFLAGS -l${target})
SET(PC_CFLAGS -I\${includedir}/${inc_subdir})

CONFIGURE_FILE(
	${PROJECT_NAME}.pc.in
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc
	@ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
