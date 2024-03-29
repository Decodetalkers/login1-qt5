cmake_minimum_required(VERSION 3.13)

# If do't define version number, specify the version number
if (NOT DEFINED VERSION)
    set(VERSION "1.0.0")
endif()

project(login1-qt5
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/Groveer/login1-qt5
    DESCRIPTION "login1 DBus interfaces binding for Qt5."
    VERSION ${VERSION})

include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--as-needed")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif ()

find_package(PkgConfig REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core DBus)
find_package(Doxygen)
#pkg_search_module(XCB REQUIRED xcb)

set (BUILD_DOCS ON)

if (BUILD_DOCS AND DOXYGEN_FOUND)
    set (QCH_INSTALL_DESTINATION ${CMAKE_INSTALLL_PREFIX}/share/dde/doc CACHE STRING "QCH install location")
    set (DOXYGEN_GENERATE_HTML "YES" CACHE STRING "Doxygen HTML output")
    set (DOXYGEN_GENERATE_XML "NO" CACHE STRING "Doxygen XML output")
    set (DOXYGEN_GENERATE_QHP "YES" CACHE STRING "Doxygen QHP output")
    set (DOXYGEN_FILE_PATTERNS *.cpp *.h *.md *.zh_CN.dox CACHE STRING "Doxygen File Patterns")
    set (DOXYGEN_PROJECT_NUMBER ${CMAKE_PROJECT_VERSION} CACHE STRING "") # Should be the same as this project is using.
    set (DOXYGEN_EXTRACT_STATIC YES)
    set (DOXYGEN_OUTPUT_LANGUAGE "Chinese")
    set (DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/docs/)
    set (DOXYGEN_QHG_LOCATION "qhelpgenerator")
    set (DOXYGEN_QHP_NAMESPACE "org.deepin.dde.${CMAKE_PROJECT_NAME}")
    set (DOXYGEN_QCH_FILE "${CMAKE_PROJECT_NAME}.qch")
    set (DOXYGEN_QHP_VIRTUAL_FOLDER ${CMAKE_PROJECT_NAME})
    set (DOXYGEN_HTML_EXTRA_STYLESHEET "" CACHE STRING "Doxygen custom stylesheet for HTML output")
    set (DOXYGEN_TAGFILES "qtcore.tags=qthelp://doc.qt.io/qt-5/" CACHE STRING "Doxygen tag files")
    set (DOXYGEN_MACRO_EXPANSION "YES")
    set (DOXYGEN_EXPAND_ONLY_PREDEF "YES")
    set (DOXYGEN_PREDEFINED
        "\"LOGIN1_BEGIN_NAMESPACE=namespace Login1 {\""
        "\"LOGIN1_END_NAMESPACE=}\""
        "\"LOGIN1_USE_NAMESPACE=using namespace Login1;\""
    )

    doxygen_add_docs (doxygen
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/docs
        ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generate documentation via Doxygen"
    )

    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/docs/html/${CMAKE_PROJECT_NAME}.qch DESTINATION ${QCH_INSTALL_DESTINATION})
endif ()

file(GLOB_RECURSE INCLUDE_FILES "include/*.h")
file(GLOB_RECURSE SRCS
    "src/*.h"
    "src/*.cpp"
)

set(BIN_NAME login1-qt5)

set(PC_LIBS_PRIVATE Qt5Core)
set(PC_REQ_PRIVATE)
set(PC_REQ_PUBLIC)

configure_file(misc/${BIN_NAME}.pc.in ${BIN_NAME}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BIN_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
configure_file(misc/${BIN_NAME}Config.cmake.in ${BIN_NAME}Config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BIN_NAME}Config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BIN_NAME})

add_library(${BIN_NAME} SHARED
    ${INCLUDE_FILES}
    ${SRCS})

set_target_properties(${BIN_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_compile_definitions(${BIN_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

target_include_directories(${BIN_NAME} PUBLIC
    Qt5::Core
    Qt5::DBus
    include
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt5::Core
    Qt5::DBus
)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})


file(GLOB_RECURSE TEST_FILES "tests/*.cpp")

add_executable(test
    ${INCLUDE_FILES}
    ${SRCS}
    ${TEST_FILES})

target_include_directories(test PUBLIC
    Qt5::Core
    Qt5::DBus
    include
)

target_link_libraries(test PRIVATE
    Qt5::Core
    Qt5::DBus
)

