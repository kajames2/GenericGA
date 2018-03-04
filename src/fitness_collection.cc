#include "genericga/fitness_collection.h"

#include <vector>

#include "genericga/vector_ops.h"

namespace genericga {

std::vector<double> FitnessCollection::GetFitnessRankings() const {
  return GetRankingsWithTies(GetFitnesses());
}

std::vector<int> FitnessCollection::GetFitnessOrderings() const {
  return GetOrderings(GetFitnesses());
}

int FitnessCollection::Size() const { return GetFitnesses().size(); }

}  // namespace genericga
