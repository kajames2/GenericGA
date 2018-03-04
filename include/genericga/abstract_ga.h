#ifndef _ABSTRACT_GA_H_
#define _ABSTRACT_GA_H_

void RunRound();
void RunRound(int n);
void SetPhenotypeConverter(
    std::shared_ptr<PhenotypeConverter<Gen, Phen>> phen_conv);
void SetFitnessCalculator(std::shared_ptr<FitnessCalculator<Phen>> fit_calc);

#endif  // _ABSTRACT_GA_H_
