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

#define LOG_TAG "Parameter_JNI"
#include "openvx_jni.h"

namespace android
{
    //**************************************************************************
    // LOCAL VARIABLES
    //**************************************************************************

    //**************************************************************************
    // EXPORTED FUNCTIONS
    //**************************************************************************
    static void GetByIndex(JNIEnv *env, jobject obj, jlong n, jint i)
    {
        vx_node node = (vx_node)n;
        vx_parameter p = vxGetParameterByIndex(node, i);
        SetHandle(env, obj, ParameterClass, parentName, n);
        SetHandle(env, obj, ParameterClass, handleName, (jlong)p);
    }

    static void Release(JNIEnv *env, jobject obj)
    {
        vx_parameter p = (vx_parameter)GetHandle(env, obj, ParameterClass, handleName);
        vxReleaseParameter(&p);
        SetHandle(env, obj, ParameterClass, handleName, 0);
    }

    static JNINativeMethod method_table[] = {
        // { name,                         signature,                 function_pointer }
        { "get",                           "(JI)V",                   (void *)GetByIndex },
        { "release",                       "()V",                     (void *)Release },
    };

    int register_org_khronos_OpenVX_Parameter(JNIEnv *env)
    {
        PrintJNITable(LOG_TAG, ParameterClass, method_table, NELEM(method_table));
        return jniRegisterNativeMethods(env, ParameterClass, method_table, NELEM(method_table));
    }
};



