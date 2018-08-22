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

#define LOG_TAG "Target_JNI"
#include "openvx_jni.h"

namespace android
{
    //**************************************************************************
    // LOCAL VARIABLES
    //**************************************************************************

    //**************************************************************************
    // EXPORTED FUNCTIONS
    //**************************************************************************
    static void GetByIndex(JNIEnv *env, jobject obj, jlong c, jint i)
    {
        vx_context context = (vx_context)c;
        vx_target t = vxGetTargetByIndex(context, i);
        SetHandle(env, obj, TargetClass, parentName, c);
        SetHandle(env, obj, TargetClass, handleName, (jlong)t);
    }

    static void Release(JNIEnv *env, jobject obj)
    {
        vx_target t = (vx_target)GetHandle(env, obj, TargetClass, handleName);
        vxReleaseTarget(&t);
        SetHandle(env, obj, TargetClass, handleName, 0);
    }

    static jint GetIndex(JNIEnv *env, jobject obj)
    {
        vx_target t = (vx_target)GetHandle(env, obj, TargetClass, handleName);
        jint index;
        vxQueryTarget(t, VX_TARGET_ATTRIBUTE_INDEX, &index, sizeof(index));
        return index;
    }

    static jstring GetName(JNIEnv *env, jobject obj)
    {
        jstring name = 0;
        vx_char targetname[VX_MAX_TARGET_NAME];
        memset(targetname, 0, sizeof(targetname));
        vx_target t = (vx_target)GetHandle(env, obj, TargetClass, handleName);
        if (t)
        {
            vx_status status = vxQueryTarget(t, VX_TARGET_ATTRIBUTE_NAME, targetname, sizeof(targetname));
            if (status != VX_SUCCESS)
                ALOGD("Failed to query target name! status=%d\n",status);
        }
        else
            ALOGD("Failed to retrieve correct target reference!\n");
        return env->NewStringUTF(targetname);
    }

    static jint GetNumKernels(JNIEnv *env, jobject obj)
    {
        vx_target t = (vx_target)GetHandle(env, obj, TargetClass, handleName);
        jint num = 0;
        vx_status status = vxQueryTarget(t, VX_TARGET_ATTRIBUTE_NUMKERNELS, &num, sizeof(num));
        if (status != VX_SUCCESS)
            num = 0;
        return num;
    }

    static jobject GetTable(JNIEnv *env, jobject obj)
    {
        vx_uint32 t,num;
        vx_target target = (vx_target)GetHandle(env, obj, TargetClass, handleName);
        vxQueryTarget(target, VX_TARGET_ATTRIBUTE_NUMKERNELS, &num, sizeof(num));
        vx_kernel_info_t *table = (vx_kernel_info_t *)calloc(num, sizeof(vx_kernel_info_t));
        jobjectArray tarray = 0;
        if (table)
        {
            jclass tclass = env->FindClass("org/khronos/openvx/Target$TargetKernel");
            tarray = env->NewObjectArray(num, tclass, 0);
            jmethodID tcon = env->GetMethodID(tclass, "<init>", "("OBJECT(Target)")V");
            jfieldID tfenum = env->GetFieldID(tclass, "enumeration", "I");
            jfieldID tfname = env->GetFieldID(tclass, "name", "Ljava/lang/String;");
            vxQueryTarget(target, VX_TARGET_ATTRIBUTE_KERNELTABLE, table, num*sizeof(vx_kernel_info_t));
            for (t = 0; t < num; t++)
            {
                jobject tobj = env->NewObject(tclass, tcon);
                env->SetIntField(tobj, tfenum, table[t].enumeration);
                jstring tstr = env->NewStringUTF(table[t].name);
                env->SetObjectField(tobj, tfname, tstr);
                env->SetObjectArrayElement(tarray, t, tobj);
            }
        }
        return tarray;
    }

    static JNINativeMethod method_table[] = {
        // { name,                         signature,                 function_pointer }
        { "get",                           "(JI)V",                   (void *)GetByIndex },
        { "release",                       "()V",                     (void *)Release },
        { "getIndex",                      "()I",                     (void *)GetIndex },
        { "getName",                       "()Ljava/lang/String;",    (void *)GetName },
        { "getNumKernels",                 "()I",                     (void *)GetNumKernels },
        { "getTable",                      "()["OBJECT(Target$TargetKernel),  (void *)GetTable },
    };

    int register_org_khronos_OpenVX_Target(JNIEnv *env)
    {
        PrintJNITable(LOG_TAG, ParameterClass, method_table, NELEM(method_table));
        return jniRegisterNativeMethods(env, TargetClass, method_table, NELEM(method_table));
    }
};



