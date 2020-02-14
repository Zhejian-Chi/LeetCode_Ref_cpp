//
//  _2121-2122_GasStation-Candy.cpp
//  LeetCode
//
//  Created by chizhejian on 11/25/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//
#include <vector>
//#include <functional>
#include <string>
//#include <unordered_map>
#include <algorithm>
#include <numeric>
//#include <cstdlib>
//#include <cmath>

/*
 2.1.21：gas station
 问题：环形道路上有N个加油站，第i个加油站有g［i］的汽油，你有一辆车可以装无限制的汽油，它从第i个站开到第i＋1个站需要消耗cost［i］的汽油，开始时油箱是空的。返回加油站的位置，让你能在环形路上能绕一圈，否则返回－1。输入保证结果唯一
 求解：1.最简单的就是从1到N遍历，满足条件结束。复杂度O（n平方）
 
 */

class GasStaion {
public:
    // time: O(n)
    int gasStation(std::vector<int> &gas, std::vector<int> &cost)
    {
        int restGas = 0;
        int hasSolution = -1;
        for (int i=0, sum=0; i<gas.size(); i++) {
            restGas += gas[i]-cost[i]; //总油量减去总消耗量是否等于大于0，若是，肯定有解
            sum += gas[i]-cost[i];//记录当前位置的剩余油量，若小于0，则说明此位置不能选为开头
            if (sum < 0) {
                hasSolution = i; //记录下油量不够的位置
                sum = 0;
            }
        }
        return restGas >= 0 ? hasSolution+1 : -1;
    }
};



/*
 2.1.22：candy
 问题：N个小孩，每个都有一个rating。给他们分糖果，每个人都至少一个糖果，并且rating大的小孩糖果数要大于他的左右邻居。至少需要多少糖果。
 

 */

class Candy1 {
public:
    //迭代版
    int minCandy(const std::vector<int> &rating)
    {
        const int n = rating.size();
        std::vector<int> increase(n);//记录第i个孩子需要增加多少个糖果才满足条件
        
        //从左往右扫描，当第i个人rating大于第i－1人时（与左邻居比较），需要增加的糖果数纪录在increase［i］中，具体增加多少用inc记录，同时与increase［i］中的已有记录进行比较，取较大值。
        for (int i=1, inc=1; i<n; i++) {
            if(rating[i]>rating[i-1])
                increase[i] = std::max(increase[i],inc++);
            else
                inc = 1;
        }
        //从右往左扫描，此时与右邻居比较
        for (int i=n-2, inc=1; i>=0; i--) {
            if(rating[i]>rating[i+1])
                increase[i] = std::max(increase[i],inc++);
            else
                inc = 1;
        }
        //最后累计所有结果，因为每个人至少都有一个糖果，故初始值为n
        return std::accumulate(&increase[0], &increase[0]+n, n);
    }
    
    //递归版
    int minCandy_ver2(const std::vector<int> &rating)
    {
        std::vector<int> f(rating.size());//存储第i个小孩需要分的糖果数
        int sum = 0;
        for (int i=0; i<rating.size(); ++i) {
            sum += solve_(rating, f, i);//第i个小孩需要分的糖果数
        }
        return sum;
    }
    
private:
    int solve_(const std::vector<int> &rating, std::vector<int> &f, int i)
    {
        if (f[i] == 0) {
            f[i] = 1;//如果还没分糖果，则先分一个
            if (i>0 && rating[i]>rating[i-1]) {//从第二个小孩开始从左到右扫描，计算需要的糖果数
                f[i] = std::max(f[i], solve_(rating, f, i-1)+1);
            }
            if (i<rating.size()-1 && rating[i]>rating[i+1]) {
                f[i] = std::max(f[i], solve_(rating, f, i+1)+1);
            }
        }
        return f[i];
    }
};
