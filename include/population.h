#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "ga_strategy.h"
#include <vector>
#include <memory>

namespace genericga {

template <class In, class Out> struct Population {
public:
  Population(const std::vector<std::shared_ptr<GAStrategy<In, Out>>> strats);
  Population SelectStrats(const StrategySelector<In, Out>& selector) {
    selector.Select(strats_);
  }

private:
  std::vector<std::shared_ptr<GAStrategy<In, Out>>> strats_;
};

} // namespace genericga

#endif // _POPULATION_H_
