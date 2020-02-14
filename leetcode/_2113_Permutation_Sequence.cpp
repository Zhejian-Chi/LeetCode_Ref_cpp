//
//  _2113_Permutation_Sequence.cpp
//  LeetCode
//
//  Created by chizhejian on 11/22/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//

#include <vector>
#include <functional>
#include <string>
//#include <unordered_map>
//#include <algorithm>
//#include <cstdlib>

/*
 问题：一个n个自然数的集合｛1，2，。。。，n｝，给定一个k，输出按照字典序的排列的第k个全排列序列。（n属于1到9）
 例如：n＝3，k＝4
 当n＝3时，所有全排列按照字典序为123，132，213，231，312，321。
 k＝4，就是输出“231”
 
 求解算法：
 1.暴力枚举，从头开始算。（这里以2112中函数为例，可以调用k－1次next_permutation（）函数，当然，stl中也提供了这个函数，stl中还提供了前一个排列的函数prev_permutation() ）。
    但是暴力法把前k－1个都求出来了，而问题只需要第k个
 2.康托编码，无重复元素的全排列。（转最后）
 */

class PermutationSequenceOfK {
public:
    //暴力枚举
    std::string getKthPermutation(int n, int k)
    {
        std::string s(n, '0');
        for (int i=0; i<n; i++) {
            s[i] += (i+1);
        }
        for (int i=0; i<k-1; i++)
            std::next_permutation(s.begin(), s.end());//这里直接调用stl中的函数
        return s;
    }
    
    
    //康托编码
    std::string getKthPermutation_K_ver(int n, int k)
    {
        std::string s(n, '0');
        for (int i=0; i<n; i++) {
            s[i] += (i+1);
        }
        
        return kth_permutation(s, k);
    }
    
private:
    
    const unsigned int fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
    
    template<typename Sequence>
    Sequence kth_permutation(const Sequence &seq, int k)
    {
        const int n = seq.size();//seq需要先排好序
        Sequence S(seq); //定义一个操作序列，计算得到某一位的值后取出，并删除该值
        Sequence result; //用于存储排列的序列，每次存入1个从S中取出的值
        
        int base = fact[n-1]; //阶乘数组（0-8）
        --k; //前k－1个
        
        for (int i=n-1; i>0; k %= base, base /= i, --i) { //求余数和商，
            auto a = std::next(S.begin(), k/base); //找到从序列S头开始往后数k/base位的位置，返回其迭代器
            result.push_back(*a); //将取出的值村人result容器中
            S.erase(a); //删除已经取出的容器，让下一次找取出元素更方便
        }
        
        result.push_back(S[0]);//插入最后一个元素
        return result;
    }
};


/*
全排列的编码：
 ｛1，2，。。。，n｝的排列共有n！个，将其按照字典序排列，如何知道某一个排列在序列中排第几个？
 例子：｛1，2，3｝中有6个全排列，123 132 213 231 312 321 。 想知道321是排在序列中第几个。
 这样考虑：第一位是3，比他小的有1和2两个数，首位确定1或者2后，剩下2位有2！种，所以共有2*2！＝4种情况的数是比321小的。
         第二位时2，比他小的只有1，第二位确定后只剩下1位，所以共有1＊1！＝1种情况比321小的。
         第三位（最后一位），没有比他小的了。
         综合三位数的情况共有4+1+0=5种情况比321小，故321是第六小。
 推广一下就是：一个数列a1a2。。。an，是｛1，2，。。。，n｝的一个排列，他排在第k位，那么按照康托编码，比这个数小的排列的个数  k－1＝（a1）*（n－1）！＋（a2）*（n－2）！＋。。。＋（an）*0！。这里（ai）表示比ai小的数字个数，但数要排除从a1到ai－1中已经出现的个数。例如当前ai＝8，比他小的数有7个，但是从a1到ai－1中已经出现了1，3，4这三个，那么最终的个数只有4个，即（ai）＝4
 
全排列的解码：
 如何找出第16个｛1，2，3，4，5｝的排列？
 1.首先16-1=15.因为要找的是第16个，所以比他小的数是15个。
 2.用15去除4！（因为除去第一个位置的数，后面还有4个数，共4！中情况），得到0余15。说明有0个比第一位小的数，那么第一位的数就是1.
 3.用15去除3！（因为除去第二个位置的数，后面还有3个数，共3！中情况，以下类似），得到2余3。说明有2个比第二位小的数，那么第二位的数就是3（1和2比3小），但是第一位已经是1了，所以此数实际为4（2和3比4小）。
 4.用3去除2！，得到1余1。说明有1个数比第三位小，此数为2，但是1已经出现，故此数实际为3
 5.用1去除1！，得到1余0。此数为2，但1，3，4都出现了，所以只能是5. 最后一位只能是2
 所以排列是｛1，4，3，5，2｝
 
 */


