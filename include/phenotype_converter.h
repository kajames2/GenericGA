#ifndef _PHENOTYPE_CONVERTER_H_
#define _PHENOTYPE_CONVERTER_H_

namespace genericga {

template <class Gen, class Phen>
class PhenotypeConverter {
 public:
  virtual Phen Convert(const Gen &genotype);
};

}  // namespace genericga

#endif  // _PHENOTYPE_CONVERTER_H_
