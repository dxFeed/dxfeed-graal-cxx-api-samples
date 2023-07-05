cmake_minimum_required(VERSION 3.25)
project(dllsample)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(plugin-api)
add_subdirectory(dxfeed-plugin)
add_subdirectory(sample)

add_dependencies(dllsample-dxfeed-plugin dllsample-plugin-api)
add_dependencies(dllsample-sample dllsample-plugin-api dllsample-dxfeed-plugin)




