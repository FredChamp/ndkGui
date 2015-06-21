/*
 * Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NDKGUI_JUIDIALOG_H__
#define __NDKGUI_JUIDIALOG_H__

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include "JUIView.h"
#include "JUIWindow.h"

namespace ndkGui {
/*
 * JUIDialog represents a dialog framgent
 * An application can create JUIView based classes and add them to JUIDialog to
 * show Java Widget over
 * native activity.
 */

class JUIDialog : public JUIBase {
  /*
   * These classes need to be a friend class to access protected methods
   */
  friend class JUIView;
  friend class JUITextView;
  friend class JUIButton;
  friend class JUIWindow;

 public:
  JUIDialog();
  explicit JUIDialog(ANativeActivity *activity);
  virtual ~JUIDialog();

  /*
   * Initialize window with an activity
   */
  void Init(ANativeActivity *activity);

  /*
   * Close the dialog
   */
  void Close();

  /*
   * Show dialog
   */
  void Show();

  /*
   * Add JUIView classes to the dialog
   */
  void AddView(JUIView *view);

  /*
   * Set a callback to dialog life cycle event
   */
  bool SetCallback(const int32_t message,
                   std::function<void(ndkGui::JUIDialog *dialog,
                                      const int32_t message)> callback);

  /*
   * Dispatch Widget events. This one is called from Java code through
   * Java_com_sample_helper_JUIHelper_JUICallbackHandler()
   */
  virtual void DispatchEvent(const int32_t message, const int32_t param1,
                             const int32_t param2);

  /*
   * Set attributes to the component
   * For a list of attributes, refer attributes_ array
   */
  template <typename T>
  bool SetAttribute(const char *strAttribute, const T t) {
    return JUIBase::SetAttribute(map_attributes_, strAttribute, t);
  }

  bool SetAttribute(const char *strAttribute, const char *str) {
    return JUIBase::SetAttribute(map_attributes_, strAttribute, str);
  }

 protected:
  static const AttributeType attributes_[];
  static std::unordered_map<std::string, int32_t> map_attributes_;

  ANativeActivity *activity_;
  std::vector<JUIView *> views_;
  bool suspended_;

  std::function<void(ndkGui::JUIDialog *dialog, const int32_t message)>
      dismiss_callback_;
  std::function<void(ndkGui::JUIDialog *dialog, const int32_t message)>
      cancel_callback_;

  void CreateDialog();
  void DeleteObject();
  virtual void Suspend();
  virtual void Resume(ANativeActivity *activity);
  void RestoreParameters(std::unordered_map<std::string, int32_t> &map);
};
}  // namespace ndkHelper
#endif  // __NDKGUI_JUIDIALOG_H__
