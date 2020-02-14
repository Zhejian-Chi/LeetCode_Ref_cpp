//
//  _214_SearchRotatedSortArray.cpp
//  LeetCode
//
//  Created by chizhejian on 10/15/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

//#include <stdio.h>
#include <vector>
#include <algorithm>

/*
 旋转一个递增数组，与213中不同，数组中存在重复数字，找一个数是否在此数组中。
 解法与213类似，也是通过二分查找，但是注意：
 区间[l,m]中，若a[m]>=a[l]时不能确定递增，将其拆分成两个条件：
 1. 若a[m]>a[l]，则区间一定递增
 2. 若a[m]=a[l]，那就l＋＋，往下看一步即可
 */
class SearchInRotatedSortedArray {
public:
    int search(std::vector<int> &nums, int target)
    {
        int first = 0;
        int last = (int)nums.size(); // 注意last的值是数组长度
        while (first != last)
        {
            const int middle = (first + last) / 2;
            if (nums[middle] == target) {
                return middle;
            }
            if (nums[middle] > nums[first]) { // 中间值大于第一个值
                // 目标值满足 first<＝ target <＝middle，即目标值在前半段，令last＝middle
                if (nums[middle] > target && target >= nums[first]) {
                    last = middle;
                } else {
                    first = middle + 1;
                }
            } else if (nums[middle] < nums[first]) { // 中间值小于第一个值
                if (nums[middle] < target && target <= nums[last-1])
                    first = middle + 1;
                else
                    last = middle;
            } else {
                first++; //跳过重复一次
            }
        }
        return -1; //没有找到，返回－1
    }
};


