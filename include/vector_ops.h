#ifndef _VECTOR_OPS_H_
#define _VECTOR_OPS_H_

#include <vector>
#include <map>
#include <numeric>

namespace genericga {
template <class T> std::vector<int> GetRankings(const std::vector<T>& vec);
template <class T> std::map<T, int> VectorToCounts(const std::vector<T>& vec);
template <class T> std::map<T, int> VectorToCounts(const std::vector<T>& vec, const std::vector<int>& counts);
template <class T> std::vector<T> CountsToVector(const std::map<T, int>& value_counts);
    
template <class T> std::vector<int> GetRankings(const std::vector<T>& vec) {
  std::vector<int> indices(vec.size());
  std::iota(indices.begin(), indices.end(), 0);
  sort(indices.begin(), indices.end(),
       [&vec](size_t i1, size_t i2) { return vec[i1] < vec[i2]; });
  return indices;
}

template <class T>
std::map<T, int> VectorToCounts(const std::vector<T>& vec) {
  std::map<T, int> index_counts;
  auto rankings = GetRankings(vec);
  int cur_count = 0;
  for(int i = 0; i < vec.size(); ++i) {
    cur_count += 1;
    if(i + 1 == vec.size() || vec[rankings[i + 1]] != vec[rankings[i]]) {
      index_counts.emplace(vec[rankings[i]], cur_count);
      cur_count = 0;
    }
  }
  return index_counts;
}

template <class T>
std::map<T, int> VectorToCounts(const std::vector<T>& vec, const std::vector<int>& counts) {
  std::map<T, int> index_counts;
  auto rankings = GetRankings(vec);
  int cur_count = 0;
  for(int i = 0; i < vec.size(); ++i) {
    cur_count += counts[rankings[i]];
    if(i + 1 == vec.size() || vec[rankings[i + 1]] != vec[rankings[i]]) {
      index_counts.emplace(vec[rankings[i]], cur_count);
      cur_count = 0;
    }
  }
  return index_counts;
}

template <class T>
std::vector<T> CountsToVector(const std::map<T, int>& value_counts) {
    std::vector<T> values;
    for (auto pair : value_counts) {
      std::vector<int> value_copies(pair.second, pair.first);
      values.insert(values.end(), value_copies.begin(), value_copies.end());
    }
    return values;
  }


}  // namespace genericga

#endif  // _VECTOR_OPS_H_
