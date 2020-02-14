//
//  _2111_RemoveElement.cpp
//  LeetCode
//
//  Created by chizhejian on 11/19/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <unordered_map>
//#include <algorithm>
#include <cstdlib>
/*
 给定一个序列和一个数，删除序列里与给定的数相同的数，然后返回序列的长度。序列顺序可以改变，也不用管超出新长度外的内容。
 与211中一样，可以直接顺序比较，用两个指针（下标）标记，其中一个找目标值，另一个用于替换。
 */

class RemoveElemets {
public:
    int removeElement(std::vector<int>& nums, int target)
    {
        int index = 0;
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] != target) {
                nums[index++] = nums[i];
            }
        }
        return index;
    }
    
    //remove函数删除第三个参数相等的元素，从前面两个参数给定的范围中，本质上是用后面的元素替换了前面的元素，返回一个指向新序列的最后一个元素的后一个位置的迭代器。
    int removeElement2(std::vector<int>& nums, int target)
    {
        return std::distance(nums.begin(), remove(nums.begin(),nums.end(),target));
    }
};
