//
//  211_RemoveDuplicate.cpp
//  LeetCode
//
//  Created by chizhejian on 9/23/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include "211_RemoveDuplicate.hpp"
#include <vector>
#include <algorithm>
//#include <>

int SolutionOfRDfromSort::removeDupicates(std::vector<int>& nums) {
    //  Remove Duplicates from Sroted Array
    // time O(n), space O(1)
        if (nums.empty()) {
            return 0;
        }
        int index = 0;
        for (int i=1; i< nums.size(); i++) {
            if (nums[index] != nums[i]) {
                nums[++index] = nums[i];
            }
        }
        return index + 1;
}

int SolutionOfRDfromSort::removeDupicates1(std::vector<int>& nums) {
    // use STL, unique function
    // unique函数功能是元素去重。“删除”序列中所有相邻的重复元素（只保留一个）。
    // distance（first，last）函数计算first与last之间元素个数
    return std::distance(nums.begin(), std::unique(nums.begin(), nums.end()));
}

/*
 unique 函数完全等价于下面这个函数
it unique(it first, it last) {
    if(first == last)
        return last;
    
    it result = first;
    while (++first != last) {
        if(!(*result == *first)) {
            *(++result) = *first;
        }
    }
    result ++result;
}
 */
