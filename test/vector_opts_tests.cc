#include <gtest/gtest.h>

#include <vector>

#include "genericga/vector_ops.h"

namespace gatests {

class VectorOpsTest : public ::testing::Test {
public:
  VectorOpsTest() {}

protected:
  virtual void SetUp() {
    vec.push_back(4);
    vec.push_back(0);
    vec.push_back(-2);
    vec.push_back(5);
    vec.push_back(4);
    vec.push_back(1);

  }
  std::vector<int> vec;
};

TEST_F(VectorOpsTest, GetOrderingsTest) {
  auto rankings = genericga::GetOrderings(vec);
  ASSERT_EQ(1, rankings[1]);
  ASSERT_EQ(5, rankings[2]);
}

TEST_F(VectorOpsTest, GetRankingsTest) {
  auto rankings = genericga::GetRankings(vec);
  ASSERT_EQ(1, rankings[1]);
  ASSERT_EQ(0, rankings[2]);
}

TEST_F(VectorOpsTest, GetRankingsWithTiesTest) {
  auto rankings = genericga::GetRankingsWithTies(vec);
  ASSERT_DOUBLE_EQ(0, rankings[2]);
  ASSERT_DOUBLE_EQ(3.5, rankings[0]);
}

} // namespace gatests
