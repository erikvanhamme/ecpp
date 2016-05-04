/*
 * Copyright 2015 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

namespace ecpp {

class Allocator {
public:
    Allocator();
    virtual ~Allocator();

    virtual void *allocate(std::size_t size);
    virtual void deallocate(void *address);
};

} // ecpp

#endif // ALLOCATOR_H
