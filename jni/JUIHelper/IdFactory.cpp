#include "IdFactory.h"

namespace ndkGui
{
/*
 * IdFactory Implementation: our ID is just a simple integer starting from 1,and
 *                           keeps on counting up. There is no re-use -- even
 *                           one ID is removed from cache, we still counting up
 *                           It will take a long while to overflow a 32 bit integer
 *                           for UI ids. Even it does, it wrap back, at that time,
 *                           previous low values will long gone.
 */
int32_t IdFactory::cur_id_ = 0;
int32_t IdFactory::getId(const JUIBase* ui_object) {
    auto it = ids_.find(ui_object);
    if (it == ids_.end()) {
        LOGE("IDs not inside hash for %p, patching done (%d)", ui_object, cur_id_);
        ids_[ui_object] = ++cur_id_;
        return cur_id_;
    }
    return it->second;
}

JUIBase* IdFactory::getUIBase(int32_t ui_id) {
    for (auto id: ids_) {
        if(id.second == ui_id) {
            return const_cast<JUIBase*>(id.first);
        }
    }
    LOGE("Unable to find object point for ID(%d, %x)", ui_id, ui_id);
    return nullptr;
}

bool IdFactory::insert(const JUIBase* ui_object) {
    bool status = true;
    auto it = ids_.find(ui_object);
    if (it != ids_.end()) {
        LOGE("Error: %p is already in = %d", it->first, it->second);
        LOGE("Overwriting %p with %p for it", it->first, ui_object);
        status = false;
        //return status;  ---> let it fall through
    }
    ids_[ui_object] = ++cur_id_;
    return status;
}

bool  IdFactory::remove(const JUIBase* ui_object) {
    auto it = ids_.find(ui_object);
    if (it == ids_.end()) {
        LOGE("IDs not inside hash for %p!!!", ui_object);
        return false;
    }
    ids_.erase(it);
    return true;
}

void IdFactory::debugDumpCurrentHashTable(void) {
    for (auto id: ids_) {
        LOGI("Cached ID (%p = %d)", id.first, id.second);
    }
}
} // ndkGui