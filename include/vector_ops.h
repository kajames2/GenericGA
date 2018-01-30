#ifndef _VECTOR_OPS_H_
#define _VECTOR_OPS_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

namespace genericga {
template <class T> std::vector<int> GetOrderings(const std::vector<T> &vec);
template <class T> std::vector<int> GetRankings(const std::vector<T> &vec);
template <class T>
std::vector<double> GetRankingsWithTies(const std::vector<T> &vec);
template <class T>
std::vector<double> GetRankingsWithTies(const std::vector<T> &vec,
                                        const std::vector<int> &counts);
template <class T> std::map<T, int> VectorToCounts(const std::vector<T> &vec);
template <class T>
std::map<T, int> VectorToCounts(const std::vector<T> &vec,
                                const std::vector<int> &counts);
template <class T>
std::vector<T> CountsToVector(const std::map<T, int> &value_counts);
template <class T>
void AddFrequencies(std::map<T, int> *map1, std::map<T, int> *map2);

template <class T> std::vector<int> GetOrderings(const std::vector<T> &vec) {
  std::vector<int> indices(vec.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(),
            [&vec](size_t i1, size_t i2) { return vec[i1] < vec[i2]; });
  return indices;
}

template <class T> std::vector<int> GetRankings(const std::vector<T> &vec) {
  return GetOrderings(GetOrderings(vec));
}

template <class T>
std::vector<double> GetRankingsWithTies(const std::vector<T> &vec) {
  GetRankingsWithTies(vec, std::vector<int>(vec.size(), 1));
}

// Ties get the average of the ranks at that value. Ex. values of 5,6,5,1,5 have
// ranks: 2,4,2,0,2 (2 = mean(1,2,3)). Decimal ranks possible.
template <class T>
std::vector<double> GetRankingsWithTies(const std::vector<T> &vec,
                                        const std::vector<int> &counts) {
  std::vector<double> out_vec(vec.size(), 0);
  // 1st element is index of smallest fitness, 2nd is of next smallest, etc.
  auto ordering = GetOrderings(vec);
  int low_count = 0;
  int count = 0;
  int n_equal = 0;
  for (auto it = ordering.begin(); it != ordering.end(); ++it) {
    count += counts[*it];
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

template <class T> std::map<T, int> VectorToCounts(const std::vector<T> &vec) {
  return VectorToCounts(vec, std::vector<int>(vec.size(), 1));
}

template <class T>
std::map<T, int> VectorToCounts(const std::vector<T> &vec,
                                const std::vector<int> &counts) {
  std::map<T, int> index_counts;
  auto orderings = GetOrderings(vec);
  int cur_count = 0;
  for (int i = 0; i < vec.size(); ++i) {
    cur_count += counts[orderings[i]];
    if (i + 1 == vec.size() || vec[orderings[i + 1]] != vec[orderings[i]]) {
      index_counts.emplace(vec[orderings[i]], cur_count);
      cur_count = 0;
    }
  }
  return index_counts;
}

template <class T>
std::vector<T> CountsToVector(const std::map<T, int> &value_counts) {
  std::vector<T> values;
  for (auto pair : value_counts) {
    std::vector<T> value_copies(pair.second, pair.first);
    values.insert(values.end(), value_copies.begin(), value_copies.end());
  }
  return values;
}

template <class T>
void AddFrequencies(std::map<T, int> *map1, std::map<T, int> *map2) {
  for (auto it = map2->begin(); it != map2->end(); ++it) {
    if (map1->find(it->first) != map1->end()) {
      (*map1)[it->first] += it->second;
    } else {
      map1->emplace(std::move(*it));
    }
  }
}

} // namespace genericga

#endif // _VECTOR_OPS_H_
