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

#ifndef FACTORY_H
#define FACTORY_H

#include "allocator.h"

#include <functional>
#include <memory>
#include <utility>

namespace ecpp {

class Factory {
public:

    Factory(Allocator &allocator) : _allocator(allocator) {
    }

    template <typename T, typename... X>
    std::unique_ptr<T, std::function<void(T *)>> create(X... x) {

        auto mem = _allocator.allocate(sizeof(T));

        auto deleter = [this] (T *t) {
            if (t != nullptr) {
                t->T::~T();
            }
            _allocator.deallocate(t);
        };

        return std::unique_ptr<T, std::function<void(T *)>> (new (mem) T(std::forward<X> (x)...), deleter);
    }

    template <typename T>
    std::unique_ptr<T[], std::function<void(T *)>> createArray(std::size_t n) {

        auto mem = _allocator.allocate(sizeof(T) * n);

        auto deleter = [this, n] (T *t) {
            T *tI = t;
            for (std::size_t i = 0; i < n; ++i, ++tI) {
                if (tI != nullptr) {
                    tI->T::~T();
                }
            }
            _allocator.deallocate(t);
        };

        return std::unique_ptr<T[], std::function<void(T *)>> (new (mem) T[n], deleter);
    }

private:
    Allocator &_allocator;

};

} // ecpp

#endif // FACTORY_H
