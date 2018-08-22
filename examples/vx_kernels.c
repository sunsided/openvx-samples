/*

 * Copyright (c) 2013-2017 The Khronos Group Inc.
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
#include <VX/vx_helper.h>
#if defined(EXPERIMENTAL_USE_VARIANTS)
#include <VX/vx_khr_variants.h>
#endif
#if defined(EXPERIMENTAL_USE_TARGET)
#include <VX/vx_ext_target.h>
#endif


vx_node vx_create_specific_sobel(vx_context context, vx_graph graph, vx_bool easy)
{
    vx_node n = 0;
    if (easy == vx_false_e) {
        //! [firstmethod]
        vx_kernel kernel = vxGetKernelByEnum(context, VX_KERNEL_SOBEL_3x3);
        vx_node node = vxCreateGenericNode(graph, kernel);
        //! [firstmethod]
#if defined(EXPERIMENTAL_USE_TARGET)
        vx_target target = vxGetTargetByName(context, "gpu");
        vxAssignNodeAffinity(node, target);
#endif
#if defined(EXPERIMENTAL_USE_VARIANTS)
        //! [variant:firstmethod]
        vxChooseKernelVariant(node, "faster");
        //! [variant:firstmethod]
#endif
        n = node;
    } else {
#if defined(EXPERIMENTAL_USE_VARIANTS)
        //! [variant:second]
#if defined(EXPERIMENTAL_USE_TARGET)
        vx_kernel kernel = vxGetKernelByName(context, "cpu:org.khronos.openvx.sobel3x3:faster");
#else
        vx_kernel kernel = vxGetKernelByName(context, "org.khronos.openvx.sobel3x3:faster");
#endif
        vx_node node = vxCreateGenericNode(graph, kernel);
        //! [variant:second]
#else   /*defined(EXPERIMENTAL_USE_VARIANTS)*/
        //! [secondmethod]
        vx_kernel kernel = vxGetKernelByName(context, "org.khronos.openvx.sobel_3x3");
        vx_node node = vxCreateGenericNode(graph, kernel);
        //! [secondmethod]
#endif
        n = node;
    }
    return n;
}

