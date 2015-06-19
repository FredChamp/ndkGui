include_directories(
    ${CMAKE_SOURCE_DIR}/JNIHelper
)
set(sources
  JavaUI.h
  JavaUI.cpp
  JavaUI_Dialog.cpp
  JavaUI_View.h
  JavaUI_Window.cpp
)

add_library(JUIHelper SHARED ${sources})

target_link_libraries(JUIHelper
    JNIHelper
)
