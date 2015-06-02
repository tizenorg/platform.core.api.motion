CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(motion)

# Source Lists
SET(SRCS
	src/shared/ctx_util_misc.cpp
	src/shared/ctx_util_sensor.cpp
# Gesture
	src/gesture/gesture.cpp
	src/gesture/motion_engine.cpp
# Activity
	src/activity/activity.cpp
)

# Dependencies
SET(dependency "dlog glib-2.0 capi-base-common capi-system-info sensor")

# Target packages
SET(target "core-context-manager")

# Options
SET(CMAKE_INSTALL_PREFIX /usr)
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
INCLUDE(FindPkgConfig)
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src/shared
	/usr/include
	/usr/include/glib-2.0
	/usr/include/dbus-1.0
)

ADD_DEFINITIONS(-O2 -Wall -fPIC -fvisibility=hidden -Wl,--as-needed -Wl,--rpath=/usr/lib)

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
INSTALL(TARGETS ${target} DESTINATION lib)
INSTALL(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include/motion
	FILES_MATCHING PATTERN "*.h"
)

SET(PC_NAME ${target})
SET(PC_INCLUDE "/usr/include/motion")
SET(PC_DESCRIPTION "Tizen Native Motion Recognition API")
SET(PC_REQUIRED ${dependency})
SET(PC_LDFLAGS -l${target})
SET(PC_CFLAGS -I\${includedir}/motion)

CONFIGURE_FILE(
	motion.pc.in
	${CMAKE_CURRENT_SOURCE_DIR}/motion.pc
	@ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/motion.pc DESTINATION lib/pkgconfig)
