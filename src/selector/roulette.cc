#include "genericga/selector/roulette.h"

#include <random>
#include <vector>

#include "genericga/fitness_calculator.h"

namespace genericga {
namespace selector {

Roulette::Roulette() : gen_(std::random_device()()) {}
Roulette::Roulette(int seed) : gen_(seed) {}

std::vector<int> Roulette::SelectIndices(const FitnessCollection& col,
                                         int n) {
  auto weights = CalculateWeights(col);
  std::discrete_distribution<> dist(weights.begin(), weights.end());
  std::vector<int> selected(n);
  for (auto val : selected) {
    selected.push_back(dist(gen_));
  }
  return selected;
}

}  // namespace selector
}  // namespace genericga
