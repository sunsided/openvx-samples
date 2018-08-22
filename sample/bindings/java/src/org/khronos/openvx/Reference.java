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

public class Reference {
    /** Force the loading of the JNI object for every sub-class */
    static {
        System.loadLibrary("openvx_jni");
    }

    protected Reference() {
        parent = 0;
        handle = 0;
    }

    protected native int getType();
    protected native int getCount();

    /** The public variable to hold the parent reference of the objects */
    protected long parent;

    /** The protected variable to hold the handle to the JNI layer reference */
    protected long handle;
}
