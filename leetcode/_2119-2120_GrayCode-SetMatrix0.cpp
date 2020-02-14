//
//  _2119-2120_GrayCode-SetMatrix0.cpp
//  LeetCode
//
//  Created by chizhejian on 11/23/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//
#include <vector>
//#include <functional>
#include <string>
//#include <unordered_map>
//#include <algorithm>
//#include <cstdlib>
//#include <cmath>

/*
 2.1.19：gray code
 二进制转gray code（gc）：保留二进制最高位为gc的最高位，二进制的第i位与第i－1位异或得到gc的第i位。
    例如：二进制1000，保留最高位1，gc的第二位为二进制第二位0与第一位1的异或，为1，以此类推，得到gc为1100
 gray code转二进制：保留gc的最高位为二进制的最高位，gc的第i位与二进制的第i－1位异或得到二进制的第i位。
    例如：gc为1101，保留最高位1，二进制的第二位为gc的第二位1与二进制的第一位1异或，为0，以此类推，得到二进制1001
 
 问题：给定一个非负整数n代表二进制的位数，打印出所有的n位gray code序列，并从0开始打印
    例子：n＝2 ，打印0(00)，1(01)，3(11)，2(10)，括号中代表对应的gc
 求解：1.数学公式，整数N的gray code为N与（N/2）的异或。故对0——2^N－1依次求gc
      2.递归，n比特对gc可以递归的从n－1的gc中生成。
        例如： n＝1时，gc为0，1
              n＝2时，从n＝1中的gc前分别加上0和1，得到00，01；10，11
              n＝3时，为000，001，010，011；100，101，110，111.以此类推
 */

class Binary2GrayCode {
public:
    std::vector<int> binary2GrayCode(int n)
    {
        std::vector<int> result;
        const size_t sizeOf2n = 1 << n; //2^n
        for (int i=0; i<sizeOf2n; i++) {
            result.push_back(i^(i>>1)); //
        }
        return result;
    }
    
    std::vector<int> binary2GrayCode_ver2(int n)
    {
        std::vector<int> result;
        result.reserve(1<<n);
        result.push_back(0);
        for (int i=0; i<n; i++) {
            const int highest_bit = 1 << i;
            for (int j=result.size()-1; j>=0; j--) {
                result.push_back(highest_bit | result[j]); //反着遍历，才能对称
            }
        }
        return result;
    }
};


/*
 2.1.20：set matrix zero
 问题：找到m＊n矩阵中的0，并把它所在的行和列都变为0
 
 */
class SetMatrixZero {
public:
    
    // time:O(m*n), space:O(m+n)
    void setMatrixZero(std::vector<std::vector<int>> &matrix)
    {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();
        
        std::vector<bool> row(m, false);
        std::vector<bool> col(n, false);
        
        for (size_t i=0; i<m; i++) {
            for (size_t j=0; j<n; j++) {
                if (matrix[i][j] == 0) {
                    row[i] = col[j] = true;
                }
            }
        }
        
        for (size_t i=0; i<m; i++) {
            if (row[i]) {
                std::fill(&matrix[i][0], &matrix[i][0]+n, 0);
            }
        }
        
        for (size_t j=0; j<n; j++) {
            if (col[j]) {
                std::fill(&matrix[0][j], &matrix[0][j]+m, 0);
            }
        }
    }
    
    // time:O(m*n), space:O(1)
    void setMatrixZero_ver2(std::vector<std::vector<int>> &matrix)
    {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();
        
        bool row_has_zero = false;//第一行是否有0
        bool col_has_zero = false;//第一列是否有0
        
        for (size_t i=0; i<m; i++) {
            if (matrix[i][0] == 0) {
                col_has_zero = true;
                break;
            }
        }
        for (size_t i=0; i<n; i++) {
            if (matrix[0][i] == 0) {
                row_has_zero = true;
                break;
            }
        }
        
        for (size_t i=1; i<m; i++) {
            for (size_t j=1; j<n; j++) {
                if (matrix[i][j] == 0) {//除第一行和第一列外，若第i行第j列是0，那么对应的第一行第j列和第1列第i行的元素也标记为0
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for (size_t i=1; i<m; i++) {
            for (size_t j=1; j<n; j++) {//除第一行和第一列外，若第一行第j列或者第1列第i行的元素为0，那么第i行第j列是0
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        //最后单独处理第一行和第一列
        if(row_has_zero)
            for (size_t i=0; i<n; i++) {
                matrix[0][i] = 0;
            }
        if(col_has_zero)
            for (size_t i=0; i<m; i++) {
                matrix[i][0] = 0;
            }
    }
};

