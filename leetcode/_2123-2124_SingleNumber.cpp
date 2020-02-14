//
//  _2123-2124_SingleNumber.cpp
//  LeetCode
//
//  Created by chizhejian on 11/25/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <functional>
#include <string>
//#include <unordered_map>
#include <algorithm>
#include <numeric>
//#include <cstdlib>
//#include <cmath>

/*
 2.1.23：
 问题：一个整数数组，每个数都出现两次，但有一个只出现1次，找出那个数。线性时间，并且不用额外空间。
 求解：异或
 
 */

class SingleNumber {
public:
    int singleNum(std::vector<int> &nums)
    {
        int x=0;
        for (auto i : nums) {
            x ^= i;
        }
        return x;
    }
    
    int singleNum_ver2(std::vector<int> &nums)
    {
        return std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor<int>());
    }
};


/*
 2.1.24：
 问题：一个整数数组，每个数都出现三次，但有一个例外，找出那个数
 求解：1.一个数出现3次，那么这个数对应的二进制数中是1的位也总共出现了3次，即3的倍数。可以推广到出现n次的情况
      2.用one记录到当前处理的元素为止，二进制1出现“1次”（mod 3之后的1）的有哪些二进制位；用two记录到当前计算的变量为止，二进制1出现“2次”（mod 3之后的2）的有哪些二进制位.当one和two中的某一位同时为1时表示该二进制位上1出现了3次，此时需要清零。即用二进制模拟三进制的计算，最终one记录的是最终结果。
 */

class SingleNumber_3{
public:
    int singleNum3(std::vector<int> &nums)
    {
        const int nBits = sizeof(int)*8; //一个整数的bit数
        int count[nBits]; //统计在每一位出现1的次数
        std::fill_n(&count[0], nBits, 0);
        for (int i=0; i<nums.size(); i++) {
            for (int j=0; j<nBits; j++) {
                count[j] += (nums[i]>>j) & 1; //求一个整数第j位上的数，通过将这个整数右移j位后与1按位与可以得到
                count[j] %= 3;
            }
        }
        int result = 0;
        for (int i=0; i<nBits; i++) {
            result += (count[i]<<i);//将二进制转化为十进制数，因为i从0开始，而且“小端模式”存储，故可以通过左移i位并相加得道十进制数
        }
        return result;
    }
    
    //time:O(n), space:O(1)
    int singleNum3_ver2(std::vector<int> &nums)
    {
        int one=0, two=0, three=0;
        for (auto i : nums) {
            two |= (one & 1);
            one ^= i;
            three = ~(one & two);
            one &= three;
            two &= three;
        }
        return one;
    }
};
