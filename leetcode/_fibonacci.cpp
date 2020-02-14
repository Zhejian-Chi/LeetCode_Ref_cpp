//
//  _fibonacci.cpp
//  LeetCode
//
//  Created by chizhejian on 10/29/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <stdio.h>

class FibonacciArray {
public:
    
    // 自底向上计算
    unsigned long fibonacciArray(unsigned int n){
        if (n < 2) {
            return n;
        }
        unsigned long fibOne = 1;
        unsigned long fibTwo = 0;
        unsigned long fibNum = 0;
        for (unsigned int i = 2; i <= n; i++) {
            fibNum = fibOne + fibTwo;
            fibTwo = fibOne;
            fibOne = fibNum;
        }
        return fibNum;
    }
    
    /*
     运用公式［fn fn－1；fn－1 fn－2］＝ ［1 1；1 0］^n-1
     */
//    unsigned long a[2][2] = {1, 1, 1, 0}; 
//    unsigned long fibonacciArray1(unsigned int n){
//        if (n < 2) {
//            return a[0][0];
//        }
//        fibonacciArray1(n>>1);
//        a[0][0]=a[0][0]*a[0][0]+a[0][1]*a[1][0];
//        a[0][1]=a[0][0]*a[0][1]+a[0][1]*a[1][1];
//        a[1][0]=a[1][0]*a[0][0]+a[1][0]*a[1][1];
//        a[1][1]=a[1][0]*a[0][1]+a[1][1]*a[1][1];
//        
//        return 1;
//        
//    }
};
