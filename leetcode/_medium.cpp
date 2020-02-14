//
//  _medium.cpp
//  LeetCode
//
//  Created by chizhejian on 2/12/20.
//  Copyright © 2020 chizhejian. All rights reserved.
//

#include <stdio.h>
#include <iostream>

/*
Divide Two Integers
求两数相除，而且不能用乘法，除法和取余操作
 use 位操作
*/
class DivideTwoIntegers {
public:
    int divideTwoInt(int divided, int divider)
    {
        if ((divided == INT_MIN && divider == -1) || divider == 0) {
            return INT_MAX;
        }
        if (divider == divided) {
            return 1;
        }
        int isNegtive_1 = 0;
        int isNegtive_2 = 0;
        if (divided < 0) {
            isNegtive_1 = 1;
            divided = -divided;
        }
        if (divider < 0) {
            isNegtive_2 = 1;
            divider = -divider;
        }
        int res = 0;
        while (divided > divider) {
            int t = divider;
            int p = 1;
            while(divided >= (t<<1)) {
                t = t << 1;
                p = p << 1;
            }
            res += p;
            divided -= t;
        }
        if ((isNegtive_1 ^ isNegtive_2) == 1) {
            return res;
        } else {
            return -res;
        }
    }
    
private:
    
};
