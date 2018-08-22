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

public class Parameter extends Reference {
    protected Parameter(long n, int i) { get(n,i); }
    private native void get(long n, int i);

    public native void release();

    //public native int getDirection();
    //public native int getType();
    //public native long getValue();

    //public native void setDirection(int direction);
    //public native void setType(int type);

    //public native void setValue(Scalar value);
    //public native void setValue(Buffer value);
    //public native void setValue(Image value);

}
