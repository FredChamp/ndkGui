set(HEADERS
  JavaUI.h
  JUIView.h
  JUIBase.h
  IdFactory.h

)

set(SOURCES
    JavaUI.cpp
    JavaUI_Dialog.cpp
    JavaUI_Window.cpp
)

add_library(JUIHelper SHARED ${HEADERS} ${SOURCES})

target_link_libraries(JUIHelper
    JNIHelper
)

install(TARGETS JUIHelper
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        )
install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        )