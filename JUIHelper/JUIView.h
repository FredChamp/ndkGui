#ifndef __NDKGUI_JUIVIEW_H__
#define __NDKGUI_JUIVIEW_H__

#include <JNIHelper.h>

#include "JUIBase.h"

namespace ndkGui {
    
/*
 * Layout parameters for AddRule() call.
 * Similar behavior to Java RelativeLayout definitions
 */
enum LayoutParameterType {
  LAYOUT_PARAMETER_UNKNOWN = -2,
  LAYOUT_PARAMETER_TRUE = -1,
  LAYOUT_PARAMETER_LEFT_OF = 0,
  LAYOUT_PARAMETER_RIGHT_OF = 1,
  LAYOUT_PARAMETER_ABOVE = 2,
  LAYOUT_PARAMETER_BELOW = 3,
  LAYOUT_PARAMETER_ALIGN_BASELINE = 4,
  LAYOUT_PARAMETER_ALIGN_LEFT = 5,
  LAYOUT_PARAMETER_ALIGN_TOP = 6,
  LAYOUT_PARAMETER_ALIGN_RIGHT = 7,
  LAYOUT_PARAMETER_ALIGN_BOTTOM = 8,
  LAYOUT_PARAMETER_ALIGN_PARENT_LEFT = 9,
  LAYOUT_PARAMETER_ALIGN_PARENT_TOP = 10,
  LAYOUT_PARAMETER_ALIGN_PARENT_RIGHT = 11,
  LAYOUT_PARAMETER_ALIGN_PARENT_BOTTOM = 12,
  LAYOUT_PARAMETER_CENTER_IN_PARENT = 13,
  LAYOUT_PARAMETER_CENTER_HORIZONTAL = 14,
  LAYOUT_PARAMETER_CENTER_VERTICAL = 15,
  LAYOUT_PARAMETER_START_OF = 16,
  LAYOUT_PARAMETER_END_OF = 17,
  LAYOUT_PARAMETER_ALIGN_START = 18,
  LAYOUT_PARAMETER_ALIGN_END = 19,
  LAYOUT_PARAMETER_ALIGN_PARENT_START = 20,
  LAYOUT_PARAMETER_ALIGN_PARENT_END = 21,
  LAYOUT_PARAMETER_COUNT = 22,
};

/*
 * Callback type for event callbacks in widgets.
 * Parameter for SetCallback() call.
 */
enum JUICallbackType {
  JUICALLBACK_SEEKBAR_STOP_TRACKING_TOUCH = 1,
  JUICALLBACK_SEEKBAR_START_TRACKING_TOUCH = 2,
  JUICALLBACK_SEEKBAR_PROGRESSCHANGED = 3,
  JUICALLBACK_COMPOUNDBUTTON_CHECKED = 4,
  JUICALLBACK_BUTTON_DOWN = 5,
  JUICALLBACK_BUTTON_UP = 6,
  JUICALLBACK_BUTTON_CANCELED = 7,

