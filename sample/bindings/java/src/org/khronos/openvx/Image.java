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

public class Image extends Reference {
    protected Image(long c, int w, int h, int f) { create(c,w,h,f); }
    private native void create(long c, int w, int h, int f);
    public native void destroy();
    public native int getWidth();
    public native int getHeight();
    public native int getFormat();
    public native int computePatchSize(int sx, int sy, int ex, int ey, int plane);
    public native int getPatch(int sx, int sy, int ex, int ey, int plane, byte[] data);
    public native int setPatch(int sx, int sy, int ex, int ey, int plane, byte[] data);
    public final static int VX_DF_IMAGE_Y800 = 0x30303859;
}
