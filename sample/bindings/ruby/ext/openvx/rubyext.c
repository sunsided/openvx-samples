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

#include <rubyext.h>

void rubyext_variables(rext_variable_t *variables, long num)
{
    long v;
    for (v = 0; v < num; v++)
    {
        rb_define_hooked_variable(variables[v].name,
                                  variables[v].pval,
                                  variables[v].getter,
                                  variables[v].setter);
    }
}


void rubyext_constants(VALUE parent, rext_const_t *constants, long numConstants)
{
    int c;
    for (c = 0; c < numConstants; c++)
    {
        if (constants[c].type == T_FLOAT)
        {
            rb_define_const(parent,
                            constants[c].name,
                            rb_float_new(constants[c].value.f));
            REXT_PRINT("Constants %s type=%d (under %ld) = %lf\n", constants[c].name, constants[c].type, parent, constants[c].value.f);
        } else if (constants[c].type == T_FIXNUM) {
            rb_define_const(parent,
                            constants[c].name,
                            INT2FIX(constants[c].value.l));
            REXT_PRINT("Constants %s type=%d (under %ld) = 0x%x=%ld\n", constants[c].name, constants[c].type, parent, constants[c].value.l, constants[c].value.l);
         }
    }
}

void rubyext_methods(VALUE parent,
                     long type,
                     rext_method_t *methods,
                     long numMethods)
{
    long m;
    for (m = 0; m < numMethods; m++)
    {
        REXT_PRINT("Methods %s type=%ld (under %ld)\n", methods[m].name, type, parent);
        switch (type)
        {
            case REXT_METHOD_SINGLETON:
                rb_define_singleton_method(parent,
                                           methods[m].name,
                                           methods[m].func,
                                           methods[m].argc);
                break;
            case REXT_METHOD_NORMAL:
                rb_define_method(parent,
                                 methods[m].name,
                                 methods[m].func,
                                 methods[m].argc);
                break;
            case REXT_METHOD_MODULE:
                rb_define_module_method(parent,
                                        methods[m].name,
                                        methods[m].func,
                                        methods[m].argc);
                break;
            case REXT_METHOD_GLOBAL:
                rb_define_global_method(methods[m].name,
                                        methods[m].func,
                                        methods[m].argc);
                break;
            default:
                break;
        }
    }
}

void rubyext_objects(VALUE parent, rext_object_t *objects, long numObjects)
{
    long obj, m;
    for (obj = 0; obj < numObjects; obj++)
    {
        if (parent == Qnil) {
            objects[obj].typeVal = rb_define_class(objects[obj].name,
                                                   *objects[obj].base);
            REXT_PRINT("Object %s=%ld\n", objects[obj].name, objects[obj].typeVal);
        } else {
            objects[obj].typeVal = rb_define_class_under(parent,
                                                     objects[obj].name,
                                                     *objects[obj].base);
            REXT_PRINT("Object %s=%ld (under %ld)\n", objects[obj].name, objects[obj].typeVal, parent);
        }
        if (objects[obj].typeVal == 0)
            continue;

        rb_define_alloc_func(objects[obj].typeVal, objects[obj].allocate);

        rubyext_constants(objects[obj].typeVal,
                          objects[obj].constants,
                          objects[obj].numConstants);

        rubyext_methods(objects[obj].typeVal,
                        REXT_METHOD_NORMAL,
                        objects[obj].methods,
                        objects[obj].numMethods);
     }
}

void rubyext_modules(VALUE parent, rext_module_t *modules, long numModules)
{
    long mod;

    for (mod = 0; mod < numModules; mod++)
    {
        rext_const_t *constants = modules[mod].constants;
        rext_object_t *objects = modules[mod].objects;
        rext_method_t *methods = modules[mod].methods;

        if (parent == Qnil) {
            modules[mod].module = rb_define_module(modules[mod].name);
            REXT_PRINT("Module %s=%ld\n", modules[mod].name, modules[mod].module);
        } else {
            modules[mod].module = rb_define_module_under(parent, modules[mod].name);
            REXT_PRINT("Module %s=%ld (under %ld)\n", modules[mod].name, modules[mod].module, parent);
        }
        if (modules[mod].module)
        {
            rubyext_constants(modules[mod].module,
                              modules[mod].constants,
                              modules[mod].numConstants);

            rubyext_methods(modules[mod].module,
                            0,
                            modules[mod].methods,
                            modules[mod].numMethods);

            rubyext_objects(modules[mod].module,
                            modules[mod].objects,
                            modules[mod].numObjects);
        }
        else
        {
            printf("Module %s failed to be defined!\n", modules[mod].name);
        }
    }
}

