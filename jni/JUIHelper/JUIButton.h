#ifndef __NDKGUI_JUIBUTTON_H__
#define __NDKGUI_JUIBUTTON_H__

#include "JUIView.h"
#include "JUITextView.h"

namespace ndkGui
{
/*
 * JUIButton
 */
class JUIButton : public JUITextView {
 public:
  JUIButton();
  explicit JUIButton(const char *str);
  virtual ~JUIButton();

  /*
   * Dispatch Widget events. This one is called from Java code through
   * Java_com_sample_helper_JUIHelper_JUICallbackHandler()
   */
  virtual void DispatchEvent(const int32_t message, const int32_t param1,
                             const int32_t param2);

  /*
   * Set callback to an input event
   */
  bool SetCallback(
      std::function<void(ndkGui::JUIView *, const int32_t)> callback);

 private:
  void Init();
  std::function<void(ndkGui::JUIView *, const int32_t)> onclick_callback_;

 protected:
  explicit JUIButton(const bool b);
  virtual void Restore();
};
} // ndkGui

#endif // __NDKGUI_JUIBUTTON_H__