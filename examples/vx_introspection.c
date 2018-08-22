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
#include <stdlib.h>

#if defined(EXPERIMENTAL_USE_TARGET)
#include <VX/vx_ext_target.h>

vx_status vx_example_introspection()
{
    //! [context]
    vx_context context = vxCreateContext();
    //! [context]

    //! [targets]
    vx_uint32 num_targets = 0;
    vx_status status = vxQueryContext(context, VX_CONTEXT_TARGETS, &num_targets, sizeof(num_targets));
    //! [targets]
    vx_uint32 t, k, p;
    //! [target_loop]
    for (t = 0; t < num_targets; t++)
    //! [target_loop]
    {
        //! [target_by_index]
        vx_target target = vxGetTargetByIndex(context, t);
        //! [target_by_index]

        //! [target_name]
        vx_char target_name[VX_MAX_TARGET_NAME];
        status = vxQueryTarget(target, VX_TARGET_ATTRIBUTE_NAME, target_name, sizeof(target_name));
        //! [target_name]
        if (status == VX_SUCCESS) {
        //! [num]
        vx_size num_kernels = 0;
        status = vxQueryTarget(target, VX_TARGET_ATTRIBUTE_NUMKERNELS, &num_kernels, sizeof(num_kernels));
        //! [num]
        if (num_kernels > 0) {
        //! [malloc]
        vx_kernel_info_t *table = (vx_kernel_info_t *)calloc(num_kernels, sizeof(vx_kernel_info_t));
        status = vxQueryTarget(target, VX_TARGET_ATTRIBUTE_KERNELTABLE, table, num_kernels*sizeof(vx_kernel_info_t));
        //! [malloc]
        //! [kernel_loop]
        for (k = 0; k < num_kernels; k++)
        //! [kernel_loop]
        {
            //! [kernel]
            vx_kernel kernel = vxGetKernelByName(context, table[k].name);
            //! [kernel]

            //! [kernel_attr]
            vx_uint32 num_params = 0u;
            vx_char kernel_name[VX_MAX_KERNEL_NAME];
            status = vxQueryKernel(kernel, VX_KERNEL_PARAMETERS, &num_params, sizeof(num_params));
            status = vxQueryKernel(kernel, VX_KERNEL_NAME, kernel_name, sizeof(kernel_name));
            //! [kernel_attr]
            {
                //! [parameter_loop]
                vx_graph graph = vxCreateGraph(context);
                vx_node node = vxCreateGenericNode(graph, kernel);
                for (p = 0; p < num_params; p++)
                //! [parameter_loop]
                {
                    //! [parameter]
                    vx_parameter param = vxGetParameterByIndex(node, p);
                    //! [parameter]

                    //! [parameter_attr]
                    vx_enum dir, state, type;
                    status = vxQueryParameter(param, VX_PARAMETER_DIRECTION, &dir, sizeof(dir));
                    status = vxQueryParameter(param, VX_PARAMETER_STATE, &state, sizeof(state));
                    status = vxQueryParameter(param, VX_PARAMETER_TYPE, &type, sizeof(type));
                    //! [parameter_attr]
                }
                vxReleaseNode(&node);
                vxReleaseGraph(&graph);
            }
            vxReleaseKernel(&kernel);
        }
        }
        }
        vxReleaseTarget(&target);
    }
    //! [teardown]
    vxReleaseContext(&context);
    //! [teardown]
    return status;
}
#else

vx_status vx_example_introspection()
{
    //! [context]
    vx_context context = vxCreateContext();
    //! [context]
    //! [num]
    vx_size k, num_kernels = 0;
    vx_status status = vxQueryContext(context, VX_CONTEXT_UNIQUE_KERNELS, &num_kernels, sizeof(num_kernels));
    //! [num]
    if (num_kernels > 0) {
    //! [malloc]
    vx_size size = num_kernels * sizeof(vx_kernel_info_t);
    vx_kernel_info_t *table = (vx_kernel_info_t *)malloc(size);
    status = vxQueryContext(context, VX_CONTEXT_UNIQUE_KERNEL_TABLE, table, size);
    //! [malloc]

    //! [kernel_loop]
    for (k = 0; k < num_kernels; k++)
    //! [kernel_loop]
    {
        //! [kernel]
        vx_kernel kernel = vxGetKernelByName(context, table[k].name);
        //! [kernel]
        //! [kernel_attr]
        vx_uint32 p, num_params = 0u;
        status = vxQueryKernel(kernel, VX_KERNEL_PARAMETERS, &num_params, sizeof(num_params));
        //! [kernel_attr]
        if (status == VX_SUCCESS)
        {
            //! [parameter_loop]
            for (p = 0; p < num_params; p++)
            //! [parameter_loop]
            {
                //! [parameter]
                vx_parameter param = vxGetKernelParameterByIndex(kernel, p);
                //! [parameter]

                //! [parameter_attr]
                vx_enum dir, state, type;
                status = vxQueryParameter(param, VX_PARAMETER_DIRECTION, &dir, sizeof(dir));
                status = vxQueryParameter(param, VX_PARAMETER_STATE, &state, sizeof(state));
                status = vxQueryParameter(param, VX_PARAMETER_TYPE, &type, sizeof(type));
                //! [parameter_attr]
            }
        }
        vxReleaseKernel(&kernel);
    }
    }
    //! [teardown]
    vxReleaseContext(&context);
    //! [teardown]
    return status;
}

#endif
