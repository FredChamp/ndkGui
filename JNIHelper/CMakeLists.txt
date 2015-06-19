set(sources
  JNIHelper.h
  JNIHelper.cpp
)


add_library(JNIHelper SHARED ${sources})

target_link_libraries(JNIHelper
    log
    android
    log
    EGL
    GLESv2
)