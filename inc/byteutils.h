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

#ifndef BYTEUTILS_H
#define BYTEUTILS_H

#include <cstddef>
#include <cstdint>

namespace ecpp {
    namespace util {

        template<typename T>
        void byteSwap(T &subject) {
            constexpr std::size_t subjectSize = sizeof(T);
            std::uint8_t *data = reinterpret_cast<std::uint8_t *>(&subject);
            for (std::uint8_t *p = data, *end = (data + subjectSize - 1); p < end; ++p, --end) {
                std::uint8_t swap = *p;
                *p = *end;
                *end = swap;
            }
        }

        template<>
        void byteSwap<std::uint8_t>(std::uint8_t &subject);

        template<>
        void byteSwap<std::int8_t>(std::int8_t &subject);

        template<>
        void byteSwap<std::uint16_t>(std::uint16_t &subject);

        template<>
        void byteSwap<std::int16_t>(std::int16_t &subject);

        template<>
        void byteSwap<std::uint32_t>(std::uint32_t &subject);

        template<>
        void byteSwap<std::int32_t>(std::int32_t &subject);

        template <>
        void byteSwap<std::uint64_t>(std::uint64_t &subject);

        template <>
        void byteSwap<std::int64_t>(std::int64_t &subject);
    }
}

#endif // BYTEUTILS_H
