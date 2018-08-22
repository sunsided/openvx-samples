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

#ifndef _OPENVX_RUBY_H_
#define _OPENVX_RUBY_H_

/*!
 * \file
 * \brief The OpenVX Ruby Bindings
 * \author Erik Rainey <erik.rainey@gmail.com>
 *  \note There are several rules about using the Extensions API.
 * 1.) VALUE can take a POINTER (it's an unsigned long).
 * 2.) Check_Type is required for every parameter
 */

#include <stdint.h>
#include <VX/vx.h>
#include <rubyext.h>

/*! \note This must match the order in \ref objects */
enum _vx_object_e {
    VX_OBJ_REF,
    VX_OBJ_KERNEL,
    VX_OBJ_GRAPH,
    VX_OBJ_IMAGE,
    VX_OBJ_NODE,
    VX_OBJ_PARAMETER,
    VX_OBJ_BUFFER,
    VX_OBJ_SCALAR,
    VX_OBJ_DISTRIBUTION,
    VX_OBJ_LUT,
    VX_OBJ_CONVOLUTION,
    VX_OBJ_MATRIX,
    VX_OBJ_THRESHOLD,
    // not really objects...
    VX_OBJ_KEYPOINT,
    VX_OBJ_RECTANGLE,
    VX_OBJ_COORDINATES,
};

#endif

