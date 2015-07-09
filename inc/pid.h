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

#ifndef PID
#define PID

#include "range.h"

#include <type_traits>

namespace ecpp {

    template <typename Tsignal = float, typename Tout = float, typename Tcfg = float>
    class Pid {
    public:

        static_assert(std::is_arithmetic<Tsignal>::value, "Signal type should be arithmetic type.");
        static_assert(std::is_arithmetic<Tout>::value, "Output type should be arithmetic type.");
        // TODO: Enable when fraction is arithmetic type.
        //static_assert(std::is_arithmetic<Tcfg>::value, "Config type should be arithmetic type.");
        static_assert(std::is_signed<Tsignal>::value, "Signal type should be signed type.");

        struct Config {
            Tsignal setPoint;
            Tcfg p;
            Tcfg i;
            Tcfg d;
            Range<Tout> outRange;
            Range<Tout> pRange;
            Range<Tout> iRange;
            Range<Tout> dRange;
        };

        Pid() {
            reset();
        }

        Pid(const Config &cfg): _cfg(cfg) {
            reset();
        }

        void configure(const Config &cfg) {
            _cfg = cfg;
        }

        void reset() {
            _output = 0;
            _previousError = 0;
            _accumulatedError = 0;
        }

        void update(const Tsignal &signal) {
            Tsignal error = _cfg.setPoint - signal;

            Tout pOut = _cfg.pRange.apply(error * _cfg.p);

            _accumulatedError = _cfg.iRange.apply(_accumulatedError + error);
            Tout iOut = _accumulatedError * _cfg.i;

            Tsignal diff = error - _previousError;
            Tout dOut = _cfg.dRange.apply(diff * _cfg.d);
            _previousError = error;

            _output = _cfg.outRange.apply(pOut + iOut + dOut);
        }

        const Tout &output() const {
            return _output;
        }

    private:
        Config _cfg;
        Tout _output;
        Tsignal _previousError;
        Tout _accumulatedError;
    };
}

#endif // PID

