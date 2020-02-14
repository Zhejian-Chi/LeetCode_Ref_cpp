//
//  _2112_NextPermutation.cpp
//  LeetCode
//
//  Created by chizhejian on 11/19/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <functional>
//#include <unordered_map>
//#include <algorithm>
//#include <cstdlib>

/*
 问题：实现当前序列的下一个排列，下一个排列是按照字典序列递增的一个排列。
      如果已经是最大的排列，则返回最小的一个排列。
 要求：不能使用额外的空间
 例子：
 1，2，3 －》 1，3，2
 3，2，1 －》 1，2，3
 1，1，5 －》 1，5，1
 
 求解算法：
 以序列｛6，8，7，4，3，2｝为例说明
 1.从右往左找到第一个不是递增的数，称为“分割数”，在序列中，‘6’将会被选为”分割数“，因为从右往左，“8，7，4，3，2”是递增的。
 2.从右往左找到第一个大于“分割数”的数字，称为”改变数“，在序列中，‘7’为”改变数“。
 3.交换“分割数”和”改变数“，那么序列变为｛7，8，6，4，3，2｝
 4.将“分割数”位置之后的所有数字组成的序列逆序，即｛8，6，4，3，2｝需要逆序。最终得到｛7，2，3，4，6，8｝
 */

class NextPermutation {
public:
    void nextPermutation(std::vector<int> &nums)
    {
        auto last = std::prev(nums.end());//注意：prev(nums.end())与prev(nums.end()，1)是一样的
        auto last1 = std::prev(nums.end(),2);
        while (*last1 > *last) {
            --last;
            --last1;
        }
        auto changeNumber = std::prev(nums.end());
        while (*changeNumber < *last1) {
            --changeNumber;
        }
        std::swap(*last1, *changeNumber);
        std::reverse(std::next(last1), nums.end());
    }
};

// from LeeCode
class Soluiton {
public:
    void nextPermutation(std::vector<int> &nums)
    {
        next_permutation(nums.begin(), nums.end());
    }
    
    template<typename BidiIt>
    bool next_permutation(BidiIt first, BidiIt last)
    {
        // get a reversed range to simplify reversed traversal
        const auto rfirst = std::reverse_iterator<BidiIt>(last);
        const auto rlast = std::reverse_iterator<BidiIt>(first);
        
        // begin from the second last element to the first element
        auto pivot = std::next(rfirst);
        
        // find 'pivot', which is the first element that is no less than its successor.
        // 'prev' is used since 'pivort' is a 'reversed_iterator'.
        while (pivot != rlast && *pivot >= *std::prev(pivot)) {
            ++pivot;
        }
        
        // no such element found, current sequence is already the largest permutation,
        // then rearrange to the first permutation and return false.
        if (pivot == rlast) {
            std::reverse(rfirst, rlast);
            return false;
        }
        
        // scan from right to left, find the first element that is greater than 'pivot'
        auto change = std::find_if(rfirst, pivot, std::bind1st(std::less<int>(), *pivot));
        
        std::swap(*change, *pivot);
        std::reverse(rfirst, pivot);
        return true;
    }
};
