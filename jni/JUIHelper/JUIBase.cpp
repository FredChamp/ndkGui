#include "JUIBase.h"

namespace ndkGui
{
/*
 * Callback Handler for Java events
 */
extern "C" {
JNIEXPORT void Java_com_sample_helper_JUIHelper_JUICallbackHandler(
    JNIEnv *env, jobject thiz, int32_t id, int32_t message, int32_t param1,
    int32_t param2) {
  /*
   * id from Java is generated token from native side, which would be mapped back
   * into an UI pointer; so id is opaque to Java -- Java receives and returns back 
   * the same id to native side
   */
  JUIBase *p = JUIBase::id_factory_.getUIBase(id);
  if( p )
      p->DispatchEvent(message, param1, param2);
  else {
      LOGE("Failed to get JUIBase pointer for %d in %s", id, __FILE__);
  }
}
}

IdFactory JUIBase::id_factory_;

} // ndkGUi