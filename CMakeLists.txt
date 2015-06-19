cmake_minimum_required(VERSION 2.8)
project(AndroidNDK-GUI)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )

include_directories(
    ${ANDROID_NDK}/sources/android/native_app_glue
    ${ANDROID_NDK}/sources/android/cpufeaturess
    ${ANDROID_NDK}/sources/android/ndk_helper
    ${ANDROID_NDK}/platforms/android-${ANDROID_NATIVE_API_LEVEL}/arch-${ANDROID_ARCH_NAME}/usr/include
)

add_subdirectory(JNIHelper)
add_subdirectory(JUIHelper)

