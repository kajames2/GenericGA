#ifndef _GA_STRATEGY_H_
#define _GA_STRATEGY_H_

#include "fitness_calculator.h"
#include "phenotype_converter.h"
#include <utility>

namespace genericga {
template <class Gen, class Phen> struct GAStrategy {
public:
  GAStrategy(Gen genotype);
  GAStrategy(Gen genotype, PhenotypeConverter<Gen, Phen> *phen_conv,
             FitnessCalculator<Phen> *fitness_calc);
  void SetPhenotypeConverter(PhenotypeConverter<Gen, Phen> *phen_conv);
  void SetFitnessCalculator(FitnessCalculator<Phen> *fitness_calc);
  double GetFitness() const;
  Phen GetPhenotype() const;
  Gen GetGenotype() const;
  void SetGenotype(const Gen &gen);
  bool operator==(const GAStrategy &other) const;
  bool operator!=(const GAStrategy &other) const;
  bool operator<(const GAStrategy &other) const;
  bool operator<=(const GAStrategy &other) const;
  bool operator>(const GAStrategy &other) const;
  bool operator>=(const GAStrategy &other) const;
  
private:
  Gen genotype_;
  Phen mutable phenotype_;
  double mutable fitness_;
  FitnessCalculator<Phen> *fitness_calc_;
  PhenotypeConverter<Gen, Phen> *phen_conv_;
  bool mutable has_phenotype_;
  bool mutable has_fitness_;

  void CalculatePhenotype() const;
  void CalculateFitness() const;
};

template <class Gen, class Phen>
GAStrategy<Gen, Phen>::GAStrategy(Gen genotype)
    : genotype_(genotype), has_phenotype_(false), has_fitness_(false) {
  SetFitnessCalculator(nullptr);
  SetPhenotypeConverter(nullptr);
}

template <class Gen, class Phen>
GAStrategy<Gen, Phen>::GAStrategy(Gen genotype,
                                  PhenotypeConverter<Gen, Phen> *phen_conv,
                                  FitnessCalculator<Phen> *fitness_calc)
    : genotype_(genotype), has_phenotype_(false), has_fitness_(false) {
  SetFitnessCalculator(fitness_calc);
  SetPhenotypeConverter(phen_conv);
}

template <class Gen, class Phen>
void GAStrategy<Gen, Phen>::SetPhenotypeConverter(
    PhenotypeConverter<Gen, Phen> *phen_conv) {
  phen_conv_ = phen_conv;
  has_fitness_ = false;
  has_phenotype_ = false;
}

template <class Gen, class Phen>
void GAStrategy<Gen, Phen>::SetFitnessCalculator(
    FitnessCalculator<Phen> *fitness_calc) {
  fitness_calc_ = fitness_calc;
  has_fitness_ = false;
}

template <class Gen, class Phen>
double GAStrategy<Gen, Phen>::GetFitness() const {
  if (!has_fitness_) {
    CalculateFitness();
  }
  return fitness_;
}

template <class Gen, class Phen>
Phen GAStrategy<Gen, Phen>::GetPhenotype() const {
  if (!has_phenotype_) {
    CalculatePhenotype();
  }
  return phenotype_;
}

template <class Gen, class Phen>
bool GAStrategy<Gen, Phen>::operator<(const GAStrategy &other) const {
  return genotype_ < other.genotype_;
}

template <class Gen, class Phen>
bool GAStrategy<Gen, Phen>::operator<=(const GAStrategy &other) const {
  return genotype_ <= other.genotype_;
}

template <class Gen, class Phen>
bool GAStrategy<Gen, Phen>::operator>(const GAStrategy &other) const {
  return genotype_ > other.genotype_;
}

template <class Gen, class Phen>
bool GAStrategy<Gen, Phen>::operator>=(const GAStrategy &other) const {
  return genotype_ >= other.genotype_;
}

template <class Gen, class Phen>
bool GAStrategy<Gen, Phen>::operator==(const GAStrategy &other) const {
  return genotype_ == other.genotype_;
}

template <class Gen, class Phen>
bool GAStrategy<Gen, Phen>::operator!=(const GAStrategy &other) const {
  return genotype_ != other.genotype_;
}

template <class Gen, class Phen>
Gen GAStrategy<Gen, Phen>::GetGenotype() const {
  return genotype_;
}

template <class Gen, class Phen>
void GAStrategy<Gen, Phen>::SetGenotype(const Gen &gen) {
  genotype_ = gen;
  has_phenotype_ = false;
  has_fitness_ = false;
}

template <class Gen, class Phen>
void GAStrategy<Gen, Phen>::CalculatePhenotype() const {
  phenotype_ = phen_conv_->Convert(genotype_);
}

template <class Gen, class Phen>
void GAStrategy<Gen, Phen>::CalculateFitness() const {
  if (!has_phenotype_) {
    CalculatePhenotype();
  }
  fitness_ = fitness_calc_->CalculateFitness(phenotype_);
}

} // namespace genericga

#endif // _GA_STRATEGY_H_
