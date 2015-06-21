set(HEADERS
    IdFactory.h
    JUIBase.h
    JUIButton.h
    JUIDialog.h
    JUITextView.h
    JUIView.h
    JUIWindow.h
)

set(SOURCES
    IdFactory.cpp
    JUIBase.cpp
    JUIButton.cpp
    JUIDialog.cpp
    JUITextView.cpp
    JUIView.cpp
    JUIWindow.cpp
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