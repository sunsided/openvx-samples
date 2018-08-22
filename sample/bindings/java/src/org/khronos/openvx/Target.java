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

package org.khronos.openvx;

public class Target extends Reference {
    protected Target(long c, int index) {
        get(c, index);
    }
    private native void get(long c, int index);
    public native void release();

    public native int getIndex();
    public native String getName();
    public native int getNumKernels();
    public class TargetKernel {
        public TargetKernel() {
            enumeration = 0;
            name = "unknown";
        }
        public int enumeration;
        public String name;
    }
    public native TargetKernel[] getTable();
}

