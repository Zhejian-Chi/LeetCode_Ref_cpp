//
//  212_RemoveDuplicate2.cpp
//  LeetCode
//
//  Created by chizhejian on 9/30/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <iostream>
#include <vector>

class Soution2 {
public:
    int removeDuplicates2(std::vector<int>& num) {
        if(num.size()<=2)
            return (int)num.size(); //directly return size which is equal and less than 2
        
        int index = 2; // 记录要需要改变的数字位置，将数字改为3就可以用于3个相同当情况了，拓展性较好
        for (int i=2; i<num.size(); i++) {
            if(num[i]!=num[index-2])
                num[index++]=num[i];
        }
        return index;
    }
    
    int removeDuplicates3(std::vector<int>& num) {
        const int n = (int)num.size();
        int index = 0;
        for (int i=0; i<n; ++i) {
            //相同个数超过2时，i会增加到不同为止
            if(i>0 && i<n-1 && num[i]==num[i-1] && num[i]==num[i+1])
                continue;
            
            num[index++] = num[i];
        }
        return index;
    }
};
