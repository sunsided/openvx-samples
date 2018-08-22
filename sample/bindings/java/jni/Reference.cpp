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

#define LOG_TAG "Reference_JNI"
#include "openvx_jni.h"

namespace android
{
    //**************************************************************************
    // LOCAL VARIABLES
    //**************************************************************************

    //**************************************************************************
    // EXPORTED FUNCTIONS
    //**************************************************************************

    static jint getType(JNIEnv *env, jobject obj)
    {
        vx_reference r = (vx_reference)GetHandle(env, obj, ReferenceClass, handleName);
        vx_enum e;
        vxQueryReference(r, VX_REF_ATTRIBUTE_TYPE, &e, sizeof(e));
        return (jint)e;
    }

    static jint getCount(JNIEnv *env, jobject obj)
    {
        vx_reference r = (vx_reference)GetHandle(env, obj, ReferenceClass, handleName);
        vx_uint32 c;
        vxQueryReference(r, VX_REF_ATTRIBUTE_COUNT, &c, sizeof(c));
        return (jint)c;
    }

    static JNINativeMethod method_table[] = {
        // { name,                         signature,                 function_pointer }
        { "getType",                       "()I",                   (void *)getType },
        { "getCount",                      "()I",                   (void *)getCount },
    };

    int register_org_khronos_OpenVX_Reference(JNIEnv *env)
    {
        PrintJNITable(LOG_TAG, ReferenceClass, method_table, NELEM(method_table));
        return jniRegisterNativeMethods(env, ReferenceClass, method_table, NELEM(method_table));
    }
};



