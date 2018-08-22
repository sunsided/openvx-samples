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

public class Scalar extends Reference {
    protected Scalar(long c, byte v)   { create(c, v); }
    protected Scalar(long c, short v)  { create(c, v); }
    protected Scalar(long c, int v)    { create(c, v); }
    protected Scalar(long c, long v)   { create(c, v); }
    protected Scalar(long c, float v)  { create(c, v); }
    protected Scalar(long c, double v) { create(c, v); }

    private native void create(long c, byte v);
    private native void create(long c, short v);
    private native void create(long c, int v);
    private native void create(long c, long v);
    private native void create(long c, float v);
    private native void create(long c, double v);

    public native void destroy();

    public native void setValue(byte value);
    public native void setValue(short value);
    public native void setValue(int value);
    public native void setValue(long value);
    public native void setValue(float value);
    public native void setValue(double value);

    public native byte getByteValue();
    public native short getShortValue();
    public native int getIntValue();
    public native long getLongValue();
    public native float getFloatValue();
    public native double getDoubleValue();
}
