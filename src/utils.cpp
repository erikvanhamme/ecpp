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

#include "utils.h"

#include <cstdint>

template<>
void ecpp::utils::byteSwap<std::uint8_t>(std::uint8_t &subject) {
    (void) subject;
}

template<>
void ecpp::utils::byteSwap<std::int8_t>(std::int8_t &subject) {
    (void) subject;
}

template<>
void ecpp::utils::byteSwap<std::uint16_t>(std::uint16_t &subject) {
    std::uint8_t a = subject >> 8;
    std::uint8_t b = subject;
    subject = (static_cast<std::uint16_t>(b) << 8) | a;
}

template<>
void ecpp::utils::byteSwap<std::int16_t>(std::int16_t &subject) {
    std::uint8_t a = subject >> 8;
    std::uint8_t b = subject;
    subject = (static_cast<std::int16_t>(b) << 8) | a;
}

template<>
void ecpp::utils::byteSwap<std::uint32_t>(std::uint32_t &subject) {
    std::uint8_t a = subject >> 24;
    std::uint8_t b = subject >> 16;
    std::uint8_t c = subject >> 8;
    std::uint8_t d = subject;
    subject = (static_cast<std::uint32_t>(d) << 24) | (static_cast<std::uint32_t>(c) << 16) |
            (static_cast<std::uint32_t>(b) << 8) | a;
}

template<>
void ecpp::utils::byteSwap<std::int32_t>(std::int32_t &subject) {
    std::uint8_t a = subject >> 24;
    std::uint8_t b = subject >> 16;
    std::uint8_t c = subject >> 8;
    std::uint8_t d = subject;
    subject = (static_cast<std::int32_t>(d) << 24) | (static_cast<std::int32_t>(c) << 16) |
            (static_cast<std::int32_t>(b) << 8) | a;
}

template <>
void ecpp::utils::byteSwap<std::uint64_t>(std::uint64_t &subject) {
    std::uint8_t a = subject >> 56;
    std::uint8_t b = subject >> 48;
    std::uint8_t c = subject >> 40;
    std::uint8_t d = subject >> 32;
    std::uint8_t e = subject >> 24;
    std::uint8_t f = subject >> 16;
    std::uint8_t g = subject >> 8;
    std::uint8_t h = subject;
    subject = (static_cast<std::uint64_t>(h) << 56) | (static_cast<std::uint64_t>(g) << 48) |
            (static_cast<std::uint64_t>(f) << 40) | (static_cast<std::uint64_t>(e) << 32) |
            (static_cast<std::uint64_t>(d) << 24) | (static_cast<std::uint64_t>(c) << 16) |
            (static_cast<std::uint64_t>(b) << 8) | a;
}

template <>
void ecpp::utils::byteSwap<std::int64_t>(std::int64_t &subject) {
    std::uint8_t a = subject >> 56;
    std::uint8_t b = subject >> 48;
    std::uint8_t c = subject >> 40;
    std::uint8_t d = subject >> 32;
    std::uint8_t e = subject >> 24;
    std::uint8_t f = subject >> 16;
    std::uint8_t g = subject >> 8;
    std::uint8_t h = subject;
    subject = (static_cast<std::int64_t>(h) << 56) | (static_cast<std::int64_t>(g) << 48) |
            (static_cast<std::int64_t>(f) << 40) | (static_cast<std::int64_t>(e) << 32) |
            (static_cast<std::int64_t>(d) << 24) | (static_cast<std::int64_t>(c) << 16) |
            (static_cast<std::int64_t>(b) << 8) | a;
}
