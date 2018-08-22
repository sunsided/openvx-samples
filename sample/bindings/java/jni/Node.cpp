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

#define LOG_TAG "Node_JNI"
#include "openvx_jni.h"

namespace android
{
    //**************************************************************************
    // LOCAL VARIABLES
    //**************************************************************************

    //**************************************************************************
    // EXPORTED FUNCTIONS
    //**************************************************************************
    static void Initialize(JNIEnv *env, jobject obj, jlong g, jlong k)
    {
        vx_graph graph = (vx_graph)g;
        vx_kernel kernel = (vx_kernel)k;
        vx_node n = vxCreateGenericNode(graph, kernel);
        SetHandle(env, obj, NodeClass, parentName, g);
        SetHandle(env, obj, NodeClass, handleName, (jlong)n);
    }

    static void Finalize(JNIEnv *env, jobject obj)
    {
        vx_node n = (vx_node)GetHandle(env, obj, NodeClass, handleName);
        vxReleaseNode(&n);
        SetHandle(env, obj, NodeClass, handleName, 0);
    }

    static jobject getParameter(JNIEnv *env, jobject obj, jint i)
    {
        vx_node n = (vx_node)GetHandle(env, obj, NodeClass, handleName);
        jclass c = env->FindClass(ParameterClass);
        jmethodID id = env->GetMethodID(c, "<init>", "(JI)"OBJECT(Parameter));
        jobject p = env->NewObject(c, id, (jlong)n, i);
        return p;
    }

    static jint setParameter(JNIEnv *env, jobject obj, jint index, jlong ref)
    {
        vx_node n = (vx_node)GetHandle(env, obj, NodeClass, handleName);
        return vxSetParameterByIndex(n, index, (vx_reference)ref);
    }

    static JNINativeMethod method_table[] = {
        // { name,                         signature,                 function_pointer }
        { "create",                        "(JJ)V",                   (void *)Initialize },
        { "destroy",                       "()V",                     (void *)Finalize },
        { "getParameter",                  "(I)"OBJECT(Parameter),    (void *)getParameter },
        { "_setParameter",                 "(IJ)I",                   (void *)setParameter },
    };

    int register_org_khronos_OpenVX_Node(JNIEnv *env)
    {
        PrintJNITable(LOG_TAG, NodeClass, method_table, NELEM(method_table));
        return jniRegisterNativeMethods(env, NodeClass, method_table, NELEM(method_table));
    }
};



