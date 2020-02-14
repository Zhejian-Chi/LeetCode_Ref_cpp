//
//  _6.1-6.cpp
//  LeetCode
//
//  Created by chizhejian on 1/28/20.
//  Copyright © 2020 chizhejian. All rights reserved.
//

#include <stdio.h>
#include <vector>

//－－－－－－－－－－－－－－－－－－－－－－
//single quicksort

class MyQuickSort {
public:
    void myQuicksort(std::vector<int>& num, int left, int right)
    {
        if (num.empty() || left >= right) {
            return;
        }
        int index = mypartition(num, left, right);
        myQuicksort(num, left, index-1);
        myQuicksort(num, index+1, right);
    }
    
private:
    int mypartition(std::vector<int>& num, int left, int right)
    {
        int i = left+1;
        int j = right;
        int val = num[left];
        while (i < j) {
            while (num[i] < num[left]) {
                i++;
            }
            while (num[j] > num[left]) {
                j--;
            }
            swapTwoNum(num[i], num[j]);
        }
        swapTwoNum(num[left], num[i]);
        return i;
    }
    
    void swapTwoNum(int& a, int& b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
};

/*
 6.1 merge sort
 
 */


/*
 6.
 
 */


/*
 6.
 
 */


/*
 6.
 
 */


/*
 6.
 
 */


/*
 6.
 
 */


/*
 6.
 
 */


