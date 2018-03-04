#ifndef _GENERICGA_PHENOTYPE_CONVERTER_H_
#define _GENERICGA_PHENOTYPE_CONVERTER_H_

namespace genericga {

template <class Gen, class Phen>
class PhenotypeConverter {
 public:
  virtual Phen Convert(const Gen &genotype) const;
};

}  // namespace genericga

#endif  // _GENERICGA_PHENOTYPE_CONVERTER_H_
