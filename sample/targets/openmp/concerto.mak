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


ifeq ($(filter $(HOST_COMPILER),GCC CLANG),$(HOST_COMPILER))
include $(PRELUDE)
ifneq (,$(findstring EXPERIMENTAL_USE_OPENMP,$(SYSDEFS)))
SKIPBUILD:=
USE_OPENMP:=true
else
SKIPBUILD:=1
endif
TARGET := openvx-openmp
TARGETTYPE := dsmo
DEFFILE := openvx-target.def
CSOURCES = $(call all-c-files)
IDIRS += $(HOST_ROOT)/$(OPENVX_SRC)/include $(HOST_ROOT)/debug
SHARED_LIBS := openvx vxu
STATIC_LIBS := openvx-debug-lib openvx-extras-lib openvx-helper openvx-c_model-lib
include $(FINALE)
endif
