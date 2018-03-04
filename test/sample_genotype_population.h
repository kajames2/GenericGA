#ifndef _SAMPLE_GENOTYPE_POPULATION_H_
#define _SAMPLE_GENOTYPE_POPULATION_H_

#include <vector>

#include "genericga/genotype_population.h"

namespace gatests {
class SampleGenotypePopulation : public genericga::GenotypePopulation<int> {
 public:
  SampleGenotypePopulation()
      : fits(std::vector<double>{1, 3, 5, -2}), genes(std::vector<int>{6, 7, 8, 2}) {}
  std::vector<double> GetFitnesses() const override { return fits; }
  double GetFitness(int i) const override { return fits[i]; }
  void AddGenotypes(std::vector<int> genes) override {}
  int GetGenotype(int i) const override { return genes[i]; }
  std::vector<int> GetGenotypes() const override { return genes; }

 private:
  std::vector<double> fits;
  std::vector<int> genes;
};
}  // namespace gatests

#endif  // _SAMPLE_GENOTYPE_POPULATION_H_
