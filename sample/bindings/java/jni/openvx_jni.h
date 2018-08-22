/* 

 * Copyright (c) 2012-2017 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <VX/vx.h>
#include <JNIHelp.h>
#include <jni.h>
#include <utils/Log.h>
#include <utils/misc.h>
#include <cutils/properties.h>
#include <android_runtime/AndroidRuntime.h>

#define VXPATH     "org/khronos/openvx/"
#define OBJECT(c)  "L"VXPATH #c";"

extern const char *ContextClass;
extern const char *ScalarClass;
extern const char *BufferClass;
extern const char *ImageClass;
extern const char *KernelClass;
extern const char *GraphClass;
extern const char *NodeClass;
extern const char *ParameterClass;
extern const char *ReferenceClass;
extern const char *TargetClass;
extern const char *handleName;
extern const char *parentName;

/*! \brief A helper function across all the JNI objects */
jlong GetHandle(JNIEnv *env, jobject obj, const char *className, const char *fieldName);

/*! \brief A helper function across all the JNI objects */
void SetHandle(JNIEnv *env, jobject obj, const char *className, const char *fieldName, jlong value);

/*! \brief Debugging method to show published JNI method table. */
void PrintJNITable(const char *tag, const char *className, JNINativeMethod *table, uint32_t numElem);

namespace android {
    int register_org_khronos_OpenVX_Context(JNIEnv *env);
    int register_org_khronos_OpenVX_Scalar(JNIEnv *env);
    int register_org_khronos_OpenVX_Buffer(JNIEnv *env);
    int register_org_khronos_OpenVX_Image(JNIEnv *env);
    int register_org_khronos_OpenVX_Kernel(JNIEnv *env);
    int register_org_khronos_OpenVX_Graph(JNIEnv *env);
    int register_org_khronos_OpenVX_Node(JNIEnv *env);
    int register_org_khronos_OpenVX_Parameter(JNIEnv *env);
    int register_org_khronos_OpenVX_Reference(JNIEnv *env);
    int register_org_khronos_OpenVX_Target(JNIEnv *env);
};
