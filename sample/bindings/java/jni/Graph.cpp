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

#define LOG_TAG "Graph_JNI"
#include "openvx_jni.h"

namespace android
{
    //**************************************************************************
    // LOCAL VARIABLES
    //**************************************************************************

    //**************************************************************************
    // EXPORTED FUNCTIONS
    //**************************************************************************
    static void Initialize(JNIEnv *env, jobject obj, jlong c)
    {
        vx_context context = (vx_context)c;
        vx_graph g = vxCreateGraph(context);
        SetHandle(env, obj, GraphClass, parentName, c);
        SetHandle(env, obj, GraphClass, handleName, (jlong)g);
    }

    static void Finalize(JNIEnv *env, jobject obj)
    {
        vx_graph g = (vx_graph)GetHandle(env, obj, GraphClass, handleName);
        vxReleaseGraph(&g);
        SetHandle(env, obj, GraphClass, handleName, 0);
    }

    static jint getNumNodes(JNIEnv *env, jobject obj)
    {
        vx_graph g = (vx_graph)GetHandle(env, obj, GraphClass, handleName);
        jint value = 0;
        vx_status status = vxQueryGraph(g, VX_GRAPH_NUMNODES, &value, sizeof(value));
        if (status != VX_SUCCESS)
            value = 0;
        return value;
    }

    static jobject createNode(JNIEnv *env, jobject obj, jlong k)
    {
        vx_graph g = (vx_graph)GetHandle(env, obj, GraphClass, handleName);
        jclass c = env->FindClass(NodeClass);
        jmethodID id = env->GetMethodID(c, "<init>", "(JJ)V");
        jobject node = env->NewObject(c, id, (jlong)g, k);
        return node;
    }

    static jint Verify(JNIEnv *env, jobject obj)
    {
        vx_graph g = (vx_graph)GetHandle(env, obj, GraphClass, handleName);
        vx_status status = vxVerifyGraph(g);
        return (jint)status;
    }

    static jint Process(JNIEnv *env, jobject obj)
    {
        vx_graph g = (vx_graph)GetHandle(env, obj, GraphClass, handleName);
        vx_status status = vxProcessGraph(g);
        return (jint)status;
    }

    static JNINativeMethod method_table[] = {
        // { name,                         signature,                 function_pointer }
        { "create",                        "(J)V",                    (void *)Initialize },
        { "destroy",                       "()V",                     (void *)Finalize },
        { "getNumNodes",                   "()I",                     (void *)getNumNodes },
        { "_createNode",                   "(J)"OBJECT(Node),         (void *)createNode },
        { "verify",                        "()I",                     (void *)Verify },
        { "process",                       "()I",                     (void *)Process },
    };

    int register_org_khronos_OpenVX_Graph(JNIEnv *env)
    {
        PrintJNITable(LOG_TAG, GraphClass, method_table, NELEM(method_table));
        return jniRegisterNativeMethods(env, GraphClass, method_table, NELEM(method_table));
    }
};



