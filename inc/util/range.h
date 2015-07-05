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

#ifndef RANGE
#define RANGE

namespace ecpp {
    namespace util {

        template <typename T>
        class Range {
        public:

            constexpr Range(T from, T to) : _from(from), _to(to) {
            }

            constexpr T from() const {
                return _from;
            }

            constexpr T to() const {
                return _to;
            }

            bool contains(const T &value) const {
                if ((_from == 0) && (_to == 0)) {
                    return true;
                }

                return (_from <= value) && (value <= _to);
            }

            T apply(const T &value) const {
                if ((_from == 0) && (_to == 0)) {
                    return value;
                }

                if (value < _from) {
                    return _from;
                }

                if (_to < value) {
                    return _to;
                }

                return value;
            }

        private:
            T _from;
            T _to;
        };
    }
}

#endif // RANGE

