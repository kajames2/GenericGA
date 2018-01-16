#ifndef _STRATEGY_SELECTOR_H_
#define _STRATEGY_SELECTOR_H_

#include "ga_strategy.h"
#include <memory>
#include <vector>

namespace genericga {

template <class In, class Out> struct StrategySelector {
public:
  virtual std::vector<std::shared_ptr<GAStrategy<In, Out>>>
  Select(const std::vector<std::shared_ptr<GAStrategy<In, Out>>> strats);
};
} // namespace genericga

#endif // _STRATEGY_SELECTOR_H_
