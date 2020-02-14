//
//  _2117-2118_PlusOne_ClimbStairs.cpp
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
#include <cmath>

/*
 问题1：将一个数字的每一位存入一个数组，在末位加1
 
 求解：需要考虑进位问题，若最后一位不是9，则直接加1后返回；否则要考虑进位。
 */

class PlusOne {
public:
    //模拟加法的过程
    std::vector<int> plusOne(std::vector<int> &nums)
    {//这里也可以用字符数组代替，只是运算时得加上或减去‘0’，完成数字与字符的转换
        const int n = nums.size();
        bool isOverflow = false;//最高位是否发生进位
        int nTakeover = 0;//统计进位
        for (int i=n-1; i>=0; --i) {
            int nSum = nums[i] + nTakeover;//某一位与进位值相加
            if (i == n-1) {
                nSum++;//若是最后一位，先加1
            }
            if (nSum >= 10) {//判断是否发生进位
                if (i == 0) {
                    isOverflow = true;
                }
                nSum -= 10;
                nTakeover = 1;
                nums[i] = nSum;
            } else {
                nums[i] = nSum;//没有进位，结束循环
                break;
            }
        }
        if (isOverflow) {
            nums.insert(nums.begin(), 1);//最高位发生进位，直接在开始处插入1
        }
        return nums;
    }
    
    
    // LeeCode simulate adding
    std::vector<int> plusone1(std::vector<int> &digits) {
        add1(digits,1);
        return digits;
    }
    
private:
    //digit在0-9之间
    void add1(std::vector<int> &digits, int digit){
        int c = digit; //进位
        std::for_each(digits.rbegin(), digits.rend(), [&c](int &d){ //use Lambda expression, rbegin() and rend() are the reverse iterator.
            d += c;
            c = d/10;
            d %= 10;
        });
        if(c > 0)
            digits.insert(digits.begin(), 1);
    }
    void add2(std::vector<int> &digits, int digit){
        int c = digit; //进位
        for (auto it=digits.rbegin(); it != digits.rend(); ++it) {
            *it += c;
            c = *it/10;
            *it %= 10;
        }
        if(c > 0)
            digits.insert(digits.begin(), 1);
    }
};





//2.1.18 斐波纳契数列
class ClimbStairs {
public:
    int climbStairs(int n)
    {
        int prev = 0;
        int cur = 1;
        for (int i=1; i<n; ++i) {
            int tmp = cur;
            cur += prev;
            prev = tmp;
        }
        return cur;
    }
    
    // use math fomular
    int climbStairs_ver2(int n)
    {
        const double s = sqrt(5);
        return std::floor((pow((1+s)/2, n+1)+pow((1-s)/2, n+1))/s+0.5);
    }
};
