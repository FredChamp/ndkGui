#ifndef __NDKGUI_IDFACTORY_H__
#define __NDKGUI_IDFACTORY_H__

#include <JNIHelper.h>

namespace ndkGui {

/*
 * class IdFactory: cache UI pointers and generate an ID, send ID to Java side
 *                  when get id back from Java, retrieve the UI pointer for that
 *                  ID, and continue. Mainly purpose is for things to be called
 *                  back on UI thread
 */
class JUIBase;
class IdFactory {
   public:
      int32_t   getId(const JUIBase* ui_object);
      JUIBase*  getUIBase(int32_t ui_id);
      void      debugDumpCurrentHashTable(void);
      bool      insert(const JUIBase* ui_object);
      bool      remove(const JUIBase* ui_object);

   private:
      std::unordered_map<const JUIBase*, int32_t> ids_;
      static int32_t cur_id_;
};
} // ndkGui

#endif //__NDKGUI_IDFACTORY_H__