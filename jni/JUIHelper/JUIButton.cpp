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

#include "JUIButton.h"

#include "JUIWindow.h"

namespace ndkGui {

/*
 * Button
 */
JUIButton::JUIButton() : JUITextView(false), onclick_callback_(NULL) { Init(); }

JUIButton::JUIButton(const char *str) : JUITextView(false) {
  Init();
  SetAttribute("Text", str);
}

JUIButton::JUIButton(const bool b) : JUITextView(false) {
  if (b == true) JUIButton();
}

void JUIButton::Init() {
  obj_ = JUIWindow::GetInstance()->CreateWidget("JUIButton", this);
  if (obj_ == NULL) LOGI("Class initialization failure");
}

JUIButton::~JUIButton() {
  if (obj_ != NULL) {
    ndkGui::JUIWindow::GetInstance()->CloseWidget(obj_);
    obj_ = NULL;
  }
}

void JUIButton::Restore() {
  // Recreate Java Widget when the activity has been disposed
  obj_ = JUIWindow::GetInstance()->CreateWidget("JUIButton", this);
  if (obj_ == NULL) LOGI("Class initialization failure");

  RestoreParameters(map_attributes_);
}

void JUIButton::DispatchEvent(const int32_t message, const int32_t param1,
                              const int32_t param2) {
  if (onclick_callback_ != NULL) onclick_callback_(this, message);
}

bool JUIButton::SetCallback(
    std::function<void(ndkGui::JUIView *, const int32_t)> callback) {
  bool b = true;
  onclick_callback_ = callback;
  return b;
}

}  // namespace ndkGui

