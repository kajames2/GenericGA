#ifndef _SAMPLE_PHENOTYPE_CONVERTER_H_
#define _SAMPLE_PHENOTYPE_CONVERTER_H_

#include "phenotype_converter.h"

namespace gatests {

class SamplePhenotypeConverter
    : public genericga::PhenotypeConverter<int, int> {
  int Convert(int genotype) override { return 5 - genotype * genotype; }
}

} // namespace gatests

#endif // _SAMPLE_PHENOTYPE_CONVERTER_H_
