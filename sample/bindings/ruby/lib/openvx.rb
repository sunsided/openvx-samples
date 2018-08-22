#!/usr/bin/ruby -w

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



require 'openvx/openvx'

module OpenVX
    VERSION = "1.0.0"
    def self.kernel_names
        khash = {}
        OpenVX.targets.each do |target|
            target.kernels.each do |kernel|
                khash[kernel.name] ||= 0
                khash[kernel.name] += 1
            end
            target = nil
        end
        return khash.keys.sort
    end

    def self.targets
        array = []
        for index in 0..OpenVX.num_targets-1 do
            array << OpenVX::Target.new(index)
        end
        return array
    end

    class Target
        def kernels
            array = []
            kernel_names.each do |name|
                array << OpenVX::Kernel.new(name)
            end
            return array
        end
    end

    def self.CopyImageNode(graph, input, output)
        return nil if graph.class != OpenVX::Graph
        return nil if input.class != OpenVX::Image
        return nil if output.class != OpenVX::Image

        kernel = OpenVX::Kernel.new("org.khronos.copy_image")
        node = OpenVX::Node.new(graph, kernel, [{:ref => input},
                                                {:ref => output}])
        kernel = nil
        return node
    end
end

