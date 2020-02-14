//
//  211_RemoveDuplicate.hpp
//  LeetCode

//  Remove Duplicates from Sroted Array

//  Created by chizhejian on 9/23/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#ifndef _11_RemoveDuplicate_hpp
#define _11_RemoveDuplicate_hpp

#include <stdio.h>
#include <vector>
#include <list>
class SolutionOfRDfromSort {
public:
    // 解法1: 将相同的数字用后面不同的数字直接替换，返回最后一个值的位置
    int removeDupicates(std::vector<int>&);
    
    // use STL directly
    int removeDupicates1(std::vector<int>&);
    
    // use list 
    int removeDupicates2(std::list<int>&);
};

#endif /* _11_RemoveDuplicate_hpp */
