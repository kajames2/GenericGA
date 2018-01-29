#ifndef _FITNESS_CALCULATOR_H_
#define _FITNESS_CALCULATOR_H_

namespace genericga {

template <class Phen> class FitnessCalculator {
public:
  virtual double CalculateFitness(const Phen &phenotype);
};
} // namespace genericga

#endif // _FITNESS_CALCULATOR_H_
