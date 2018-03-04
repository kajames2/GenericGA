#ifndef _GENERICGA_VECTOR_OPS_H_
#define _GENERICGA_VECTOR_OPS_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

namespace genericga {
template <class T>
std::vector<int> GetOrderings(const std::vector<T> &vec);
template <class T>
std::vector<int> GetRankings(const std::vector<T> &vec);
template <class T>
std::vector<double> GetRankingsWithTies(const std::vector<T> &vec);

template <class T>
std::vector<int> GetOrderings(const std::vector<T> &vec) {
  std::vector<int> indices(vec.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(),
            [&vec](size_t i1, size_t i2) { return vec[i1] < vec[i2]; });
  return indices;
}

template <class T>
std::vector<int> GetRankings(const std::vector<T> &vec) {
  return GetOrderings(GetOrderings(vec));
}

// Ties get the average of the ranks at that value. Ex. values of 5,6,5,1,5 have
// ranks: 2,4,2,0,2 (2 = mean(1,2,3)). Decimal ranks possible.
template <class T>
std::vector<double> GetRankingsWithTies(const std::vector<T> &vec) {
  std::vector<double> out_vec(vec.size());
  // 1st element is index of smallest fitness, 2nd is of next smallest, etc.
  auto ordering = GetOrderings(vec);
  int low_count = 0;
  int count = 0;
  int n_equal = 0;
  for (auto it = ordering.begin(); it != ordering.end(); ++it) {
    count++;
    n_equal++;
    if (it + 1 == ordering.end() || vec[*(it + 1)] != vec[*it]) {
      for (int i = n_equal - 1; i >= 0; --i) {
        out_vec[*(it - i)] = (count + low_count - 1) / 2.0;
      }
      low_count = count;
      n_equal = 0;
    }
  }
  return out_vec;
}

}  // namespace genericga

#endif  // _GENERICGA_VECTOR_OPS_H_
