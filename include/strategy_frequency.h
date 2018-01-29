#ifndef _STRATEGY_FREQUENCY_H_
#define _STRATEGY_FREQUENCY_H_

#include "ga_strategy.h"

namespace genericga {

template <class Gen, class Phen> class StrategyFrequency {
public:
  GAStrategy<Gen, Phen> strategy;
  int frequency;
  bool operator<(const StrategyFrequency other) {
    return strategy < other.strategy;
  }
};

} // namespace genericga

#endif // _STRATEGY_FREQUENCY_H_
