//
//  _217_TwoSumReturnIndex.cpp
//  LeetCode
//
//  Created by chizhejian on 11/2/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <unordered_map>

/*
 问题：给一个整数数组，给一个目标值，找出数组中两个数的和等于目标值，返回他们的位置，并且index1要小于index2
 解法：创建一个hash表，存储每个数对应的下标，复杂度O（n）
 */

class TwoSum {
public:
    std::vector<int> towSum(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> mapping;
        std::vector<int> result; //用一个vector容器存储两个下标，最后返回
        for (int i=0; i<nums.size(); i++) {
            mapping[nums[i]] = i;
        }
        for (int i=0; i<nums.size(); i++) {
            const int gap = target - nums[i]; //求另一个数
            if (mapping.find(gap) != mapping.end() && mapping[gap] > i) {//找出另一个数的下标
                result.push_back(i+1);
                result.push_back(mapping[gap]+1);
                break;
            }
        }
        return result;
    }
};
