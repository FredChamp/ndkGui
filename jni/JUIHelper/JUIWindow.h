#ifndef __NDKGUI_JUIWINDOW_H__
#define __NDKGUI_JUIWINDOW_H__

/*
 * JUIWindow represents a popup window with a relative layout put on the window
 * An application can create JUIView based classes and add them to JUIWindow to
 * show Java Widget over
 * native activity.
 */
#include <jni.h>
#include <JNIHelper.h>
// #include "JUIView.h"
#include "JUIDialog.h"

namespace ndkGui
{
 
//
class JUIView;
class JUIDialog;
class JUIWindow {
  /*
   * These classes need to be a friend class to access protected methods
   */
  friend class JUIView;
  friend class JUITextView;
  friend class JUIButton;
  friend class JUIDialog;

 public:
  /*
   * Retrieve the singleton object of the helper.
   * Static member of the class

   * Methods in the class are NOT designed as thread safe.
   */
  static JUIWindow *GetInstance();

  /*
   * Retrieve an instance of JUIHelper Java class
   *
   */
  static jobject GetHelperClassInstance();

  /*
   * Retrieve JUIHelper Java class
   *
   */
  static jclass GetHelperClass();

  /*
   * Initialize window with an activity
   */
  static void Init(ANativeActivity *activity,
                   const char *helper_class_name = NULL);

  /*
   * Close the window
   */
  void Close();

  /*
   * Resume JUIWindow
   * This function needs to be invoked corresponding activity life cycle event
   */
  void Resume(ANativeActivity *activity, const int32_t command);

  /*
   * Suspend JUIWindow
   * This function needs to be invoked corresponding activity life cycle event
   */
  void Suspend(const int32_t command);

  /*
   * Add JUIView classes to the window
   */
  void AddView(JUIView *view);

  /*
   * Get context associated with the window class
   */
  jobject GetContext() {
    if (activity_ == NULL) return NULL;
    return activity_->clazz;
  }

  /*
   * Get mutex for JUI helpers
   */
  std::mutex &GetMutex() { return mutex_; }

 private:
  JUIWindow();
  ~JUIWindow();
  JUIWindow(const JUIWindow &rhs);
  JUIWindow &operator=(const JUIWindow &rhs);

  ANativeActivity *activity_;
  jobject popupWindow_;

  std::vector<JUIView *> views_;

  bool suspended_;
  bool windowDestroyed_;

  jobject jni_helper_java_ref_;
  jclass jni_helper_java_class_;

  JUIDialog *dialog_;

  // mutex for synchronization
  mutable std::mutex mutex_;

  jobject CreateWidget(const char *strWidgetName, void *id);
  jobject CreateWidget(const char *strWidgetName, void *id,
                       const int32_t param);
  void CloseWidget(jobject obj);

  void SetDialog(JUIDialog *dialog) { dialog_ = dialog; }
};
} // ndkGui

#endif // __NDKGUI_JUIWINDOW_H__