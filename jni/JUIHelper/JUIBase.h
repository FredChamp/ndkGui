#ifndef __NDKGUI_JUIBASE_H__
#define __NDKGUI_JUIBASE_H__

#include <map>
#include <unordered_map>
#include <string>

#include <JNIHelper.h>
#include "IdFactory.h"

namespace ndkGui 
{
    
/*
* Internal enums for attribute parameter type
*/
enum AttributeParapeterType {
 ATTRIBUTE_PARAMETER_INT,
 ATTRIBUTE_PARAMETER_FLOAT,
 ATTRIBUTE_PARAMETER_BOOLEAN,
 ATTRIBUTE_PARAMETER_STRING,
 ATTRIBUTE_PARAMETER_IF,  // parameters of int32_t, float
 ATTRIBUTE_PARAMETER_FF,  // parameters of 2 floats
 ATTRIBUTE_PARAMETER_III,  // parameters of int32_t, int32_t, int32_t
 ATTRIBUTE_PARAMETER_IIII,  // parameters of int32_t, int32_t, int32_t, int32_t
 ATTRIBUTE_PARAMETER_FFFI,  // parameters of float, float, float, int32_t
};
/*
* Internal structure to store attribute parameters
*/
struct AttributeParameterStore {
 AttributeParapeterType type;
 union {
   int32_t i;
   float f;
   bool b;
   std::string *str;
   struct {
     int32_t i1;
     float f2;
   } param_if;
   struct {
     float f1;
     float f2;
   } param_ff;
   struct {
     int32_t i1;
     int32_t i2;
     int32_t i3;
   } param_iii;
   struct {
     float f1;
     float f2;
     float f3;
     int32_t i;
   } param_fffi;
   struct {
     int32_t i1;
     int32_t i2;
     int32_t i3;
     int32_t i4;
   } param_iiii;
 };
};

/*
* Base class of JUIView
*/
class JUIBase {
public:
 JUIBase() : obj_(NULL) {  id_factory_.insert(this); }
 virtual ~JUIBase(){  id_factory_.remove(this); }

 /*
  * Dispatch Widget events. This one is called from Java code through
  * Java_com_sample_helper_JUIHelper_JUICallbackHandler()
  */
 virtual void DispatchEvent(const int32_t message, const int32_t param1,
                            const int32_t param2) {}

 /*
  * Template for 1 parameter version of SetAttribute
  */
 template <typename T>
 bool SetAttribute(std::unordered_map<std::string, int32_t> &map,
                   const char *strAttribute, const T t) {
   LOGI("Attribute '%s' updating", strAttribute);
   auto it = map.find(strAttribute);
   if (it != map.end()) {
     std::string s = std::string("set");
     s += it->first;

     AttributeParameterStore &p = map_attribute_parameters[it->first];
     switch (it->second) {
       case ATTRIBUTE_PARAMETER_INT:
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(I)V", t);
         p.type = ATTRIBUTE_PARAMETER_INT;
         p.i = t;
         break;
       case ATTRIBUTE_PARAMETER_FLOAT:
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(F)V", t);
         p.type = ATTRIBUTE_PARAMETER_FLOAT;
         p.f = t;
         break;
       case ATTRIBUTE_PARAMETER_BOOLEAN:
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(Z)V", t);
         p.type = ATTRIBUTE_PARAMETER_BOOLEAN;
         p.b = t;
         break;
       default:
         LOGI("Attribute parameter does not match : %s", strAttribute);
         break;
         }
   } else {
     LOGI("Attribute '%s' not found", strAttribute);
     return false;
   }
   return true;
 }

 /*
  * Specialized Template for string version of SetAttribute
  */
 bool SetAttribute(std::unordered_map<std::string, int32_t> &map,
                   const char *strAttribute, const char *str) {
   auto it = map.find(strAttribute);
   if (it != map.end()) {
     std::string s = std::string("set");
     s += it->first;

     AttributeParameterStore &p = map_attribute_parameters[it->first];
     switch (it->second) {
       case ATTRIBUTE_PARAMETER_STRING: {
         JNIEnv *env =
             ndkGui::JNIHelper::GetInstance()->AttachCurrentThread();
         jstring string = env->NewStringUTF(str);
         jstring stringGlobal = (jstring)env->NewGlobalRef(string);
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(Ljava/lang/CharSequence;)V", stringGlobal);
         // env->DeleteGlobalRef(stringGlobal);
         // env->DeleteLocalRef(string);
             ndkGui::JNIHelper::GetInstance()->DetachCurrentThread();

         p.type = ATTRIBUTE_PARAMETER_STRING;
         if (p.str != NULL) {
           if (p.str->compare(str) != 0) {
             delete p.str;
             p.str = new std::string(str);
           }
         } else {
           p.str = new std::string(str);
         }
       } break;
       default:
         LOGI("Attribute parameter does not match : %s", strAttribute);
         break;
     }
   } else {
     LOGI("Attribute '%s' not found", strAttribute);
     return false;
   }
   return true;
 }

