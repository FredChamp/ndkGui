#ifndef __NDKGUI_JUITEXTVIEW_H__
#define __NDKGUI_JUITEXTVIEW_H__

#include <map>
#include <unordered_map>
#include <string>
#include "JUIView.h"

//-------------------------------------------------
// JUITextView
//-------------------------------------------------
namespace ndkGui 
{
class JUITextView : public JUIView {
 public:
  JUITextView();
  explicit JUITextView(const char *str);
  virtual ~JUITextView();

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

  template <typename T, typename T2>
  bool SetAttribute(const char *strAttribute, T t, T2 t2) {
    return JUIBase::SetAttribute(map_attributes_, strAttribute, t, t2);
  }

  template <typename T, typename T2, typename T3, typename T4>
  bool SetAttribute(const char *strAttribute, T p1, T2 p2, T3 p3, T4 p4) {
    return JUIBase::SetAttribute(map_attributes_, strAttribute, p1, p2, p3, p4);
  }

  /*
   * Retrieve attribute of the widget
   */
  template <typename T>
  bool GetAttributeA(const char *strAttribute, T *value) {
    return JUIView::GetAttribute(map_attributes_, strAttribute, value);
  }

 private:
  const static AttributeType attributes_[];
  void Init();

 protected:
  static std::unordered_map<std::string, int32_t> map_attributes_;
  virtual void Restore();

  explicit JUITextView(const bool b);
};
}//ndkGui

#endif // __NDKGUI_JUITEXTVIEW_H__