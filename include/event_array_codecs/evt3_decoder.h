// -*-c++-*--------------------------------------------------------------------
// Copyright 2022 Bernd Pfrommer <bernd.pfrommer@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EVENT_ARRAY_CODECS__EVT3_DECODER_H_
#define EVENT_ARRAY_CODECS__EVT3_DECODER_H_

#include <stdint.h>

#include <memory>
#include <string>

#include "event_array_codecs/decoder.h"

namespace event_array_codecs
{
namespace evt3
{
class Decoder : public event_array_codecs::Decoder
{
public:
  using timestamp_t = uint64_t;

  void decode(const uint8_t * buf, size_t bufSize, EventProcessor * processor) override;
  void summarize(
    const uint8_t * buf, size_t size, uint64_t * firstTS, uint64_t * lastTS,
    size_t * numEventsOnOff) override;
  void setTimeBase(uint64_t) override
  {
    // no-op
  }
  bool findFirstSensorTime(const uint8_t * buf, size_t size, uint64_t * firstTS) override;

private:
  // --------------------- variables
  size_t numEvents_{0};
  uint16_t ey_{0};              // current y coordinate
  uint16_t timeLow_{0};         // time stamp low
  timestamp_t timeHigh_{0};     // time stamp high + rollover bits
  uint16_t lastHigh_{0};        // for debugging
  uint16_t lastTimeLow_{0};     // for debugging
  uint8_t currentPolarity_{0};  // polarity for vector event
  uint16_t currentBaseX_{0};    // X coordinate basis for vector event
};
}  // namespace evt3
}  // namespace event_array_codecs
#endif  // EVENT_ARRAY_CODECS__EVT3_DECODER_H_
