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
    namespace mem {

        class Factory {
        public:

            template <typename T>
            class Deleter {
            public:
                Deleter() {
                }

                void operator()(T *t) const {
                    _lambda(t);
                }

                void setLambda(std::function<void(T *)> lambda) {
                    _lambda = lambda;
                }

            private:
                std::function<void(T *)> _lambda;
            };

            Factory(Allocator &allocator) : _allocator(allocator) {
            }

            template <typename T, typename... X>
            std::unique_ptr<T, Deleter<T>> create(X... x) {

                // Allocate the memory.
                void *mem = _allocator.allocate(sizeof(T));

                // Create the deleter and set its lambda function.
                Deleter<T> deleter;
                deleter.setLambda([this] (T *t) {
                    if (t != nullptr) {
                        t->T::~T();
                    }
                    _allocator.deallocate(t);
                });

                // Create smart pointer and return it.
                return std::unique_ptr<T, Deleter<T>>(new (mem) T(std::forward<X>(x)...), deleter);
            }

            template <typename T>
            std::unique_ptr<T[], Deleter<T>> createArray(std::size_t n) {

                // Allocate the memory.
                void *mem = _allocator.allocate(sizeof(T) * n);

                // Create deleter and set its lambda function.
                Deleter<T> deleter;
                deleter.setLambda([this, n] (T *t) {
                    T *tI = t;
                    for (std::size_t i = 0; i < n; ++i, ++tI) {
                        if (tI != nullptr) {
                            tI->T::~T();
                        }
                    }
                    _allocator.deallocate(t);
                });

                // Create smart pointer and return it.
                return std::unique_ptr<T[], Deleter<T>>(new (mem) T[n], deleter);
            }

        private:

            Allocator &_allocator;
        };
    }
}

#endif // FACTORY_H
