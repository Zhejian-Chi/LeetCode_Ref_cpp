//
//  _213_SearchInRotatedSortedArray.cpp
//  LeetCode
//
//  Created by chizhejian on 9/30/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//
/*
 旋转一个排好序到数组（无重复元素）后，查找某个元素
 */
#include "_213_SearchInRotatedSortedArray.hpp"


int SearchInRotated::searchInRotated(const std::vector<int> &nums, int target) {
    int first = 0;
    int last = (int)nums.size();
    while (first != last) {
        const int middle = first + (last-first)/2;
//        const int middle = (first+last)/2;
        if(nums[middle] == target)
            return middle;
        if(nums[first] <= nums[middle]) {
            if (nums[first] <= target && target < nums[middle]) {
                //大前提：中间元素不小于第一个元素。
                //如果目标元素不小于第一个元素且小于中间元素，那么目标值在前半段
                last = middle;
            } else
                //反之则在后半段
                first = middle + 1;
        } else {
            if (nums[middle] < target && target <= nums[last-1]) {
                //大前提：中间元素小于第一个元素。
                //目标值大于中间元素且不小于倒数第二个元素，则目标值在后半段
                first = middle + 1;
            } else
                //反之则在前半段
                last = middle;
        }
    }
    return -1;
}

