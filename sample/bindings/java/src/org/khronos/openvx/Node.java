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

public class Node extends Reference {
    protected Node(long g, long k) { create(g, k); }
    private native void create(long g, long k);
    public native void destroy();
    //public native Perf getPerf();
    //public native int getStatus();
    public native Parameter getParameter(int index);
    public int setParameter(int index, int direction, Scalar v) {
        return _setParameter(index, direction, v.getType(), v.handle);
    }
    public int setParameter(int index, int direction, Buffer v){
        return _setParameter(index, direction, v.getType(), v.handle);
    }
    public int setParameter(int index, int direction, Image v){
        return _setParameter(index, direction, v.getType(), v.handle);
    }
    private native int _setParameter(int index, int direction, int type, long r);
}
