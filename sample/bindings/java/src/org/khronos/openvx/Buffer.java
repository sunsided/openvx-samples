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

public class Buffer extends Reference {
    protected Buffer(long c, int unitSize, int numUnits) {
        create(c, unitSize, numUnits);
    }
    private native void create(long c, int us, int nu);
    public native void destroy();
    public native int getUnitSize();
    public native int getNumUnits();
    public native int computeRangeSize(int start, int end);
    public native int getRange(int start, int end, byte[] data);
    public native int setRange(int start, int end, byte[] data);
    public native int getRange(int start, int end, short[] data);
    public native int setRange(int start, int end, short[] data);
    public native int getRange(int start, int end, int[] data);
    public native int setRange(int start, int end, int[] data);
    public native int getRange(int start, int end, long[] data);
    public native int setRange(int start, int end, long[] data);
    public native int getRange(int start, int end, float[] data);
    public native int setRange(int start, int end, float[] data);
    public native int getRange(int start, int end, double[] data);
    public native int setRange(int start, int end, double[] data);
}
