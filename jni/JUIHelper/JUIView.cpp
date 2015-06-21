#include "JUIView.h"

#include "JUIWindow.h"
/*
 * JUIView
 */
// Attribute types for View

namespace ndkGui 
{
    
/*
* JUIView
*/
// Attribute types for View
std::unordered_map<std::string, int32_t> JUIView::map_attributes_;
const AttributeType JUIView::attributes_[] = {
   {"AccessibilityLiveRegion", ATTRIBUTE_PARAMETER_INT},
   {"Alpha", ATTRIBUTE_PARAMETER_FLOAT},
   {"BackgroundResource", ATTRIBUTE_PARAMETER_INT},
   {"Clickable", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"Enabled", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"DrawingCacheQuality", ATTRIBUTE_PARAMETER_INT},
   {"ScrollbarFadingEnabled", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"FilterTouchesWhenObscured", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"FitsSystemWindows", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"Focusable", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"FocusableATTRIBUTE_PARAMETER_INTouchMode", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"HapticFeedbackEnabled", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"Id", ATTRIBUTE_PARAMETER_INT},
   {"ImportantForAccessibility", ATTRIBUTE_PARAMETER_INT},
   {"ScrollContainer", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"KeepScreenOn", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"LayoutDirection", ATTRIBUTE_PARAMETER_INT},
   {"LongClickable", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"MinimumHeight", ATTRIBUTE_PARAMETER_INT},
   {"MinimumWidth", ATTRIBUTE_PARAMETER_INT},
   {"NextFocusDownId", ATTRIBUTE_PARAMETER_INT},
   {"NextFocusForwardId", ATTRIBUTE_PARAMETER_INT},
   {"NextFocusLeftId", ATTRIBUTE_PARAMETER_INT},
   {"NextFocusRightId", ATTRIBUTE_PARAMETER_INT},
   {"NextFocusUpId", ATTRIBUTE_PARAMETER_INT},
   {"PaddingRelative", ATTRIBUTE_PARAMETER_IIII},
   {"Padding", ATTRIBUTE_PARAMETER_IIII},
   {"VerticalFadingEdgeEnabled", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"Rotation", ATTRIBUTE_PARAMETER_FLOAT},
   {"RotationX", ATTRIBUTE_PARAMETER_FLOAT},
   {"RotationY", ATTRIBUTE_PARAMETER_FLOAT},
   {"SaveEnabled", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"ScaleX", ATTRIBUTE_PARAMETER_FLOAT},
   {"ScaleY", ATTRIBUTE_PARAMETER_FLOAT},
   {"ScrollBarDefaultDelayBeforeFade", ATTRIBUTE_PARAMETER_INT},
   {"ScrollBarFadeDuration", ATTRIBUTE_PARAMETER_INT},
   {"ScrollBarSize", ATTRIBUTE_PARAMETER_INT},
   {"ScrollBarStyle", ATTRIBUTE_PARAMETER_INT},
   {"SoundEffectsEnabled", ATTRIBUTE_PARAMETER_BOOLEAN},
   {"TextAlignment", ATTRIBUTE_PARAMETER_INT},
   {"TextDirection", ATTRIBUTE_PARAMETER_INT},
   {"PivotX", ATTRIBUTE_PARAMETER_FLOAT},
   {"PivotY", ATTRIBUTE_PARAMETER_FLOAT},
   {"TranslationX", ATTRIBUTE_PARAMETER_FLOAT},
   {"TranslationY", ATTRIBUTE_PARAMETER_FLOAT},
   {"Visibility", ATTRIBUTE_PARAMETER_INT},
};

JUIView::JUIView()
    : layoutWidth_(ATTRIBUTE_SIZE_WRAP_CONTENT),
      layoutHeight_(ATTRIBUTE_SIZE_WRAP_CONTENT),
      layoutWeight_(0.f),
      marginLeft_(0),
      marginRight_(0),
      marginTop_(0),
      marginBottom_(0) 
{
  // setup attribute map (once)
  if (map_attributes_.size() == 0) 
  {
    for (int32_t i = 0; i < sizeof(attributes_) / sizeof(attributes_[0]); ++i) {
      map_attributes_[std::string(attributes_[i].attribute_name)] =
          attributes_[i].attribute_type;
    }
  }

  for (int32_t i = 0; i < LAYOUT_PARAMETER_COUNT; ++i) 
  {
    array_current_rules_[i] = LAYOUT_PARAMETER_UNKNOWN;
  }
}

JUIView::~JUIView()
{
  auto it = map_attribute_parameters.begin();
  auto itEnd = map_attribute_parameters.end();
  while (it != itEnd) {
    AttributeParameterStore &p = map_attribute_parameters[it->first];
    switch (p.type) {
      case ATTRIBUTE_PARAMETER_STRING:
        if (it->second.str != NULL) delete it->second.str;
        break;
      default:
        break;
    }
    it++;
  }
}

/*
 * Add relative layout rule to the view
 */
void JUIView::AddRule(const int32_t layoutParameterIndex,
                      const int32_t parameter) 
{
  if (layoutParameterIndex < 0 ||
      layoutParameterIndex >= LAYOUT_PARAMETER_COUNT) 
  {
    LOGE("Invalid rule index");
    return;
  }
  ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
      JUIWindow::GetHelperClassInstance(), "addRule",
      "(Landroid/view/View;II)V", GetJobject(), layoutParameterIndex,
      parameter);
  array_current_rules_[layoutParameterIndex] = parameter;
}

