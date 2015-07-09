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

#ifndef FRACTION
#define FRACTION

#include <type_traits>

namespace ecpp {

    template <typename Tnum = int, typename Tden = int>
    class Fraction {
    public:

        static_assert(std::is_integral<Tnum>::value, "Tnum should be integral type.");
        static_assert(std::is_integral<Tden>::value, "Tden should be integral type.");

        Fraction() : _num(0), _den(0) {
        }

        constexpr Fraction(Tnum num, Tden den) : _num(num), _den(den) {
        }

        constexpr Tnum getNum() {
            return _num;
        }

        constexpr Tden getDen() {
            return _den;
        }

        // TODO: Implement math operators for Fraction / Fraction operations.

    private:
        Tnum _num;
        Tden _den;
    };

    template <typename T, typename Tnum, typename Tden>
    constexpr T operator *(const T &a, const Fraction<Tnum, Tden> &b) {

        static_assert(std::is_arithmetic<T>::value, "Arithmetic type needed.");
        static_assert(std::is_signed<T>::value == std::is_signed<Fraction<Tnum, Tden>>::value, "Signed mixed with unsigned.");

        return (a * static_cast<T> (b.getNum())) / static_cast<T> (b.getDen());
    }

    template <typename T, typename Tnum, typename Tden>
    constexpr T operator *(const Fraction<Tnum, Tden> &a, const T &b) {

        static_assert(std::is_arithmetic<T>::value, "Arithmetic type needed.");
        static_assert(std::is_signed<T>::value == std::is_signed<Fraction<Tnum, Tden>>::value, "Signed mixed with unsigned.");

        return (b * static_cast<T> (a.getNum())) / static_cast<T> (a.getDen());
    }

    template <typename T, typename Tnum, typename Tden>
    constexpr T operator /(const T &a, const Fraction<Tnum, Tden> &b) {

        static_assert(std::is_arithmetic<T>::value, "Arithmetic type needed.");
        static_assert(std::is_signed<T>::value == std::is_signed<Fraction<Tnum, Tden>>::value, "Signed mixed with unsigned.");

        return (a * static_cast<T> (b.getDen())) / static_cast<T> (b.getNum());
    }

    // TODO: Implement other basic math operators, (Addition, Subtraction) return type will be Fraction<Tnum, Tden>.

    template <typename T>
    struct is_fraction {
        static constexpr bool value = false;
    };

    template <typename Tnum, typename Tden>
    struct is_fraction<Fraction<Tnum, Tden>> {
        static constexpr bool value = true;
    };
}

namespace std {

    template <typename Tnum, typename Tden>
    struct is_signed<ecpp::util::Fraction<Tnum, Tden>> {
        static constexpr bool value = std::is_signed<Tnum>::value || std::is_signed<Tden>::value;
    };
}

#endif // FRACTION
