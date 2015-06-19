set(sources
  JNIHelper.h
  JNIHelper.cpp
)

add_library(JNIHelper SHARED ${sources})
target_link_libraries(JNIHelper
    log
    android
)

install(TARGETS JNIHelper
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        )
install(FILES JNIHelper.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        )