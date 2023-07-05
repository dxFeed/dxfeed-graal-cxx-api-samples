cmake_minimum_required(VERSION 3.25)

add_library(dllsample-plugin-api INTERFACE)

target_sources(dllsample-plugin-api PUBLIC FILE_SET HEADERS BASE_DIRS . FILES plugin-api.h)