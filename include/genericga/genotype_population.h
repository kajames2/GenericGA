#ifndef _GENERICGA_GENOTYPE_POPULATION_H_
#define _GENERICGA_GENOTYPE_POPULATION_H_

#include "genericga/fitness_collection.h"
#include "genericga/selector/abstract_selector.h"

namespace genericga {

template <class Gen>
class GenotypePopulation : public FitnessCollection {
 public:
  virtual void AddGenotypes(std::vector<Gen> genotypes) = 0;
  virtual Gen GetGenotype(int i) const = 0;
  virtual std::vector<Gen> GetGenotypes() const = 0;
  std::vector<Gen> SelectGenotypes(selector::AbstractSelector& selector,
                                   int n) const;
  std::vector<Gen> SelectGenotypes(std::vector<int> indices) const;
};

template <class Gen>
std::vector<Gen> GenotypePopulation<Gen>::SelectGenotypes(
    selector::AbstractSelector& selector, int n) const {
  return SelectGenotypes(selector.SelectIndices(*this, n));
}

template <class Gen>
std::vector<Gen> GenotypePopulation<Gen>::SelectGenotypes(
    std::vector<int> indices) const {
  std::vector<Gen> selected_genes;
  selected_genes.reserve(indices.size());
  for (auto index : indices) {
    selected_genes.push_back(GetGenotype(index));
  }
  return selected_genes;
}

}  // namespace genericga

#endif  // _GENERICGA_GENOTYPE_POPULATION_H_
