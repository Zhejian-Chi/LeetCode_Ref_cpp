//
//  _218_ThreeSums.cpp
//  LeetCode
//
//  Created by chizhejian on 11/2/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <unordered_map>

/*
 Q: given an array S of n integers, there are 3 elements a,b,c in S such that a+b+c=0. find all
    unique triples in arrray.
 note:
    elements in a triple (a,b,c) must be in non-descending order.(a<=b<=c)
    the solution set must not contain duplicate triples.
 eg:
    S = {-1 0 1 2 -1 4}
    output:
        (-1,0,1)
        (-1,-1,2)
 
 解法：排序，再左右夹逼，跳过重复的数，时间复杂度O（n平方），空间O（1）;
      此方法可推广到k－sum，先排序，然后做k－2次循环，在最内层循环左右夹逼，时间复杂度是O（max｛nlogn， n^(k-1)})
 */

class ThreeSumToZero {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
        std::vector<std::vector<int>> result; //用vector容器返回结果
        if (nums.size() < 3) {
            return result;
        }
        std::sort(nums.begin(), nums.end());//排序后可以先定一个数，然后从剩下的数中通过夹逼找另外两个数。然后通过循环，前面已经找过的数就可以不用再找了。例如－1，0，1，2，先确定－1，然后从剩下的0，1，2中找。下一次就不用再从－1开始了，直接从0开始，直至结束。
        
        const int target = 0; //target可以是任意需要的数，这里取0
        
        auto last = nums.end();
        for (auto i = nums.begin(); i < last-2; ++i) {
            auto j = i+1; //从i的下一个数开始往后，因为前面的数已经匹配过了，这就是排序后可以用的策略
            if (i > nums.begin() && *i == *(i-1)) { //跳过重复的数
                continue;
            }
            auto k = last-1; //从最后一个数开始往前
            while (j < k) { //夹逼寻找另外两个数，j表示从左到右找，不匹配则j＋＋，k表示从右到左找，不匹配则k－－
                if (*i + *j + *k < target) { //若三个数的和小于目标值，让左边的值增大，即j＋＋
                    ++j;
                    while (*j == *(j-1) && j < k) { //跳过重复的数
                        ++j;
                    }
                }
                else if (*i + *j + *k > target) { //若三个数的和大于目标值，让右边的值减小，即k－－
                    --k;
                    while (*k == *(k+1) && j < k) { //跳过重复的数
                        --k;
                    }
                }
                else {
                    result.push_back({*i, *j, *k}); //找到一组匹配值，加入result容器中，并让j＋＋，k－－
                    ++j;
                    --k;
                    while (*j == *(j-1) && *k == *(k+1) && j < k) { //跳过重复的数
                        ++j;
                    }
                }
            }
        }
        return result;
    }
};
