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

#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <cstdint>

namespace ecpp {
    namespace utils {

        template<typename T>
        static void byteSwap(T &subject) {
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

        // Using de Bruijn Sequences to Index a 1 in a Computer Word:
        // http://supertech.csail.mit.edu/papers/debruijn.pdf
        static constexpr unsigned int deBruijn[] = {0u, 1u, 28u, 2u, 29u, 14u, 24u, 3u, 30u, 22u, 20u, 15u, 25u, 17u, 4u, 8u,
                                                    31u, 27u, 13u, 23u, 21u, 19u, 16u, 7u, 26u, 12u, 18u, 6u, 11u, 5u, 10u, 9u};
        constexpr inline int bitPosition(std::uint32_t v) {
            return deBruijn[(static_cast<std::uint32_t>((v & -v) * 0x077CB531u)) >> 27];
        }
    }
}

#endif // UTILS_H
