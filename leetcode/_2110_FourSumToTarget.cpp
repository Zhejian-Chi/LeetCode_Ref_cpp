//
//  _2110_FourSumToTarget.cpp
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
 Q: given an array S of n integers, there are 4 elements a,b,c and d in S such that a+b+c+d=target
 find all unique quadruplets in the array.
 note:
    (a,b,c,d)must be in non-descending order, that is a<=b<=c<=d
    the solution set must not contain duplicate quadruplets.
 eg:
 S = {1 0 -1 0 -2 2}, target = 0
 output: 
    (-1,0,0,1), (-2,-1,1,2), (-2,0,0,2)
 
 
 */

class FourSumToTarget {
public:
    
    // 解法1：排序，再左右夹逼，时间复杂度O（n平方），空间O（1）;
    std::vector<std::vector<int>> fourSumToTarget1(std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> result;//用vector容器存储需要返回的结果
        if (nums.size() < 4) {
            return result;
        }
        std::sort(nums.begin(), nums.end());//先排序
        
        auto last = nums.end();
        for (auto a=nums.begin(); a < std::prev(last,3); ++a) {//与219中类似，使用prev和next，prev中是3
            for (auto b=std::next(a); b < std::prev(last,2); ++b) {//这里prev中是2
                auto c = std::next(b);//开始左右夹逼
                auto d = std::prev(last);
                while (c < d) {
                    if (*a+*b+*c+*d < target) {
                        ++c;
                    } else if (*a+*b+*c+*d > target) {
                        --d;
                    } else {
                        result.push_back({*a,*b,*c,*d});
                        ++c;
                        --d;
                    }
                }
            }
        }
        std::sort(result.begin(), result.end());//因为题目要求结果不能有重复的，先排序
        result.erase(std::unique(result.begin(), result.end()), result.end());//然后再使用unique函数删除序列中相邻的重复结果（只保留一个），一般使用前需要将序列进行排序。但是unique函数并非真正删除重复元素，它返回一个迭代器，指向的是去重后容器中不重复序列的最后一个元素的下一个位置。所以这再用了erase方法删除了多余的元素。
        return result;
    }
    
    // 解法2:用一个hashmap先缓存两个数的和。时间复杂度，平均O（n平方），最坏O（n四次方），空间O（n平方）
    // map缓存
    std::vector<std::vector<int>> fourSumToTarget2(std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> result;//用vector容器存储需要返回的结果
        if (nums.size() < 4) {
            return result;
        }
        std::sort(nums.begin(), nums.end());//先排序
        
        std::unordered_map<int, std::vector<std::pair<int, int>>> cache;//创建一个hashmap存储前两个数的和，并且以和为key，以它们的笛卡尔积为value，通过pair存储
        for (size_t a; a < nums.size(); ++a) {
            for (size_t b=a+1; b<nums.size(); ++b) {
                cache[nums[a]+nums[b]].push_back(std::pair<int, int>(a,b));
            }
        }
        
        for (int c = 0; c < nums.size(); ++c) {
            for (size_t d=c+1; d<nums.size(); ++d) {
                const int key = target - nums[c] - nums[d];
                if (cache.find(key) == cache.end()) { //没找到，继续循环
                    continue;
                }
                
                const auto& vec = cache[key];
                for (size_t k = 0; k<vec.size(); ++k) {
                    if (c <= vec[k].second) {//要满足a<=b<=c<=d，因为d一定比c大，a一定小于b，所以判断是否b<=c
                        continue;
                    }
                    result.push_back({nums[vec[k].first], nums[vec[k].second], nums[c], nums[d]});
                }
            }
        }
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }
    
    // 解法3:用一个hashmap先缓存两个数的和。时间复杂度，平均O（n平方），空间O（n平方）
    // multimap
    std::vector<std::vector<int>> fourSumToTarget3(std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> result;//用vector容器存储需要返回的结果
        if (nums.size() < 4) {
            return result;
        }
        std::sort(nums.begin(), nums.end());//先排序
        
        std::unordered_multimap<int, std::pair<int, int>> cache;
        for (int i; i+1 < nums.size(); ++i) {
            for (int j=i+1; j < nums.size(); ++j) {
                cache.insert(std::make_pair(nums[i]+nums[j], std::make_pair(i, j)));
            }
        }
        
        for (auto i=cache.begin(); i != cache.end(); ++i) {
            int x = target - i->first;
            auto range = cache.equal_range(x);
            for (auto j = range.first; j != range.second; ++j) {
                auto a = i->second.first;
                auto b = i->second.second;
                auto c = j->second.first;
                auto d = j->second.second;
                if (a != c && a != d && b != c && b != d) {
                    std::vector<int> vec = {nums[a], nums[b], nums[c], nums[d]};
                    std::sort(vec.begin(), vec.end());
                    result.push_back(vec);
                }
            }
        }
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }
};



