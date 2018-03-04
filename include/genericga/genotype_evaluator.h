#ifndef _GENERICGA_GENOTYPE_EVALUATOR_H_
#define _GENERICGA_GENOTYPE_EVALUATOR_H_

#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include "genericga/fitness_calculator.h"
#include "genericga/ga_strategy.h"
#include "genericga/phenotype_converter.h"

namespace genericga {

template <class Gen, class Phen>
class GenotypeEvaluator {
 public:
  GenotypeEvaluator(std::unique_ptr<const PhenotypeConverter<Gen, Phen>>);
  void Update(const std::vector<Gen>& genotypes);
  void SetFitnessCalculator(
      std::unique_ptr<const FitnessCalculator<Phen>> fit_calc);

  std::vector<double> GetFitnesses(const std::vector<Gen>& genes) const;
  const GAStrategy<Phen>& GetStrategy(const Gen& gene) const;
  double GetFitness(const Gen& gene) const;

 private:
  GAStrategy<Phen> GenerateStrategy(const Gen& gene) const;

  std::map<Gen, GAStrategy<Phen>> strats_;
  std::unique_ptr<const FitnessCalculator<Phen>> fit_calc_;
  std::unique_ptr<const PhenotypeConverter<Gen, Phen>> phen_conv_;
};

template <class Gen, class Phen>
GenotypeEvaluator<Gen, Phen>::GenotypeEvaluator(
    std::unique_ptr<const PhenotypeConverter<Gen, Phen>> phen_conv)
    : phen_conv_(std::move(phen_conv)), fit_calc_(nullptr) {}

// Parallelize later.
template <class Gen, class Phen>
void GenotypeEvaluator<Gen, Phen>::Update(const std::vector<Gen>& genes) {
  std::set<Gen> uniques(genes.begin(), genes.end());
  std::map<Gen, GAStrategy<Phen>> new_strats;
  for (auto& gene : uniques) {
    auto el = strats_.find(gene);
    if (el == strats_.end()) {
      new_strats.emplace(gene, GenerateStrategy(gene));
    } else {
      new_strats.emplace(*el);
    }
  }
  strats_ = new_strats;
}

template <class Gen, class Phen>
GAStrategy<Phen> GenotypeEvaluator<Gen, Phen>::GenerateStrategy(
    const Gen& gene) const {
  Phen phen = phen_conv_->Convert(gene);
  return fit_calc_ ? GAStrategy<Phen>{phen, fit_calc_->CalculateFitness(phen)}
                   : GAStrategy<Phen>{phen};
}

template <class Gen, class Phen>
void GenotypeEvaluator<Gen, Phen>::SetFitnessCalculator(
    std::unique_ptr<const FitnessCalculator<Phen>> fit_calc) {
  fit_calc_ = std::move(fit_calc);
  for (auto& pair : strats_) {
    pair.second.fitness = fit_calc_->CalculateFitness(pair.second.phenotype);
  }
}

template <class Gen, class Phen>
std::vector<double> GenotypeEvaluator<Gen, Phen>::GetFitnesses(
    const std::vector<Gen>& genes) const {
  std::vector<double> fits(genes.size());
  for (int i = 0; i < genes.size(); ++i) {
    fits[i] = strats_.at(genes[i]).fitness;
  }
  return fits;
}

template <class Gen, class Phen>
const GAStrategy<Phen>& GenotypeEvaluator<Gen, Phen>::GetStrategy(
    const Gen& gene) const {
  return strats_.at(gene);
}

template <class Gen, class Phen>
double GenotypeEvaluator<Gen, Phen>::GetFitness(const Gen& gene) const {
  return strats_.at(gene).fitness;
}

}  // namespace genericga
#endif  // _GENERICGA_GENOTYPE_EVALUATOR_H_
