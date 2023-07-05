# Copyright (c) 2023 Devexperts LLC.
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.25)

add_library(dllsample-dxfeed-plugin SHARED plugin.cpp)

target_link_libraries(dllsample-dxfeed-plugin dllsample-plugin-api)

include(FetchContent)

FetchContent_Declare(dxFeedGraalCxxApi GIT_REPOSITORY "https://github.com/dxFeed/dxfeed-graal-cxx-api.git" GIT_TAG v0.0.1-alpha)
FetchContent_MakeAvailable(dxFeedGraalCxxApi)

target_link_libraries(dllsample-dxfeed-plugin dxfcxx)
target_compile_definitions(dllsample-dxfeed-plugin PRIVATE DXFCPP_USE_DLLS DLLSAMPLE_EXPORTS)

add_custom_command(TARGET dllsample-dxfeed-plugin POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:dxfcxx::graal>
        $<TARGET_FILE:dxfcxx>
        $<TARGET_FILE_DIR:dllsample-dxfeed-plugin>)