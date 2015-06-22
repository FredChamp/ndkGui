cmake_minimum_required(VERSION 2.8)
project(AndroidNDK-GUI)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/jni/JNIHelper
    ${CMAKE_CURRENT_SOURCE_DIR}/jni/JUIHelper
    ${ANDROID_NDK}/sources/android/native_app_glue
)

add_subdirectory(jni/JNIHelper)
add_subdirectory(jni/JUIHelper)

install(DIRECTORY src/com
        DESTINATION ${CMAKE_INSTALL_PREFIX}/src
        )