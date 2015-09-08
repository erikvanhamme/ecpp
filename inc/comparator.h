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

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <type_traits>

namespace ecpp {

/**
 * @brief This is the abstract base class for comparators.
 */
template <typename Ta, typename Tb = Ta>
class Comparator {
public:
    /**
     * @brief The compare method will compare 2 references with eachother and return the result.
     *
     * @param [in] a Operand a.
     * @param [in] b Operand b.
     *
     * @return Positive number if a < b, negative number if a > b, 0 if a = b.
     */
    virtual int compare(const Ta &a, const Tb&b) const = 0;
};

template <typename Ta, typename Tb = Ta>
class LessThanComparator : public Comparator<Ta, Tb> {
public:
    static LessThanComparator<Ta, Tb> &getInstance() {
        static LessThanComparator<Ta, Tb> instance;
        return instance;
    }

    virtual int compare(const Ta &a, const Tb &b) const override {
        static_assert(std::is_arithmetic<Ta>::value, "Type A: Arithmetic type required.");
        static_assert(std::is_arithmetic<Tb>::value, "Type B: Arithmetic type required.");

        if (a < b) {
            return 1;
        } else if (a > b) {
            return -1;
        } else {
            return 0;
        }
    }

private:
    LessThanComparator() {
    }
};

template <typename Ta, typename Tb>
class GreaterThenComparator : public Comparator<Ta, Tb> {
public:
    static GreaterThenComparator<Ta, Tb> &getInstance() {
        static GreaterThenComparator<Ta, Tb> instance;
        return instance;
    }

    virtual int compare(const Ta &a, const Tb &b) const override {
        static_assert(std::is_arithmetic<Ta>::value, "Type A: Arithmetic type required.");
        static_assert(std::is_arithmetic<Tb>::value, "Type B: Arithmetic type required.");

        if (a > b) {
            return 1;
        } else if (a < b) {
            return -1;
        } else {
            return 0;
        }
    }
};

}

#endif // COMPARATOR_H
