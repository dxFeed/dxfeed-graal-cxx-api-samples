cmake_minimum_required(VERSION 3.20)
project(dxFeedGraalCxxApiSample)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party/dxfeed-graal-cxx-api)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} dxfcxx)
target_compile_definitions(${PROJECT_NAME} PRIVATE DXFCPP_USE_DLLS)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:dxfcxx::graal>
        $<TARGET_FILE:dxfcxx>
        ${CMAKE_CURRENT_SOURCE_DIR}/dxfeed.properties
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
