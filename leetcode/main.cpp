//
//  main.cpp
//  LeetCode
//
//  Created by chizhejian on 9/23/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <iostream>
#include <utility>
#include <unordered_map>
#include <memory>
#include <vector>
#include <list>
//#include "_221-225_AddTwoNum-RemoveDuplicate.cpp"
//#include "_226-2210_RotateList-CopyList.cpp"
//#include "_31-315_Stringref.cpp"
//#include "_6.1-6.cpp"
#include "_13_DPref.cpp"

int main(int argc, const char * argv[]) {
    
    
    
//    int a[] = {1, -2, -4, 10, 3};
    int a[] = {-2,1,-3,4,-1,2,1,-5,4};
    std::vector<int> arr(a, a+9);
//    MyQuickSort myqs;
    MaximumSubarraySum mss;
    int res = mss.maxSubarrSum(arr);
    int i = mss.getPrevIndex(arr, res);
//    for(auto i: arr)
//        std::cout << i << ' ';
    std::cout << res << ',' << i << std::endl;
//    myqs.myQuicksort(arr, 0, arr.size()-1);
//    for(auto i: arr)
//        std::cout << i << ' ';
//    std::cout << *a << std::endl;
//    decltype(*a) b = a[0];
    
    
//    std::remove_reference<decltype(*a)>::type b = a[0];
//    a[0] = 100;
//    std::cout << b;
//    std::cout<<INT_MAX<<','<<INT_MIN<<std::endl;
    
//    Implement_strStr strstr;
//    std::string s1 = "abcdabc";
//    std::string s2 = "dab";
//    std::cout << strstr.my_strStr(s1, s2) << std::endl;
//    std::cout << strstr.my_strStr_kmp(s1, s2) << std::endl;
//    while (p) {
//        std::cout<<p->val<<' ';
//        p=p->next;
//    }
//    std::cout<<std::endl;

    return 0;
}
