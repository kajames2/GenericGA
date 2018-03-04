#ifndef _GENERICGA_POPULATION_H_
#define _GENERICGA_POPULATION_H_

#include <algorithm>
#include <vector>

#include "genericga/genotype_evaluator.h"
#include "genericga/genotype_population.h"

namespace genericga {

template <class Gen, class Phen>
class Population : public GenotypePopulation<Gen> {
 public:
  Population(GenotypeEvaluator<Gen, Phen> gen_eval, std::vector<Gen> genes);
  std::vector<double> GetFitnesses() const override;
  double GetFitness(int i) const override;
  void AddGenotypes(std::vector<Gen> genes) override;
  void SetGenotypes(std::vector<Gen> genes);
  void GetGenotype(int i) const override { return genes_[i]; }
  std::vector<Gen> GetGenotypes() const override { return genes_; }
  void SetFitnessCalculator(std::unique_ptr<FitnessCalculator<Phen>> fit_calc);

 private:
  std::vector<Gen> genes_;
  GenotypeEvaluator<Gen, Phen> gen_eval_;
};

template <class Gen, class Phen>
std::vector<double> Population<Gen, Phen>::GetFitnesses() const {
  return gen_eval_.GetFitnesses(genes_);
}

template <class Gen, class Phen>
double Population<Gen, Phen>::GetFitness(int i) const {
  return gen_eval_.GetFitness(genes_[i]);
}

template <class Gen, class Phen>
void Population<Gen, Phen>::AddGenotypes(std::vector<Gen> genes) {
  genes_.insert(genes_.end(), genes.begin(), genes.end());
  gen_eval_.Update(genes_);
}

template <class Gen, class Phen>
void Population<Gen, Phen>::SetGenotypes(std::vector<Gen> genes) {
  genes_ = genes;
  gen_eval_.Update(genes_);
}

template <class Gen, class Phen>
void Population<Gen, Phen>::SetFitnessCalculator(
    std::unique_ptr<FitnessCalculator<Phen>> fit_calc) {
  gen_eval_.SetFitnessCalculator(std::move(fit_calc));
}

}  // namespace genericga
#endif  // _GENERICGA_POPULATION_H_
