#ifndef _SAMPLE_PHENOTYPE_CONVERTER_H_
#define _SAMPLE_PHENOTYPE_CONVERTER_H_

#include "genericga/phenotype_converter.h"

namespace gatests {

class SamplePhenotypeConverter
    : public genericga::PhenotypeConverter<int, int> {
public:
  explicit SamplePhenotypeConverter(int n) : n_(n) {}
  int Convert(const int &genotype) const override { return n_ - genotype * genotype; }

private:
  int n_;
};

} // namespace gatests

#endif // _SAMPLE_PHENOTYPE_CONVERTER_H_
