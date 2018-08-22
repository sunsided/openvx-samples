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

#include "openvx_jni.h"

using namespace android;

//**************************************************************************
// GLOBAL FUNCTIONS
//**************************************************************************

const char *ContextClass = VXPATH"Context";
const char *ScalarClass = VXPATH"Scalar";
const char *BufferClass = VXPATH"Buffer";
const char *ImageClass = VXPATH"Image";
const char *KernelClass = VXPATH"Kernel";
const char *GraphClass = VXPATH"Graph";
const char *NodeClass = VXPATH"Node";
const char *ParameterClass = VXPATH"Parameter";
const char *ReferenceClass = VXPATH"Reference";
const char *TargetClass = VXPATH"Target";
const char *handleName = "handle";
const char *parentName = "parent";

//**************************************************************************
// GLOBAL FUNCTIONS
//**************************************************************************
jlong GetHandle(JNIEnv *env, jobject obj, const char *className, const char *varname) {
    jclass c = env->FindClass(className);
    jfieldID id = env->GetFieldID(c, varname, "J");
    return env->GetLongField(obj, id);
}

void SetHandle(JNIEnv *env, jobject obj, const char *className, const char *varname, jlong value) {
    jclass c = env->FindClass(className);
    jfieldID id = env->GetFieldID(c, varname, "J");
    env->SetLongField(obj, id, value);
}

void PrintJNITable(const char *tag, const char *className, JNINativeMethod *table, uint32_t numElem)
{
    for (uint32_t i = 0; i < numElem; i++)
    {
        __android_log_print(ANDROID_LOG_DEBUG, tag, "%s.%s:%s=ptr=%p\n",
            className,
            table[i].name,
            table[i].signature,
            table[i].fnPtr);
    }
}

//**************************************************************************
// ENTRY POINT
//**************************************************************************
extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved __attribute__((unused)))
{
    JNIEnv* env = NULL;
    jint result = -1;
    int ret = 0;
    // the 2nd void cast is to bypass gcc warning message.  Alternately,
    // the '-fno-strict-aliasing' flag can also be used at the expense of
    // preventing some optimizations.
    if (vm->GetEnv((void**) (void*) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    ret |= register_org_khronos_OpenVX_Reference(env);
    ret |= register_org_khronos_OpenVX_Context(env);
    ret |= register_org_khronos_OpenVX_Scalar(env);
    ret |= register_org_khronos_OpenVX_Buffer(env);
    ret |= register_org_khronos_OpenVX_Image(env);
    ret |= register_org_khronos_OpenVX_Kernel(env);
    ret |= register_org_khronos_OpenVX_Graph(env);
    ret |= register_org_khronos_OpenVX_Node(env);
    ret |= register_org_khronos_OpenVX_Parameter(env);
    ret |= register_org_khronos_OpenVX_Target(env);
    return JNI_VERSION_1_6;
}