  JUICALLBACK_DIALOG_DISMISSED = 108,
  JUICALLBACK_DIALOG_CANCELLED = 109,
};

/*
 * Gravity attribute settings
 */
enum AttributeGravityType {
  ATTRIBUTE_GRAVITY_TOP = 0x30,
  ATTRIBUTE_GRAVITY_BOTTOM = 0x50,
  ATTRIBUTE_GRAVITY_LEFT = 0x03,
  ATTRIBUTE_GRAVITY_RIGHT = 0x05,
  ATTRIBUTE_GRAVITY_CENTER_VERTICAL = 0x10,
  ATTRIBUTE_GRAVITY_FILL_VERTICAL = 0x70,
  ATTRIBUTE_GRAVITY_CENTER_HORIZONTAL = 0x01,
  ATTRIBUTE_GRAVITY_FILL_HORIZONTAL = 0x07,
  ATTRIBUTE_GRAVITY_CENTER = 0x11,
  ATTRIBUTE_GRAVITY_FILL = 0x77,
  ATTRIBUTE_GRAVITY_CLIP_VERTICAL = 0x80,
  ATTRIBUTE_GRAVITY_CLIP_HORIZONTAL = 0x08,
  ATTRIBUTE_GRAVITY_START = 0x00800003,
  ATTRIBUTE_GRAVITY_END = 0x00800005,
};

/*
 * Attribute unit for SetAttribute() parameter
 */
enum AttributeUnitType {
  ATTRIBUTE_UNIT_PX = 0x0,
  ATTRIBUTE_UNIT_DIP = 0x1,
  ATTRIBUTE_UNIT_SP = 0x2,
  ATTRIBUTE_UNIT_PT = 0x3,
  ATTRIBUTE_UNIT_IN = 0x4,
  ATTRIBUTE_UNIT_MM = 0x5,
};

/*
 * Size attribute for AddRule()
 */
enum AttributeSizeType {
  ATTRIBUTE_SIZE_MATCH_PARENT = -1,
  ATTRIBUTE_SIZE_WRAP_CONTENT = -2,
};

/*
 * Linear layout orientation
 */
enum LayoutOrientationType {
  LAYOUT_ORIENTATION_HORIZONTAL = 0,
  LAYOUT_ORIENTATION_VERTICAL = 1,
};

/*
 * Enum for alert dialog button
 */
enum AlertDialogButtonType {
  ALERTDIALOG_BUTTON_NEGATIVE = -2,
  ALERTDIALOG_BUTTON_NEUTRAL = -3,
  ALERTDIALOG_BUTTON_POSITIVE = -1,
};

/*
 * ProgressBar style
 */
enum ProgressBarStyleType {
  PROGRESS_BAR_STYLE_DEFAULT = 0x01010077,
  PROGRESS_BAR_STYLE_HIROZONTAL = 0x01010078,
  PROGRESS_BAR_STYLE_SMALL = 0x01010079,
  PROGRESS_BAR_STYLE_LARGE = 0x101007A,
  PROGRESS_BAR_STYLE_INVERSE = 0x01010287,
  PROGRESS_BAR_STYLE_SMALL_INVERSE = 0x01010288,
  PROGRESS_BAR_STYLE_LARGE_INVARSE = 0x01010289,
  PROGRESS_BAR_STYLE_SMALL_TITLE = 0x0101020f,
};

enum ViewVisibility {
  VIEW_VISIVILITY_VISIBLE = 0,
  VIEW_VISIVILITY_INVISIBLE = 4,
  VIEW_VISIVILITY_GONE = 8,
};

struct AttributeType {
  const char *attribute_name;
  const int32_t attribute_type;
};

/*
 * JUIView class
 */
class JUIView : public JUIBase {
  friend class JUIWindow;
  friend class JUIDialog;

 public:
  JUIView();
  virtual ~JUIView();

  /*
   * Add layout rule to the widget
   */
  void AddRule(const int32_t layoutParameterIndex, const int32_t parameter);
  void AddRule(const int32_t layoutParameterIndex, const JUIView *parameter);
  /*
   * Set LayoutParams for RelativeLayout
   */
  void SetLayoutParams(const int32_t width, const int32_t height);
  /*
   * Set LayoutParams for LinearLayout
   */
  void SetLayoutParams(const int32_t width, const int32_t height,
                       const float f);

  /*
   * Set Margins
   */
  void SetMargins(const int32_t left, const int32_t top, const int32_t right,
                  const int32_t bottom);

  /*
   * Set attribute of the widget
   * See attributes_ for available attribute names
   */
  template <typename T>
  bool SetAttribute(const char *strAttribute, const T t) {
    return SetAttribute(map_attributes_, strAttribute, t);
  }

  bool SetAttribute(const char *strAttribute, const char *str) {
    return JUIBase::SetAttribute(map_attributes_, strAttribute, str);
  }

  template <typename T, typename T2>
  bool SetAttribute(const char *strAttribute, T t, T2 t2) {
    return JUIBase::SetAttribute(map_attributes_, strAttribute, t, t2);
  }

  template <typename T, typename T2, typename T3, typename T4>
  bool SetAttribute(const char *strAttribute, T p1, T2 p2, T3 p3, T4 p4) {
    return JUIBase::SetAttribute(map_attributes_, strAttribute, p1, p2, p3, p4);
  }

  template <typename T>
  bool GetAttributeA(const char *strAttribute, T *value) {
    return JUIBase::GetAttribute(map_attributes_, strAttribute, value);
  }

 private:
  const static AttributeType attributes_[];
  int32_t array_current_rules_[LAYOUT_PARAMETER_COUNT];

  int32_t layoutWidth_;
  int32_t layoutHeight_;
  float layoutWeight_;

  int32_t marginLeft_;
  int32_t marginRight_;
  int32_t marginTop_;
  int32_t marginBottom_;

 protected:
  static std::unordered_map<std::string, int32_t> map_attributes_;

  void RestoreParameters(std::unordered_map<std::string, int32_t> &map);
  virtual void Restore() = 0;
};
} // ndkGui
#endif  // __NDKGUI_JUIVIEW_H__

