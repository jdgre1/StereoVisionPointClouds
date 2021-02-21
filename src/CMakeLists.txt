

### ~~~~~~~~~~~~ BUILD RELEVANT LIBRARIES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

add_library(StereoVisionPointClouds STATIC stereo_vis_pcd.cpp ../include/stereo_vis_pcd.h)
target_link_libraries(StereoVisionPointClouds ${OpenCV_LIBS})



### ~~~~~~~~~~~~ CREATE EXECUTABLE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(project_sources main.cpp StereoVisionRun.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${project_sources} )
target_link_libraries( ${CMAKE_PROJECT_NAME} StereoVisionPointClouds ) 
target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE ../include/pch.h)


