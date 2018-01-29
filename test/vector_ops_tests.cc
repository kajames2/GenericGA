#include "vector_ops.h"

#include <gtest/gtest.h>
#include <map>
#include <vector>

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

    vec_counts = std::vector<int>(vec.size(), 1);
    vec_counts[2] = 3;
    
    for(int i = 1; i < 5; ++i) {
      map.emplace(i, i);
    }
    
    for(int i = 7; i > 3; --i) {
      map2.emplace(i, i);
    }
  }
  std::vector<int> vec, vec_counts;
  std::map<int, int> map, map2;
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
  auto rankings = genericga::GetRankingsWithTies(vec, vec_counts);
  ASSERT_DOUBLE_EQ(1.0, rankings[2]);
  ASSERT_DOUBLE_EQ(5.5, rankings[0]);
}

TEST_F(VectorOpsTest, VectorToCountsTest) {
  auto counts = genericga::VectorToCounts(vec);
  auto it = counts.begin();
  ++it;
  ++it;
  ++it;
  ASSERT_EQ(5, counts.size());
  ASSERT_EQ(4, it->first);
  ASSERT_EQ(2, it->second);
}

TEST_F(VectorOpsTest, VectorToCounts2Test) {
  auto counts = genericga::VectorToCounts(vec, vec_counts);
  auto it = counts.begin();
  ASSERT_EQ(5, counts.size());
  ASSERT_EQ(-2, it->first);
  ASSERT_EQ(3, it->second);
}


TEST_F(VectorOpsTest, CountsToVectorTest) {
  auto expanded_vec = genericga::CountsToVector(map);
  ASSERT_EQ(10, expanded_vec.size());
  ASSERT_EQ(3, expanded_vec[4]);
}

TEST_F(VectorOpsTest, MergeCountsTest) {
  auto merged = genericga::MergeCounts(map, map2);
  auto it = merged.begin();
  ++it;
  ++it;
  ASSERT_EQ(3, it->first);
  ASSERT_EQ(3, it->second);
  ++it;
  ASSERT_EQ(4, it->first);
  ASSERT_EQ(8, it->second);
  ++it;
  ASSERT_EQ(5, it->first);
  ASSERT_EQ(5, it->second);
}

} // namespace gatests
