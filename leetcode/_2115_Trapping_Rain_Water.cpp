//
//  _2115_Trapping_Rain_Water.cpp
//  LeetCode
//
//  Created by chizhejian on 11/22/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <functional>
#include <string>
//#include <unordered_map>
//#include <algorithm>
//#include <cstdlib>

/*
 问题：给定n个非负整数代表坐标上正方形的个数，这些正方形的空缺处形成的空间用于捕获雨水，能捕获多少，假设正方形面积为1
 例如：
 ｛0，1，0，2，1，0，1，3，2，1，2，1｝，返回6
 
 求解：
 将正方形看成柱子，单独看每个位置柱子，能接雨水量是：
 第一个柱子为0，能接0雨水，第二个柱子为1，能接0雨水，第三个柱子为0，能接1雨水。。。
 总结规律：当前位置左边最高的数与右边最高的数的最小值减去当前位置的数。
 所以，对于每个位置，只要分别考虑其左边最高的柱子和右边最高的柱子即可，然后结合两个结果，取小的一个（木桶原理），最后再扣除当前柱子的高度。
 */

class TrappingRain {
public:
    int trappingRain(const std::vector<int> &nums)
    {
        const int n = nums.size();
        int *max_left = new int[n]();
        int *max_right = new int[n]();
        
        for (int i=1; i<n; i++) {
            max_left[i] = std::max(max_left[i-1], nums[i-1]);//从左往右扫描，对于每个柱子，找到他左边的最大值
            max_right[n-i-1] = std::max(max_right[n-i], nums[n-i]);//从右往左扫描，找到他右边的最大值
        }
        
        int sum = 0;
        for (int i=0; i<n; i++) {
            int height = std::min(max_left[i], max_right[i]);//找两个中较小的一个得到雨水高度（木桶原理）
            if (height > nums[i]) {
                sum += height - nums[i];//雨水高度扣除当前位置上的柱子
            }
        }
        
        delete []max_right;
        max_right = nullptr;
        delete []max_left;
        max_left = nullptr;
        return sum;
        
    }
    
    //
    int trappintRain_ver2(const std::vector<int> &nums)
    {
        const int n = nums.size();
        int maxNum = 0;
        for (int i=0; i<n; i++) {
            if (nums[i]>nums[maxNum]) {
                maxNum = i;//找到最高的柱子，将数组分成两半
            }
        }
        
        int water = 0;
        for (int i=0, peak=0; i<maxNum; i++) {//最高柱子左边，从左往右扫描，不断计算第i个peak与第i＋1个peak之间的区域能收集的雨水，其中第i个peak一定低于第i＋1个peak
            if (nums[i]>peak) {
                peak = nums[i];
            } else {
                water += peak-nums[i];
            }
        }
        for (int i=n-1, top=0; i>maxNum; i--) {//最高柱子右边，同理
            if (nums[i]>top) {
                top = nums[i];
            } else {
                water += top-nums[i];
            }
        }
        return water;
    }
};
