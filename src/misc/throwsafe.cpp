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

// The methods in this file are here to protect agains exceptions thrown from the STL. They override the methods
// defined in the libraries that ship with GCC.

// The list was obtained with the following command:
//     objdump /usr/lib/gcc/x86_64-linux-gnu/4.8/*.a -S | grep "__throw_" | c++filt | awk '{print $9 " " $10}' | sed 's/<//' | sed 's/).*/)/' | sort | uniq

/*
Output:

std::__throw_bad_alloc()
std::__throw_bad_cast()
std::__throw_bad_exception()
std::__throw_bad_function_call()
std::__throw_bad_typeid()
std::__throw_domain_error(char const*)
std::__throw_future_error(int)
std::__throw_invalid_argument(char const*)
std::__throw_ios_failure(char const*)
std::__throw_length_error(char const*)
std::__throw_logic_error(char const*)
std::__throw_out_of_range(char const*)
std::__throw_overflow_error(char const*)
std::__throw_range_error(char const*)
std::__throw_regex_error(std::regex_constants::error_type)
std::__throw_runtime_error(char const*)
std::__throw_system_error(int)
std::__throw_underflow_error(char const*)

*/

#ifndef NO_THROW_SAFETY

#include <cstdlib>
#include <regex>

namespace std {

    void __throw_bad_alloc() {
        abort();
    }

    void __throw_bad_cast() {
        abort();
    }

    void __throw_bad_exception() {
        abort();
    }

    void __throw_bad_function_call() {
        abort();
    }

    void __throw_bad_typeid() {
        abort();
    }

    void __throw_domain_error(char const *s) {
        abort();
    }

    void __throw_future_error(int i) {
        abort();
    }

    void __throw_invalid_argument(char const *s) {
        abort();
    }

    void __throw_ios_failure(char const *s) {
        abort();
    }

    void __throw_length_error(char const *s) {
        abort();
    }

    void __throw_logic_error(char const *s) {
        abort();
    }

    void __throw_out_of_range(char const *s) {
        abort();
    }

    void __throw_overflow_error(char const *s) {
        abort();
    }

    void __throw_range_error(char const *s) {
        abort();
    }

    void __throw_regex_error(regex_constants::error_type t) {
        abort();
    }

    void __throw_runtime_error(char const *s) {
        abort();
    }

    void __throw_system_error(int i) {
        abort();
    }

    void __throw_underflow_error(char const *s) {
        abort();
    }
}

#endif