 /*
  * Template for 2 parameters version of SetAttribute
  */
 template <typename T, typename T2>
 bool SetAttribute(std::unordered_map<std::string, int32_t> &map,
                   const char *strAttribute, T t, T2 t2) {
   auto it = map.find(strAttribute);
   if (it != map.end()) {
     std::string s = std::string("set");
     s += it->first;

     AttributeParameterStore &p = map_attribute_parameters[it->first];
     switch (it->second) {
       case ATTRIBUTE_PARAMETER_IF:
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(IF)V", static_cast<int32_t>(t),
             static_cast<float>(t2));
         p.type = ATTRIBUTE_PARAMETER_IF;
         p.param_if.i1 = static_cast<int32_t>(t);
         p.param_if.f2 = static_cast<float>(t2);
         break;
       case ATTRIBUTE_PARAMETER_FF:
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(FF)V", static_cast<float>(t),
             static_cast<float>(t2));
         p.type = ATTRIBUTE_PARAMETER_FF;
         p.param_ff.f1 = static_cast<float>(t);
         p.param_ff.f2 = static_cast<float>(t2);
         break;
       default:
         LOGI("Attribute parameter does not match : %s", strAttribute);
         break;
     }
   } else {
     LOGI("Attribute '%s' not found", strAttribute);
     return false;
   }
   return true;
 }

 /*
  * Template for 4 parameters version of SetAttribute
  */
 template <typename T, typename T2, typename T3, typename T4>
 bool SetAttribute(std::unordered_map<std::string, int32_t> &map,
                   const char *strAttribute, T p1, T2 p2, T3 p3, T4 p4) {
   auto it = map.find(strAttribute);
   if (it != map.end()) {
     std::string s = std::string("set");
     s += it->first;

     AttributeParameterStore &p = map_attribute_parameters[it->first];
     switch (it->second) {
       case ATTRIBUTE_PARAMETER_IIII:
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(IIII)V", static_cast<int32_t>(p1),
             static_cast<int32_t>(p2), static_cast<int32_t>(p3),
             static_cast<int32_t>(p4));
         p.type = ATTRIBUTE_PARAMETER_IIII;
         p.param_iiii.i1 = static_cast<int32_t>(p1);
         p.param_iiii.i2 = static_cast<int32_t>(p2);
         p.param_iiii.i3 = static_cast<int32_t>(p3);
         p.param_iiii.i4 = static_cast<int32_t>(p4);
         break;
       case ATTRIBUTE_PARAMETER_FFFI:
         ndkGui::JNIHelper::GetInstance()->CallVoidMethod(
             obj_, s.c_str(), "(FFFI)V", static_cast<float>(p1),
             static_cast<float>(p2), static_cast<float>(p3),
             static_cast<int32_t>(p4));
         p.type = ATTRIBUTE_PARAMETER_FFFI;
         p.param_fffi.f1 = static_cast<float>(p1);
         p.param_fffi.f2 = static_cast<float>(p2);
         p.param_fffi.f3 = static_cast<float>(p3);
         p.param_fffi.i = static_cast<int32_t>(p4);
         break;
       default:
         LOGI("Attribute parameter does not match : %s", strAttribute);
         break;
     }
   } else {
     LOGI("Attribute '%s' not found", strAttribute);
     return false;
   }
   return true;
 }

 /*
  * Retrieve attribute
  */
 template <typename T>
 bool GetAttribute(std::unordered_map<std::string, int32_t> &map,
                   const char *strAttribute, T *p_value) {
   T ret;
   auto it = map.find(strAttribute);
   if (it != map.end()) {
     std::string s = std::string("get");
     s += it->first;

     switch (it->second) {
       case ATTRIBUTE_PARAMETER_INT:
         ret = (T)ndkGui::JNIHelper::GetInstance()->CallIntMethod(
             obj_, s.c_str(), "()I");
         break;
       case ATTRIBUTE_PARAMETER_FLOAT:
         ret = (T)ndkGui::JNIHelper::GetInstance()->CallFloatMethod(
             obj_, s.c_str(), "()F");
         break;
       case ATTRIBUTE_PARAMETER_BOOLEAN:
         ret = (T)ndkGui::JNIHelper::GetInstance()->CallBooleanMethod(
             obj_, s.c_str(), "()Z");
         break;
       default:
         ret = 0;
         break;
     }
   } else {
     LOGI("Attribute '%s' not found", strAttribute);
     return false;
   }
   *p_value = ret;
   return true;
 }

 static IdFactory id_factory_;

protected:
 std::unordered_map<std::string, AttributeParameterStore>
     map_attribute_parameters;
 jobject obj_;
 jobject GetJobject() { return obj_; }
 ndkGui::JNIHelper* m_ndkGui;
};
}
#endif //__NDKGUI_JUIBASE_H__