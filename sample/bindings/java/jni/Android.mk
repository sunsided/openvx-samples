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


LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
LOCAL_ARM_MODE := arm
LOCAL_CPPFLAGS := $(OPENVX_DEFS)
LOCAL_SRC_FILES := openvx_jni.cpp \
                   Context.cpp \
                   Image.cpp \
                   Buffer.cpp \
                   Scalar.cpp \
                   Kernel.cpp \
                   Graph.cpp \
                   Node.cpp \
                   Parameter.cpp \
                   Reference.cpp \
                   Target.cpp
                   # Convolution.cpp \
                   # Distribution.cpp \
                   # Matrix.cpp \

LOCAL_C_INCLUDES += $(JNI_H_INCLUDE) $(OPENVX_INC) $(OPENVX_TOP)/debug
LOCAL_SHARED_LIBRARIES += \
    libopenvx \
    libvxu \
    libcutils \
    libhardware \
    libhardware_legacy \
    libnativehelper \
    libsystem_server \
    libutils \
    libui \
    libdl \
    libbinder \
    libgui \
    libmedia

ifeq ($(TARGET_SIMULATOR),true)
ifeq ($(TARGET_OS),linux)
ifeq ($(TARGET_ARCH),x86)
LOCAL_LDLIBS += -lpthread -ldl -lrt
endif
endif
endif
ifeq ($(WITH_MALLOC_LEAK_CHECK),true)
    LOCAL_CFLAGS += -DMALLOC_LEAK_CHECK
endif
LOCAL_MODULE:= libopenvx_jni
include $(BUILD_SHARED_LIBRARY)
