//
//  _215_MedianOfTwoArray.cpp
//  LeetCode
//
//  Created by chizhejian on 10/29/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
class MedianOfTwoSortedArray {
public:
    double findMedianOfTwoSortedArray(const std::vector<int> &A,
                                      const std::vector<int> &B)
    {
        const int size_a = A.size();
        const int size_b = B.size();
        int total_size = size_a + size_b;
        if (total_size & 0x1) {
            return find_k_th(A.begin(), size_a, B.begin(), size_b, total_size/2 + 1);
        }
        else {
            return (find_k_th(A.begin(), size_a, B.begin(), size_b, total_size/2) + find_k_th(A.begin(), size_a, B.begin(), size_b, total_size/2 + 1)) / 2.0;
        }
    }
    
    
private:
    // 找第k大的元素
    static int find_k_th(std::vector<int>::const_iterator A, const int size_a,
                         std::vector<int>::const_iterator B, const int size_b, int k)
    {
        // 这里总是假设size_a <= size_b，如果输入不是这样，直接交换就好
        if (size_a > size_b) {
            return find_k_th(B, size_b, A, size_a, k);
        }
        // 若A为空，问题变为找递增序列B的第k大值，直接返回即可
        if (size_a == 0) {
            return *(B+k-1);
        }
        if (k == 1) {
            return std::min(*A, *B);
        }
        
        // 将k分成两个部分
        int ia = std::min(k/2, size_a), ib = k - ia;
        if (*(A+ia-1) < *(B+ib-1)) {
            return find_k_th(A+ia, size_a-ia, B, size_b, k-ia);
        }
        else if (*(A+ia-1) > *(B+ib-1)) {
            return find_k_th(A, size_a, B+ib, size_b-ib, k-ib);
        }
        else
            return A[ia-1];
    }
};


/*
给定排好序的两个数组A和B，找到其中第k大的数。
 1.直观解法：给两个指针pa和pb分别指向A和B，m为计数器，表示当前数为第m大。如果A当前小，则pa＋＋，m＋＋；如果B当前小
            则pb＋＋，m＋＋。最终m＝k时得到答案。复杂度O（a＋b）
 2.考虑到A的中位数为ma，B的中位数为mb，那么AB的中位数M一定满足ma<M<mb。
    假设A，B元素都大于k／2，将A的第k/2个元素与B的第k/2个元素比较，则：（假设k为偶数，奇数时也一样）
    A[k/2-1]==B[k/2-1];
    A[k/2-1]>B[k/2-1];
    A[k/2-1]<B[k/2-1];
    若A[k/2-1]<B[k/2-1]，意味着A[k/2-1]一定小于k，即A［0］到A[k/2-1]之间到值可以排除；
    同理，A[k/2-1]>B[k/2-1]时，可以删除B［0］到B[k/2-1]的值；
    而A[k/2-1]==B[k/2-1]时，就是答案。
  用递归实现，时间空间复杂度O(log(m+n))
*/
