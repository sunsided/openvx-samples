#!/usr/bin/ruby -w

# 

# Copyright (c) 2012-2017 The Khronos Group Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


require 'mkmf'
$preload = ["openvx"]
dir_config("openvx")
openvx_root = "#{ENV['OPENVX_ROOT']}"
openvx_out = "#{ENV['OPENVX_OUT']}"
openvx_inc = File.join(openvx_root,"include")
find_header("VX/vx.h",openvx_inc)
find_library("openvx","vxCreateContext",openvx_out)
find_library("vxu","vxuColorConvert",openvx_out)
$defs.push("-D_LITTLE_ENDIAN_") unless $defs.include?("-D_LITTLE_ENDIAN_")
$defs.push("-I#{ENV['OPENVX_ROOT']}/include")
$defs.push("-L#{ENV['OPENVX_OUT']}")
create_makefile("openvx/openvx")

