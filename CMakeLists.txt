project(FeedBacker)
cmake_minimum_required(VERSION 2.8)
# Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(UNIX)
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local")
endif(UNIX)
set(CMAKE_BUILD_TYPE Debug)

get_cmake_property(_variableNames VARIABLES)

option(BUILD_TESTS "Build Unit tests for the Engine" OFF)
IF(BUILD_TESTS)
    message(STATUS "Building Unit tests")
    FILE(GLOB UnitTests_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "tests/Test*.cpp" )
    ADD_EXECUTABLE(UnitTester tests/runTest.cpp ${UnitTests_SRCS})
    TARGET_LINK_LIBRARIES(UnitTester cppunit)
    FOREACH(test ${UnitTests_SRCS})
            MESSAGE(STATUS "  Adding test: ${test}")
            GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
            ADD_TEST(${TestName} UnitTester ${TestName})
    ENDFOREACH(test)
ENDIF(BUILD_TESTS)


#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
include(FeatureSummary)

FILE(GLOB odb_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/presistent/*.h" )
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/src/presistent)

foreach(_file ${odb_src})
   string(REPLACE ".h" "-odb.cpp" gencppfile ${_file})
   add_custom_command(
     OUTPUT ${CMAKE_BINARY_DIR}/${gencppfile}
     COMMAND /usr/bin/odb --database sqlite --std c++11 --hxx-suffix .h
     --ixx-suffix .ipp --cxx-suffix .cpp
     --output-dir ${CMAKE_BINARY_DIR}/src/presistent
     --generate-query --generate-schema
     ${CMAKE_CURRENT_SOURCE_DIR}/${_file}
     DEPENDS ${_file}
     COMMENT "Building odb for ${_file}"
     )
   list(APPEND gen_odb_src ${CMAKE_BINARY_DIR}/${gencppfile})
endforeach()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/presistent ${CMAKE_BINARY_DIR}/src/presistent)
aux_source_directory(./src/presistent SRC_LIST)
aux_source_directory(./src/ SRC_LIST)
aux_source_directory(./src/GUI SRC_LIST)
#set(GUI_SRC ./src/GUI/AboutDialog.cpp ./src/GUI/MainWindow.cpp ./src/GUI/NewStudentDialog.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/res/feedbacker.sqlite DESTINATION ${CMAKE_BINARY_DIR}/res)

find_package(Qt5Widgets REQUIRED)

qt5_wrap_ui(UI_HEADERS ./src/GUI/MainWindow.ui ./src/GUI/AboutDialog.ui ./src/GUI/NewStudentDialog.ui
                ./src/GUI/StudentsWindow.ui ./src/GUI/NewCourseDialog.ui)

# Wrap the ODB presistent classes



add_executable(${PROJECT_NAME} ${SRC_LIST} ${UI_HEADERS} ${gen_odb_src})

target_link_libraries(${PROJECT_NAME} vmime sqlite3 odb-sqlite odb Qt5::Widgets)

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
#set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")




feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

