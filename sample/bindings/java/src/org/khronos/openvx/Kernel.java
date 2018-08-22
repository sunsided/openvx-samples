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

public class Kernel extends Reference {
    protected Kernel(long c, String name) { get(c, name); }
    protected Kernel(long c, int kenum) { get(c, kenum); }
    private native void get(long c, String kname);
    private native void get(long c, int kenum);
    public native void release();
    public native int getNumParameters();
    public native String name();
    public static final int INPUT = 0;
    public static final int OUTPUT = 1;
    public static final int BIDIRECTIONAL = 2;
}
