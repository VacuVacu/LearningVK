cmake_minimum_required(VERSION 3.22)

project ("LearnVulkan")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

message("current dir=" ${CMAKE_SOURCE_DIR})

#include_directories(${CMAKE_SOURCE_DIR}/packages/glfw/include)
link_directories(${CMAKE_SOURCE_DIR}/packages/glfw/lib)

include_directories(${CMAKE_SOURCE_DIR}/packages/glm)

file(GLOB_RECURSE SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/sources/*.cpp 
    ${CMAKE_SOURCE_DIR}/sources/*.h
)
add_executable(${PROJECT_NAME}  ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/packages/stb_image)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/packages/tiny_obj_loader)
target_link_libraries(${PROJECT_NAME}  glfw3.lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/packages/glfw/include)

####Vulkan
find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)