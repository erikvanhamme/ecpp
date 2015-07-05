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

#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include <cstdint>

struct Endian {
private:
    static constexpr uint32_t WORD = 0x01020304;
    static constexpr uint8_t BYTE = static_cast<const uint8_t &> (WORD);

    static_assert(BYTE != 0x02, "Middle endianness is not supported.");
    static_assert(BYTE != 0x03, "Middle endianness is not supported.");

    Endian() = delete;

public:
    static constexpr bool LITTLE = (BYTE == 0x04);
    static constexpr bool BIG = (BYTE == 0x01);

    static_assert(LITTLE || BIG, "Unknown endianness.");
};

#endif // ENDIANNESS_H