void JUIView::AddRule(const int32_t layoutParameterIndex,
                      const JUIView *parameter) 
{

  /*
   * perform pointer to id xlation
   */
    AddRule(layoutParameterIndex, id_factory_.getId(parameter));
}

void JUIView::SetLayoutParams(const int32_t width, const int32_t height) 
{
  ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
      JUIWindow::GetHelperClassInstance(), "setLayoutParams",
      "(Landroid/view/View;II)V", GetJobject(), width, height);
  layoutWidth_ = width;
  layoutHeight_ = height;
  layoutWeight_ = 0.f;
}

void JUIView::SetLayoutParams(const int32_t width, const int32_t height,
                              const float weight) 
{
  ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
      JUIWindow::GetHelperClassInstance(), "setLayoutParams",
      "(Landroid/view/View;IIF)V", GetJobject(), width, height, weight);
  layoutWidth_ = width;
  layoutHeight_ = height;
  layoutWeight_ = weight;
}

void JUIView::SetMargins(const int32_t left, const int32_t top,
                         const int32_t right, const int32_t bottom) 
{
  ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
      JUIWindow::GetHelperClassInstance(), "setMargins",
      "(Landroid/view/View;IIII)V", GetJobject(), left, top, right, bottom);
  marginLeft_ = left;
  marginRight_ = right;
  marginTop_ = top;
  marginBottom_ = bottom;
}

void JUIView::RestoreParameters(std::unordered_map<std::string, int32_t> &map) 
{
  // Restore Layout Rule
  for (int32_t i = 0; i < LAYOUT_PARAMETER_COUNT; ++i) {
    if (array_current_rules_[i] != LAYOUT_PARAMETER_UNKNOWN) {
      AddRule(i, array_current_rules_[i]);
    }
  }

  auto it = map_attribute_parameters.begin();
  auto itEnd = map_attribute_parameters.end();
  while (it != itEnd) {
    AttributeParameterStore &p = map_attribute_parameters[it->first];
    switch (p.type) {
      case ATTRIBUTE_PARAMETER_INT:
        JUIBase::SetAttribute(map, it->first.c_str(), (int32_t)p.i);
        break;
      case ATTRIBUTE_PARAMETER_FLOAT:
        JUIBase::SetAttribute(map, it->first.c_str(), p.f);
        break;
      case ATTRIBUTE_PARAMETER_BOOLEAN:
        JUIBase::SetAttribute(map, it->first.c_str(), p.f);
        break;
      case ATTRIBUTE_PARAMETER_STRING:
        JUIBase::SetAttribute(map, it->first.c_str(), p.str->c_str());
        break;
      case ATTRIBUTE_PARAMETER_IF:
        JUIBase::SetAttribute(map, it->first.c_str(), p.param_if.i1,
                              p.param_if.f2);
        break;
      case ATTRIBUTE_PARAMETER_FF:
        JUIBase::SetAttribute(map, it->first.c_str(), p.param_ff.f1,
                              p.param_ff.f2);
        break;
      case ATTRIBUTE_PARAMETER_IIII:
        JUIBase::SetAttribute(map, it->first.c_str(), p.param_iiii.i1,
                              p.param_iiii.i2, p.param_iiii.i3,
                              p.param_iiii.i4);
        break;
      case ATTRIBUTE_PARAMETER_FFFI:
        JUIBase::SetAttribute(map, it->first.c_str(), p.param_fffi.f1,
                              p.param_fffi.f2, p.param_fffi.f3, p.param_fffi.i);
        break;
      default:
        break;
    }
    it++;
  }

  if (layoutWidth_ != ATTRIBUTE_SIZE_WRAP_CONTENT ||
      layoutHeight_ != ATTRIBUTE_SIZE_WRAP_CONTENT || layoutWeight_ != 0.f) 
  {
    if (layoutWeight_ != 0.f)
      SetLayoutParams(layoutWidth_, layoutHeight_, layoutWeight_);
    else
      SetLayoutParams(layoutWidth_, layoutHeight_);
  }

  if (marginLeft_ || marginRight_ || marginTop_ || marginBottom_) 
  {
    SetMargins(marginLeft_, marginTop_, marginRight_, marginBottom_);
  }
}

} // ndkGui 