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

#define LOG_TAG "Kernel_JNI"
#include "openvx_jni.h"

namespace android
{
    //**************************************************************************
    // LOCAL VARIABLES
    //**************************************************************************

    //**************************************************************************
    // EXPORTED FUNCTIONS
    //**************************************************************************
    static void GetByName(JNIEnv *env, jobject obj, jlong c, jstring name)
    {
        const char *str = env->GetStringUTFChars(name, NULL);
        vx_context context = (vx_context)c;
        vx_kernel k = vxGetKernelByName(context, (vx_char *)str);
        env->ReleaseStringUTFChars(name, str);
        SetHandle(env, obj, KernelClass, parentName, c);
        SetHandle(env, obj, KernelClass, handleName, (jlong)k);
    }

    static void GetByEnum(JNIEnv *env, jobject obj, jlong c, jint kenum)
    {
        vx_context context = (vx_context)c;
        vx_kernel k = vxGetKernelByEnum(context, kenum);
        SetHandle(env, obj, KernelClass, parentName, c);
        SetHandle(env, obj, KernelClass, handleName, (jlong)k);
    }

    static void Release(JNIEnv *env, jobject obj)
    {
        vx_kernel k = (vx_kernel)GetHandle(env, obj, KernelClass, handleName);
        vxReleaseKernel(&k);
        SetHandle(env, obj, KernelClass, handleName, 0);
    }

    static jint getNumParameters(JNIEnv *env, jobject obj)
    {
        vx_kernel k = (vx_kernel)GetHandle(env, obj, KernelClass, handleName);
        jint value = 0;
        vx_status status = vxQueryKernel(k, VX_KERNEL_PARAMETERS, &value, sizeof(value));
        if (status != VX_SUCCESS)
            value = 0;
        return value;
    }

    static jstring GetName(JNIEnv *env, jobject obj)
    {
        vx_kernel k = (vx_kernel)GetHandle(env, obj, KernelClass, handleName);
        vx_char name[VX_MAX_KERNEL_NAME];
        vx_status status = vxQueryKernel(k, VX_KERNEL_NAME, name, sizeof(name));
        if (status == VX_SUCCESS)
            return env->NewStringUTF(name);
        else
            return env->NewStringUTF("");
    }

    static JNINativeMethod method_table[] = {
        // { name,                          signature,                 function_pointer }
        { "get",                            "(JLjava/lang/String;)V",  (void *)GetByName },
        { "get",                            "(JI)V",                   (void *)GetByEnum },
        { "release",                        "()V",                     (void *)Release },
        { "getNumParameters",               "()I",                     (void *)getNumParameters },
        { "name",                           "()Ljava/lang/String;",    (void *)GetName },
    };

    int register_org_khronos_OpenVX_Kernel(JNIEnv *env)
    {
        PrintJNITable(LOG_TAG, KernelClass, method_table, NELEM(method_table));
        return jniRegisterNativeMethods(env, KernelClass, method_table, NELEM(method_table));
    }
};



