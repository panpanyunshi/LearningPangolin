cmake_minimum_required(VERSION 3.6)
project(jt_test_pangolin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Pangolin 0.2 QUIET)
find_package(OpenCV QUIET)
# decide if we have pangolin
if (Pangolin_FOUND)
    message("--- found PANGOLIN, compiling dso_pangolin library.")
    include_directories( ${Pangolin_INCLUDE_DIRS} )
#    set(dso_pangolin_SOURCE_FILES
#            ${PROJECT_SOURCE_DIR}/src/IOWrapper/Pangolin/KeyFrameDisplay.cpp
#            ${PROJECT_SOURCE_DIR}/src/IOWrapper/Pangolin/PangolinDSOViewer.cpp)
    set(HAS_PANGOLIN 1)
else ()
    message("--- could not find PANGOLIN, not compiling dso_pangolin library.")
    message("    this means there will be no 3D display / GUI available for dso_dataset.")
#    set(dso_pangolin_SOURCE_FILES )
    set(HAS_PANGOLIN 0)
endif ()

# decide if we have openCV
if (OpenCV_FOUND)
    message("--- found OpenCV, compiling dso_opencv library.")
    include_directories( ${OpenCV_INCLUDE_DIRS} )
#    set(dso_opencv_SOURCE_FILES
#            ${PROJECT_SOURCE_DIR}/src/IOWrapper/OpenCV/ImageDisplay_OpenCV.cpp
#            ${PROJECT_SOURCE_DIR}/src/IOWrapper/OpenCV/ImageRW_OpenCV.cpp)
    set(HAS_OPENCV 1)
else ()
    message("--- could not find OpenCV, not compiling dso_opencv library.")
    message("    this means there will be no image display, and image read / load functionality.")
#    set(dso_opencv_SOURCE_FILES
#            ${PROJECT_SOURCE_DIR}/src/IOWrapper/ImageDisplay_dummy.cpp
#            ${PROJECT_SOURCE_DIR}/src/IOWrapper/ImageRW_dummy.cpp)
    set(HAS_OPENCV 0)
endif ()

set(SOURCE_FILES main.cpp)
add_executable(jt_test_pangolin ${SOURCE_FILES})

target_link_libraries(jt_test_pangolin  ${Pangolin_LIBRARIES} ${OpenCV_LIBS})
