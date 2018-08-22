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

#define LOG_TAG "Image_JNI"
#include "openvx_jni.h"

namespace android
{
    //**************************************************************************
    // LOCAL VARIABLES
    //**************************************************************************

    //**************************************************************************
    // EXPORTED FUNCTIONS
    //**************************************************************************
    static void Initialize(JNIEnv *env, jobject obj, jlong c, jint w, jint h, jint f)
    {
        vx_context context = (vx_context)c;
        vx_image i = vxCreateImage(context, w, h, f);
        SetHandle(env, obj, ImageClass, parentName, c);
        SetHandle(env, obj, ImageClass, handleName, (jlong)i);
    }

    static void Finalize(JNIEnv *env, jobject obj)
    {
        vx_image i = (vx_image)GetHandle(env, obj, ImageClass, handleName);
        vxReleaseImage(&i);
        SetHandle(env, obj, ImageClass, handleName, 0);
    }

    static jint getWidth(JNIEnv *env, jobject obj)
    {
        vx_image i = (vx_image)GetHandle(env, obj, ImageClass, handleName);
        jint value = 0;
        vx_status status = vxQueryImage(i, VX_IMAGE_WIDTH, &value, sizeof(value));
        if (status != VX_SUCCESS)
            value = 0;
        return value;
    }

    static jint getHeight(JNIEnv *env, jobject obj)
    {
        vx_image i = (vx_image)GetHandle(env, obj, ImageClass, handleName);
        jint value = 0;
        vx_status status = vxQueryImage(i, VX_IMAGE_HEIGHT, &value, sizeof(value));
        if (status != VX_SUCCESS)
            value = 0;
        return value;
    }

    static jint getFormat(JNIEnv *env, jobject obj)
    {
        vx_image i = (vx_image)GetHandle(env, obj, ImageClass, handleName);
        jint value = 0;
        vx_status status = vxQueryImage(i, VX_IMAGE_HEIGHT, &value, sizeof(value));
        if (status != VX_SUCCESS)
            value = 0;
        return value;
    }

    static jint computePatchSize(JNIEnv *env, jobject obj, jint sx, jint sy, jint ex, jint ey, jint p)
    {
        vx_image i = (vx_image)GetHandle(env, obj, ImageClass, handleName);
        vx_rectangle_t rect = {sx, sy, ex, ey};
        jint size = vxComputeImagePatchSize(i, &rect, p);
        return size;
    }

    static jint getPatch(JNIEnv *env, jobject obj, jint sx, jint sy, jint ex, jint ey, jint p, jbyteArray data)
    {
        void *patch = NULL;
        vx_status status = VX_FAILURE;
        vx_imagepatch_addressing_t addr;
        vx_image i = (vx_image)GetHandle(env, obj, ImageClass, handleName);
        jbyte *ptr = env->GetByteArrayElements(data, NULL);
        if (ptr)
        {
            vx_rectangle_t rect = {sx, sy, ex, ey};
            status = vxAccessImagePatch(i, &rect, p, &addr, (void **)&ptr, VX_READ_AND_WRITE);
            env->ReleaseByteArrayElements(data, ptr, 0);
        }
        return (jint)status;
    }

    static jint setPatch(JNIEnv *env, jobject obj, jint sx, jint sy, jint ex, jint ey, jint p, jbyteArray data)
    {
        void *patch = NULL;
        vx_status status = VX_FAILURE;
        vx_imagepatch_addressing_t addr;
        vx_image i = (vx_image)GetHandle(env, obj, ImageClass, handleName);
        jbyte *ptr = env->GetByteArrayElements(data, NULL);
        if (ptr)
        {
            vx_rectangle_t rect = {sx, sy, ex, ey};
            status = vxCommitImagePatch(i, &rect, p, &addr, ptr);
            env->ReleaseByteArrayElements(data, ptr, 0);
        }
        return (jint)status;
    }

    static JNINativeMethod method_table[] = {
        // { name,                         signature,                 function_pointer }
        { "create",                        "(JIII)V",                 (void *)Initialize },
        { "destroy",                       "()V",                     (void *)Finalize },

        { "getWidth",                      "()I",                     (void *)getWidth },
        { "getHeight",                     "()I",                     (void *)getHeight },
        { "getFormat",                     "()I",                     (void *)getFormat },

        { "computePatchSize",              "(IIIII)I",                (void *)computePatchSize },
        { "getPatch",                      "(IIIII[B)I",              (void *)getPatch },
        { "setPatch",                      "(IIIII[B)I",              (void *)setPatch },

    };

    int register_org_khronos_OpenVX_Image(JNIEnv *env)
    {
        PrintJNITable(LOG_TAG, ImageClass, method_table, NELEM(method_table));
        return jniRegisterNativeMethods(env, ImageClass, method_table, NELEM(method_table));
    }
};



