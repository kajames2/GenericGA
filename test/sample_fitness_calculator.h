#ifndef _SAMPLE_FITNESS_CALCULATOR_H_
#define _SAMPLE_FITNESS_CALCULATOR_H_

#include "genericga/fitness_calculator.h"

namespace gatests {

class SampleFitnessCalculator : public genericga::FitnessCalculator<int> {
public:
  explicit SampleFitnessCalculator(int n) : n_(n) {}
  double CalculateFitness(const int &phenotype) const override {
    return phenotype + n_;
  }

private:
  int n_;
};

} // namespace gatests

#endif // _SAMPLE_FITNESS_CALCULATOR_H_
