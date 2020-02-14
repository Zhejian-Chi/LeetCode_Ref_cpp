//
//  _2116_Rotate_Image(Matrix).cpp
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
 问题：给定一个n＊n的矩阵，将其顺时针旋转90度，不使用额外空间
 
 求解：
 1.先沿着副对角线翻转一次，然后沿着水平中线翻转一次即可。
    1 2    4 2      3 1
    3 4    3 1      4 2
 2.或者先沿着水平中线翻转一次，然后再沿着主对角线翻转一次。
    1 2    3 4      3 1
    3 4    1 2      4 2
 */


class Rotate_Images {
public:
    void rotateImages(std::vector<std::vector<int>> &matrix)
    {
        const int n = matrix.size();
        for (int i=0; i<n/2; i++) {
            for (int j=0; j<n; j++) {
                std::swap(matrix[i][j], matrix[n-i-1][j]);//沿着水平中线翻转
            }
        }
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                std::swap(matrix[i][j], matrix[j][i]);//沿着主对角线翻转
            }
        }
    }
    
    
    void rotateImages_ver2(std::vector<std::vector<int>> &matrix)
    {
        const int n = matrix.size();
        for (int i=0; i<n; i++) {
            for (int j=0; j+i<n; j++) {
                std::swap(matrix[i][j], matrix[n-1-j][n-1-i]);//沿着副对角线翻转
            }
        }
        for (int i=0; i<n/2; i++) {
            for (int j=0; j<n; j++) {
                std::swap(matrix[i][j], matrix[n-i-1][j]);//沿着水平中线翻转
            }
        }
    }
};
