#ifndef _GENERICGA_FITNESS_CALCULATOR_H_
#define _GENERICGA_FITNESS_CALCULATOR_H_

namespace genericga {

template <class Phen>
class FitnessCalculator {
 public:
  virtual double CalculateFitness(const Phen &phenotype) const;
};
}  // namespace genericga

#endif  // _GENERICGA_FITNESS_CALCULATOR_H_
