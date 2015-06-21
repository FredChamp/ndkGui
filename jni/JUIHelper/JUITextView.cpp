#include "JUITextView.H"

#include "JUIWindow.h"

namespace ndkGui
{
std::unordered_map<std::string, int32_t> JUITextView::map_attributes_;
const AttributeType JUITextView::attributes_[] = {
    {"AutoLinkMask", ATTRIBUTE_PARAMETER_INT},
    {"Text", ATTRIBUTE_PARAMETER_STRING},
    {"CursorVisible", ATTRIBUTE_PARAMETER_BOOLEAN},
    {"CompoundDrawablesWithIntrinsicBounds", ATTRIBUTE_PARAMETER_IIII},
    {"CompoundDrawablesRelativeWithIntrinsicBounds", ATTRIBUTE_PARAMETER_IIII},
    {"CompoundDrawablePadding", ATTRIBUTE_PARAMETER_INT},
    {"InputExtras", ATTRIBUTE_PARAMETER_INT},
    {"Ellipsize", ATTRIBUTE_PARAMETER_INT /*TextUtils.TruncateAt*/},
    {"Ems", ATTRIBUTE_PARAMETER_INT},
    {"Typeface", ATTRIBUTE_PARAMETER_INT /*Typeface*/},
    {"FreezesText", ATTRIBUTE_PARAMETER_BOOLEAN},
    {"Gravity", ATTRIBUTE_PARAMETER_INT},
    {"Height", ATTRIBUTE_PARAMETER_INT},
    {"Hint", ATTRIBUTE_PARAMETER_INT},
    {"ImeOptions", ATTRIBUTE_PARAMETER_INT},
    {"IncludeFontPadding", ATTRIBUTE_PARAMETER_BOOLEAN},
    {"RawInputType", ATTRIBUTE_PARAMETER_INT},
    {"LineSpacing", ATTRIBUTE_PARAMETER_FF},
    {"Lines", ATTRIBUTE_PARAMETER_INT},
    {"LinksClickable", ATTRIBUTE_PARAMETER_BOOLEAN},
    {"MarqueeRepeatLimit", ATTRIBUTE_PARAMETER_INT},
    {"MaxEms", ATTRIBUTE_PARAMETER_INT},
    {"MaxHeight", ATTRIBUTE_PARAMETER_INT},
    {"MaxLines", ATTRIBUTE_PARAMETER_INT},
    {"MaxWidth", ATTRIBUTE_PARAMETER_INT},
    {"MinEms", ATTRIBUTE_PARAMETER_INT},
    {"MinHeight", ATTRIBUTE_PARAMETER_INT},
    {"MinLines", ATTRIBUTE_PARAMETER_INT},
    {"MinWidth", ATTRIBUTE_PARAMETER_INT},
    {"PrivateImeOptions", ATTRIBUTE_PARAMETER_STRING},
    {"HorizontallyScrolling", ATTRIBUTE_PARAMETER_BOOLEAN},
    {"SelectAllOnFocus", ATTRIBUTE_PARAMETER_BOOLEAN},
    {"ShadowLayer", ATTRIBUTE_PARAMETER_FFFI},
    {"AllCaps", ATTRIBUTE_PARAMETER_BOOLEAN},
    {"TextColor", ATTRIBUTE_PARAMETER_INT},
    {"HighlightColor", ATTRIBUTE_PARAMETER_INT},
    {"HintTextColor", ATTRIBUTE_PARAMETER_INT},
    {"LinkTextColor", ATTRIBUTE_PARAMETER_INT},
    {"TextScaleX", ATTRIBUTE_PARAMETER_FLOAT},
    {"TextSize", ATTRIBUTE_PARAMETER_IF},
    {"Width", ATTRIBUTE_PARAMETER_INT}};

JUITextView::JUITextView() : JUIView() {
  obj_ = JUIWindow::GetInstance()->CreateWidget("JUITextView", this);
  if (obj_ == NULL) LOGI("Class initialization failure");

  Init();
}

JUITextView::JUITextView(const char *str) : JUIView() {
  obj_ = JUIWindow::GetInstance()->CreateWidget("JUITextView", this);
  if (obj_ == NULL) LOGI("Class initialization failure");

  Init();
  SetAttribute("Text", str);
}

JUITextView::JUITextView(const bool b) : JUIView() {
  if (b == true)
    JUITextView();
  else
    Init();
}

void JUITextView::Init() {
  // setup attribute map (once)
  if (map_attributes_.size() == 0) {
    // Add base class's map
    map_attributes_.insert(JUIView::map_attributes_.begin(),
                           JUIView::map_attributes_.end());

    for (int32_t i = 0; i < sizeof(attributes_) / sizeof(attributes_[0]); ++i) {
      map_attributes_[std::string(attributes_[i].attribute_name)] =
          attributes_[i].attribute_type;
    }
  }
}

JUITextView::~JUITextView() {
  if (obj_ != NULL) {
    ndkGui::JUIWindow::GetInstance()->CloseWidget(obj_);
    obj_ = NULL;
  }
}

void JUITextView::Restore() {
  // Recreate Java Widget when the activity has been disposed
  obj_ = JUIWindow::GetInstance()->CreateWidget("JUITextView", this);
  if (obj_ == NULL) LOGI("Class initialization failure");

  RestoreParameters(map_attributes_);
}
} //ndkGui