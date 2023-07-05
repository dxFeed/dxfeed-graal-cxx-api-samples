# Copyright (c) 2023 Devexperts LLC.
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.25)

project(dllsample-sample)

set(CMAKE_C_STANDARD 11)

add_executable(dllsample-sample main.c)

target_link_libraries(dllsample-sample dllsample-plugin-api)

add_custom_command(TARGET dllsample-sample POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:dllsample-dxfeed-plugin>
        $<TARGET_FILE:dxfcxx::graal>
        $<TARGET_FILE:dxfcxx>
        $<TARGET_FILE_DIR:dllsample-sample>)