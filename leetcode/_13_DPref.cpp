//
//  _13_DPref.cpp
//  LeetCode
//
//  Created by chizhejian on 2/1/20.
//  Copyright © 2020 chizhejian. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <string>

#define MAX_OF_TWO(a,b) (a)>(b)?(a):(b)
#define MIN_OF_TWO(a,b) (a)<(b)?(a):(b)

/*
 13.1 triangle
 
 */


/*
 13.2 Max Subarray sum
 eg:
 [−2,1,−3,4,−1,2,1,−5,4] the contiguous subarray [4,−1,2,1] has
 the largest sum = 6.
 设状态f［j］表示数组s中以s［j］为结尾的最大连续子序列和，则状态转移为：
 f［j］＝ max｛f［j－1］＋s［j］， s［j］｝ j＝ 1 to n
 result ＝ max｛f［j］｝
 */
class MaximumSubarraySum {
public:
    // 1.dynamic programming
    int maxSubarrSum(const std::vector<int>& num)
    {
//        if (num.empty()) {
//            return 0;
//        }
        int result = INT_MIN;
        int sum_j = 0;
        right = 0;
        for (int i = 0; i < num.size(); ++i) {
            sum_j = MAX_OF_TWO(sum_j + num[i], num[i]);
            if (sum_j > result) {
                result = sum_j;
                right = i;
            }
        }
        return result;
    }
    
    
    int getPrevIndex(const std::vector<int>& num, int result = INT_MIN)
    {
        if (result == INT_MIN) {
            result = maxSubarrSum(num);
        }
        for (int i = right; i >= 0; --i) {
            result -= num[i];
            if (result == 0) {
                return i;
            }
        }
        return 0;
    }
    
    // 2. normal 
    int maxSubarrSum_ver2(std::vector<int>& num)
    {
        return maxSubsum(num.begin(), num.end());
    }
    
private:
    int right;
    
    template<typename Iter>
    int maxSubsum(Iter begin, Iter end)
    {
        int result, cur_min;
        const int N = std::distance(begin, end);
        int *sum = new int[N + 1]; //前n项和
        sum[0] = 0;
        result = INT_MIN;
        cur_min = sum[0];
        
        for (int i = 1; i <= N; ++i) {
            sum[i] = sum[i-1] + *(begin+i-1);
        }
        for (int i = 1; i <= N; ++i) {
            result = MAX_OF_TWO(result, sum[i]-cur_min);
            cur_min = MIN_OF_TWO(cur_min, sum[i]);
        }
        
        delete []sum;
        return result;
    }
};


/*
 13.3 palindrome partition2
 给定一个字符串s，用最少的分隔使得子串都是回文
 s＝“aab”，则“aa”，“b” 都是回文，那么分隔为1
 
 设f（i）＝区间［i，n－1］之间最小的cut数，n为字符串长度，则
 f（i）＝min｛f（j＋1）＋1｝，i<=j<n
 现在的问题是如何判断［i，j］是否回文。定义状态p[i][j]=true if[i,j]为回文，则
 p[i][j]＝ str［i］＝＝str［j］&& p[i＋1][j-1]
 */
class PalindromePar {
public:
    int minCut(const std::string& str)
    {
        if (str.empty()) {
            return 0;
        }
        const int N = str.size();
        int f[N+1];
        bool p[N][N];
        std::fill_n(&p[0][0], N*N, false);
        
        // the worst case is cutting by each char
        for (int i = 0; i <= N; ++i) {
            f[i] = N - 1 - i; // last one f[N]=-1
        }
        for (int i = N - 1; i >= 0; --i) {
            for (int j = i; j < N; ++j) {
                if (str[i] == str[j] && (j - i < 2 || p[i+1][j-1])) {
                    p[i][j] = true;
                    f[i] = MIN_OF_TWO(f[i], f[j+1]+1);
                }
            }
        }
        return f[0];
    }
};


/*
 13.4 maximal rectangle
 given a 2d binary matrix filled with 0 and 1, find largest rectangle
 containning all 1 and return its area
 查找最大矩形，所以它一定是以 某个行元素开始的，将要找到的某个矩形就转换成某一个行开始的最大矩形Histogram问题。
 */
class MaximalRectangle {
public:
    
    /*
     方法一:简单的，类似于 Container With Most Water，对每个柱子，左右扩展，直到碰到比自己矮的，计算这个矩
     形的面积，用一个变量记录最大的面积，复杂度 O(n^2) ，会超时。
     */
    int maximalRectangle(std::vector<std::vector<int>>& maxtrix)
    {
        if (maxtrix.empty()) {
            return 0;
        }
        const int m = maxtrix.size();
        const int n = maxtrix[0].size();
        std::vector<int> H(n, 0);
        std::vector<int> L(n, 0);
        std::vector<int> R(n, 0);
        
        int ret = 0;
        for (int i = 0; i < m; ++i) {
            int left = 0, right = n;
            
            // calculate L(i, j) from left to right
            for (int j = 0; j < n; ++j) {
                if (maxtrix[i][j] == '1') {
                    ++H[j];
                    L[j] = MAX_OF_TWO(L[j], left);
                } else {
                    left = j + 1;
                    H[j] = 0;
                    L[j] = 0;
                    R[j] = n;
                }
            }
            
            // calculate R(i, j) from right to left
            for (int j = n - 1; j >= 0; --j) {
                if (maxtrix[i][j] == '1') {
                    R[j] = MIN_OF_TWO(R[j], right);
                    ret = MAX_OF_TWO(ret, H[j]*(R[j] - L[j]));
                } else {
                    right = j;
                }
            }
        }
        return ret;
    }
    
    /*
     
     */
    
};

/*
 13.1 merge sort
 
 */
