//
//  _219_ThreeSumClosestToTarget.cpp
//  LeetCode
//
//  Created by chizhejian on 11/3/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <unordered_map>
//#include <algorithm>
#include <cstdlib>

/*
 Q: given an array S of n integers, there are 3 elements a,b,c in S such that a+b+c is closest to a given number, target. return the sum of the three integers. you can assume that each input would have exactly one solution.
 eg:
 S = {-1 2 1 4}, target = 1
 output: 2(=-1+2+1)
 
 解法：排序，再左右夹逼，时间复杂度O（n平方），空间O（1）;
 */

class ThreeSumClosestToTarget {
public:
    int threeumClosestToTarget(std::vector<int> &nums, int target)
    {
        int result = 0;
        int min_gap = INT_MAX;
        std::sort(nums.begin(), nums.end());
        
        for (auto a=nums.begin(); a != std::prev(nums.end(), 2); ++a) { //prev返回nums.end()前2个迭代指针，例如nums＝｛1，2，3，4，5｝，那么prev(nums.end(), 2)就返回4这个位置的迭代器，也就是倒数第二个位置。
            auto b = std::next(a); //next返回a的下一个迭代指针（与prev类似）
            auto c = std::prev(nums.end());//prev返回nums.end()前一个迭代，也就是倒数第一个位置。
            
            while (b < c) {
                const int sum = *a + *b + *c;
                const int gap = abs(sum - target);
                if (gap < min_gap) {
                    min_gap = gap;
                    result = sum;
                }
                if (sum < target) { //若和小于目标值，b往后移动；反之，c往前移动
                    ++b;
                }
                else
                    --c;
            }
        }
        
        return result;
    }
};
