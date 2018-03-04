#include "genericga/selector/tournament.h"

#include <algorithm>
#include <random>
#include <vector>

#include "genericga/fitness_collection.h"

namespace genericga {
namespace selector {

Tournament::Tournament(int tourn_size)
    : tourn_size_(tourn_size), gen_(std::random_device()()) {}

Tournament::Tournament(int tourn_size, int seed)
    : tourn_size_(tourn_size), gen_(seed) {}

std::vector<int> Tournament::SelectIndices(const FitnessCollection& col,
                                           int n) {
  dist = std::uniform_int_distribution<>(0, col.Size() - 1);
  std::vector<int> ind_vec(n);
  for (int i = 0; i < n; ++i) {
    ind_vec[i] = TournamentRound(col, GenerateTournamentIndices(col));
  }
  return ind_vec;
}

int Tournament::TournamentRound(const FitnessCollection& col,
                                std::vector<int> indices) {
  return *std::max_element(indices.begin(), indices.end(),
                           [&col](int i, int j) -> bool {
                             return col.GetFitness(i) < col.GetFitness(j);
                           });
}

std::vector<int> Tournament::GenerateTournamentIndices(
    const FitnessCollection& col) {
  std::vector<int> tourn_vec(tourn_size_);
  for (int i = 0; i < tourn_size_; ++i) {
    tourn_vec[i] = dist(gen_);
  }
  return tourn_vec;
}

}  // namespace selector
}  // namespace genericga
