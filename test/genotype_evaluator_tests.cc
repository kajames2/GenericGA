#include <gtest/gtest.h>

#include <vector>

#include "genericga/fitness_calculator.h"
#include "genericga/genotype_evaluator.h"
#include "sample_fitness_calculator.h"
#include "sample_phenotype_converter.h"

namespace gatests {

class GenotypeEvaluatorTest : public ::testing::Test {
 public:
  GenotypeEvaluatorTest() : gene_eval(std::make_unique<SamplePhenotypeConverter>(100)) {}

 protected:
  virtual void SetUp() {
    fit_calc = std::make_unique<SampleFitnessCalculator>(5);
    genes = std::vector<int>{1, 4, 9, 1, 3, 3, 1};
    genes2 = std::vector<int>{1, 4, 9, 1, 8};
  }
  std::vector<int> genes, genes2;
  std::unique_ptr<const SampleFitnessCalculator> fit_calc;
  genericga::GenotypeEvaluator<int, int> gene_eval;
};

TEST_F(GenotypeEvaluatorTest, UpdateWhenEmptyTest) {
  gene_eval.Update(genes);
  ASSERT_EQ(-1, gene_eval.GetFitness(3));
  ASSERT_EQ(-1, gene_eval.GetFitness(9));
  ASSERT_ANY_THROW(gene_eval.GetFitness(8));
}

TEST_F(GenotypeEvaluatorTest, UpdateAddTest) {
  gene_eval.Update(genes);
  gene_eval.Update(genes2);
  ASSERT_EQ(-1, gene_eval.GetFitness(8));
}

TEST_F(GenotypeEvaluatorTest, UpdateRemoveTest) {
  gene_eval.Update(genes);
  gene_eval.Update(genes2);
  ASSERT_ANY_THROW(gene_eval.GetFitness(3));
}

TEST_F(GenotypeEvaluatorTest, UpdateWithFitnessTest) {
  gene_eval.SetFitnessCalculator(std::move(fit_calc));
  gene_eval.Update(genes);
  ASSERT_EQ(24, gene_eval.GetFitness(9));
}

TEST_F(GenotypeEvaluatorTest, SetFitnessTest) {
  gene_eval.Update(genes);
  gene_eval.SetFitnessCalculator(std::move(fit_calc));
  ASSERT_EQ(24, gene_eval.GetFitness(9));
}

}  // namespace gatests
