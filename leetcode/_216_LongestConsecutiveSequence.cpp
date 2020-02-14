//
//  _216_LongestConsecutiveSequence.cpp
//  LeetCode
//
//  Created by chizhejian on 10/30/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

/*
 找一个数组中元素能组成的最长元素连续序列，例如［100, 4, 200, 1, 3, 2]，最长元素连续序列为［1，2，3，4］，
 长度为4。要求时间复杂度为O（n）。
 
 分析：时间复杂度为O（n），数组又是无序的，可以采用hash表。用一个hash表unordered_map<int, bool> used
      记录每个元素是否使用，对每个元素为中心，往左右扩展，直到不连续为止，记录下最长的长度。
 */
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

class LongestConsecutiveSequence {
public:
    int longestConsecutive(const std::vector<int> &nums) {
        std::unordered_map<int, bool> used; // 与map类似，是一个key－value对
        int longest = 0;
        
        // 初始化hash
        for(auto i: nums)
            used[i] = false;
        for(auto i: nums) {
            if(used[i])
                continue;
            
            int length = 1;
            used[i] = true;
            for (int j=i+1; used.find(j)!=used.end(); j++) {// 找当前数的后一个，找到则长度加1，否则结束循环
                used[j] = true;
                length++;
            }
            for (int j=i-1; used.find(j)!=used.end(); j--) {// 找当前数的前一个，找到则长度加1，否则结束循环
                used[j] = true;
                length++;
            }
            longest = std::max(longest, length);
        }
        return longest;
    }
    
    /*
    int longestConsecutiveVer2(const std::vector<int> &nums) {
        std::unordered_map<int, int> map;
        int size = nums.size();
        int l = 1;
        for (int i=0; i<size; i++) {
            if(map.find(nums[i]) != map.end())
                continue;
            map[nums[i]] = 1;
            if (map.find(nums[i]-1) != map.end()) {
                l = std::max(l, mergeCluster(map, nums[i]-1, nums[i]));
            }
            if (map.find(nums[i]+1) != map.end()) {
                l = std::max(l, mergeCluster(map, nums[i], nums[i]+1));
            }
        }
        return size = 0 ? 0 : l;
    }
    
private:
    int mergeCluster(std::unordered_map<int, int> &map, int left, int right) {
        int upper = right + map[right] - 1;
        int lower = left - map[left] + 1;
        int length = upper - lower + 1;
        map[upper] = length;
        map[lower] = length;
        return length;
    }
     */
};
