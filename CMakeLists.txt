project(FeedBacker)
cmake_minimum_required(VERSION 2.8)
# Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local")
set(CMAKE_BUILD_TYPE Debug)

get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
include(FeatureSummary)

aux_source_directory(./src/ SRC_LIST)
aux_source_directory(./src/GUI SRC_LIST)
#set(GUI_SRC ./src/GUI/AboutDialog.cpp ./src/GUI/MainWindow.cpp ./src/GUI/NewStudentDialog.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/res/feedbacker.sqlite DESTINATION ${CMAKE_BINARY_DIR}/res)

find_package(Qt5Widgets REQUIRED)

qt5_wrap_ui(UI_HEADERS ./src/GUI/MainWindow.ui ./src/GUI/AboutDialog.ui ./src/GUI/NewStudentDialog.ui
                ./src/GUI/StudentsWindow.ui ./src/GUI/NewCourseDialog.ui)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${UI_HEADERS})

target_link_libraries(${PROJECT_NAME} vmime sqlite3 Qt5::Widgets)

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
#set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")




feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

