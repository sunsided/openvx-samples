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

/*!
 * \file
 * \brief The Histogram Kernels
 * \author Erik Rainey <erik.rainey@gmail.com>
 * \author Shervin Emami <semami@nvidia.com>
 */

#include <VX/vx.h>
#include <VX/vx_helper.h>

#include "vx_interface.h"

static vx_status VX_CALLBACK vxHistogramInputValidator(vx_node node, vx_uint32 index)
{
    vx_status status = VX_ERROR_INVALID_PARAMETERS;
    if (index == 0)
    {
        vx_image input = 0;
        vx_parameter param = vxGetParameterByIndex(node, index);

        vxQueryParameter(param, VX_PARAMETER_REF, &input, sizeof(input));
        if (input)
        {
            vx_df_image format = 0;
            vxQueryImage(input, VX_IMAGE_FORMAT, &format, sizeof(format));
            if (format == VX_DF_IMAGE_U8 || format == VX_DF_IMAGE_U16)
            {
                status = VX_SUCCESS;
            }
            vxReleaseImage(&input);
        }
        vxReleaseParameter(&param);
    }
    return status;
}

static vx_status VX_CALLBACK vxHistogramOutputValidator(vx_node node, vx_uint32 index, vx_meta_format_t *ptr)
{
    vx_status status = VX_ERROR_INVALID_PARAMETERS;
    if (index == 1)
    {
        vx_image src = 0;
        vx_parameter src_param = vxGetParameterByIndex(node, 0);
        vx_parameter dst_param = vxGetParameterByIndex(node, 1);
        vx_distribution dist;

        vxQueryParameter(src_param, VX_PARAMETER_REF, &src, sizeof(src));
        vxQueryParameter(dst_param, VX_PARAMETER_REF, &dist, sizeof(dist));
        if ((src) && (dist))
        {
            vx_uint32 width = 0, height = 0;
            vx_df_image format;
            vx_size numBins = 0;
            vxQueryDistribution(dist, VX_DISTRIBUTION_BINS, &numBins, sizeof(numBins));
            vxQueryImage(src, VX_IMAGE_WIDTH, &width, sizeof(height));
            vxQueryImage(src, VX_IMAGE_HEIGHT, &height, sizeof(height));
            vxQueryImage(src, VX_IMAGE_FORMAT, &format, sizeof(format));
            /* fill in the meta data with the attributes so that the checker will pass */
            ptr->type = VX_TYPE_DISTRIBUTION;
            status = VX_SUCCESS;
            vxReleaseDistribution(&dist);
            vxReleaseImage(&src);
        }
        vxReleaseParameter(&dst_param);
        vxReleaseParameter(&src_param);
    }
    return status;
}

static vx_status vxEqualizeHistInputValidator(vx_node node, vx_uint32 index)
{
    vx_status status = VX_ERROR_INVALID_PARAMETERS;
    if (index == 0)
    {
        vx_image input = 0;
        vx_parameter param = vxGetParameterByIndex(node, index);

        vxQueryParameter(param, VX_PARAMETER_REF, &input, sizeof(input));
        if (input)
        {
            vx_df_image format = 0;
            vxQueryImage(input, VX_IMAGE_FORMAT, &format, sizeof(format));
            if (format == VX_DF_IMAGE_U8)
            {
                status = VX_SUCCESS;
            }
            vxReleaseImage(&input);
        }
        vxReleaseParameter(&param);
    }
    return status;
}

static vx_status vxEqualizeHistOutputValidator(vx_node node, vx_uint32 index, vx_meta_format_t *ptr)
{
    vx_status status = VX_ERROR_INVALID_PARAMETERS;
    if (index == 1)
    {
        vx_parameter param = vxGetParameterByIndex(node, 0); /* we reference the input image */
        if (param)
        {
            vx_image input = 0;

            vxQueryParameter(param, VX_PARAMETER_REF, &input, sizeof(input));
            if (input)
            {
                vx_uint32 width = 0, height = 0;
                vxQueryImage(input, VX_IMAGE_WIDTH, &width, sizeof(width));
                vxQueryImage(input, VX_IMAGE_HEIGHT, &height, sizeof(height));
                ptr->type = VX_TYPE_IMAGE;
                ptr->dim.image.format = VX_DF_IMAGE_U8;
                ptr->dim.image.width = width;
                ptr->dim.image.height = height;
                status = VX_SUCCESS;
                vxReleaseImage(&input);
            }
            vxReleaseParameter(&param);
        }
    }
    return status;
}


static vx_param_description_t histogram_kernel_params[] = {
    {VX_INPUT, VX_TYPE_IMAGE, VX_PARAMETER_STATE_REQUIRED},
    {VX_OUTPUT, VX_TYPE_DISTRIBUTION, VX_PARAMETER_STATE_REQUIRED},
};

static vx_param_description_t equalize_hist_kernel_params[] = {
    {VX_INPUT, VX_TYPE_IMAGE, VX_PARAMETER_STATE_REQUIRED},
    {VX_OUTPUT, VX_TYPE_IMAGE, VX_PARAMETER_STATE_REQUIRED},
};


vx_cl_kernel_description_t histogram_kernel = {
    {
        VX_KERNEL_HISTOGRAM,
        "org.khronos.openvx.histogram",
        NULL,
        histogram_kernel_params, dimof(histogram_kernel_params),
        NULL,
        vxHistogramInputValidator,
        vxHistogramOutputValidator,
        NULL,
        NULL,
    },
    VX_CL_SOURCE_DIR""FILE_JOINER"vx_histogram.cl",
    "vx_histogram_8",
    INIT_PROGRAMS,
    INIT_KERNELS,
    INIT_NUMKERNELS,
    INIT_RETURNS,
    NULL,
};
/*
vx_kernel_description_t equalize_hist_kernel = {
    VX_KERNEL_EQUALIZE_HISTOGRAM,
    "org.khronos.openvx.equalize_histogram",
    vxEqualizeHistKernel,
    equalize_hist_kernel_params, dimof(equalize_hist_kernel_params),
    vxEqualizeHistInputValidator,
    vxEqualizeHistOutputValidator,
    NULL,
    NULL,
};

*/
