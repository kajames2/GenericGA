#ifndef _RANDOM_SELECTOR_H_
#define _RANDOM_SELECTOR_H_

#include "ga_strategy.h"
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class In, class Out> struct RandomSelector {
public:
  RandomSelector() : gen_(std::random_device()()) {}
  explicit RandomSelector(int seed) : gen_(seed) {}
  virtual std::vector<double> CalculateWeights(
      std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats) const;

  std::vector<std::shared_ptr<GAStrategy<In, Out>>>
  Select(std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats,
         int n) override {
    auto weights = CalculateWeights();
    std::discrete_distribution<> dist(weights.begin(), weights.end());
    std::vector<int> ind_vec(n);
    for (int i = 0; i < n; ++i) {
      ind_vec[i] = dist(gen_);
    }
    return Select(strats, ind_vec);
  }

private:
  std::mt19937 gen_;
};
} // namespace genericga

#endif // _RANDOM_SELECTOR_H_
