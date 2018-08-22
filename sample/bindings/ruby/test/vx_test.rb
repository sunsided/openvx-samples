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


require 'openvx'

def openvx_simple_demo
    graph = OpenVX::Graph.new
    input = OpenVX::Image.new(640, 480, OpenVX::Image::VX_DF_IMAGE_U8)
    output = OpenVX::Image.new(640, 480, OpenVX::Image::VX_DF_IMAGE_U8)
    node = OpenVX::CopyImageNode(graph, input, output)
    graph.verify
    graph.process
end

def openvx_debugging
    puts "OpenVX is a #{OpenVX.class}"
    OpenVX.constants.each {|c|
        puts "\tclass #{c}"
    }
    OpenVX::load("xyz")
    puts "There are #{OpenVX.num_kernels} kernels in OpenVX"
    puts "There are #{OpenVX.num_targets} targets in OpenVX"
    puts "There are #{OpenVX.num_modules} targets in OpenVX"
    kernel = OpenVX::Kernel.new("org.khronos.copy_image")
    puts "Copy image has #{kernel.params} parameters"
    graph = OpenVX::Graph.new
    puts "There are #{graph.nodes} nodes in the graph"
    images = [] # new array
    puts "VX_DF_IMAGE_Y800 = #{OpenVX::Image::VX_DF_IMAGE_Y800}"
    # Image from named hash
    images << OpenVX::Image.new({:width => 640,
                                 :height => 480,
                                 :format => OpenVX::Image::VX_DF_IMAGE_Y800})
    # explicit typed parameters
    images << OpenVX::Image.new(640, 480, OpenVX::Image::VX_DF_IMAGE_Y800)
    # "Virtual"
    images << OpenVX::Image.new
    # node construction takes an array
    node = OpenVX::CopyImageNode(graph, images[0], images[1])
    graph.verify
    graph.process
    node = nil
    images.map! {|i| i=nil }
    graph = nil
end

if __FILE__ == $0
    if (ARGV[0] == '-s')
        openvx_simple_demo()
    else
        openvx_debugging()
    end
end
