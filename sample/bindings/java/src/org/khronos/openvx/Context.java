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

public class Context extends Reference {
    public Context() { create(); }
    private native void create();
    public native void destroy();

    public native boolean loadKernels(String name);

    public native int getNumKernels();
    public native int getNumModules();
    public native int getNumReferences();
    public native int getNumTargets();

    public native Image createImage(int width, int height, int df_image);
    public native Buffer createBuffer(int unitSize, int numUnits);

    public native Scalar createScalar(byte value);
    public native Scalar createScalar(short value);
    public native Scalar createScalar(int value);
    public native Scalar createScalar(long value);
    public native Scalar createScalar(float value);
    public native Scalar createScalar(double value);

    public native Kernel getKernel(String name);
    public native Kernel getKernel(int kenum);

    public native Graph createGraph();

    public native Target getTarget(int index);
}
