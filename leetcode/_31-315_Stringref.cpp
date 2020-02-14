//
//  _31-315_Stringref.cpp
//  LeetCode
//
//  Created by chizhejian on 1/19/20.
//  Copyright © 2020 chizhejian. All rights reserved.
//

#include <stdio.h>
#include <algorithm>
#include <string>
//#include <iostream>

/*
 3.1：
 问题：回文
 例如：->
 */
class Palindrome {
public:
    bool isPalindrome(std::string str)
    {
        if (str.empty()) {
            return false;
        }
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        auto left = str.begin();
        auto right = prev(str.end());
        while (left < right) {
            if (!::isalnum(*left)) {
                ++left;
            } else if (!::isalnum(*right)) {
                --right;
            } else if (*left != *right) {
                return false;
            } else {
                ++left;
                --right;
            }
        }
        return true;
    }
};

/*
 3.2：Implement strStr()
 例如：->
 */
class Implement_strStr {
public:
    //violent enum
    int my_strStr(const std::string& haystack, const std::string& needle)
    {
        if (needle.empty()) {
            return -1;
        }
        const unsigned long N = haystack.size() - needle.size() + 1;
        for (int i = 0; i < N; ++i) {
            int j = i;
            int k = 0;
            while (j < haystack.size() && k < needle.size() && haystack[j] == needle[k]) {
                ++j;
                ++k;
            }
            if (k == needle.size()) {
                return i;
            }
        }
        return -1;
    }
    
    //KMP
    int my_strStr_kmp(const std::string& haystack, const std::string& needle)
    {
        return my_kmp(haystack.c_str(), needle.c_str());
    }
    
private:
    static int my_kmp(const char* text, const char* pattern)
    {
        int i;
        int j = -1;
        const unsigned long n = strlen(text);
        const unsigned long m = strlen(pattern);
        if (n == 0 && m == 0) {
            return 0; // "" , ""
        }
        if (m == 0) {
            return 0; // "a", ""
        }
        
        int* next = new int[m];
        compute_prefix(pattern, next);
        
        for (i = 0; i < n; ++i) {
            while (j > -1 && pattern[j+1] != text[j]) {
                j = next[j];
            }
            if (text[i] == pattern[j+1]) {
                ++j;
            }
            if (j == m-1) {
                delete []next;
                next = nullptr;
                return i - j;
            }
        }
        delete []next;
        next = nullptr;
        return -1;
    }
    
    static void compute_prefix(const char* pattern, int* next)
    {
        int i;
        int j = -1;
        const unsigned long m = strlen(pattern);
        
        next[0] = j;
        for (i = 1; i < m; ++i) {
            while (j > -1 && pattern[j+1] != pattern[j]) {
                j = next[j];
            }
            if (pattern[i] == pattern[j+1]) {
                ++j;
            }
            next[i] = j;
        }
    }
};



/*
 3.3：atoi()
 例如：
 */
class MyAtoi {
public:
    int myAtoi(const std::string& str)
    {
        if (str.empty()) {
            return 0;
        }
        
        int sign = 1; // is negetive or not
        int num = 0;
        const unsigned long N = str.length();
        int i = 0;
        
        while (str[i] == ' ' && i < N) { //find first non-blank charactor
            ++i;
        }
        
        if (str[i] == '+') {
            ++i;
        } else if (str[i] == '-'){
            sign = -1;
            ++i;
        }
        
        for (; i < N; ++i) {
            if (str[i] < '0' || str[i] > '9') {
                break;
            }
            if (num > __INT_MAX__ / 10 || (num == __INT_MAX__ / 10 && (str[i] - '0') > __INT_MAX__ % 10)) {
                return sign == -1 ? (-__INT_MAX__  -1) : __INT_MAX__;
            }
            num = num * 10 + (str[i] - '0');
        }
        return num * sign;
    }
};


/*
 3.4：add binary
 问题：
 例如：“11” ＋ “1” ＝ “100”
 */
class AddBinary {
public:
    std::string addBinary(std::string& a, std::string& b)
    {
        std::string result;
        const size_t N = a.size() > b.size() ? a.size() : b.size();
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());
        int countAdv = 0;
        for (size_t i = 0; i < N; ++i) {
            const int ai = i < a.size() ? a[i]-'0' : 0;
            const int bi = i < b.size() ? b[i]-'0' : 0;
            const int val = (ai + bi + countAdv) % 2;
            countAdv = (ai + bi + countAdv) / 2;
            result.insert(result.begin(), val+'0');
        }
        if (countAdv == 1) {
            result.insert(result.begin(), '1');
        }
        return result;
    }
};


/*
 3.5
 问题：最长回文子串
 例如：->
 */
class LongestPalindromicSubString {
public:
    // dynamic programming
    // 设状态f(i,j)表示区间 [i,j] 是否为回文
    std::string longestPSstr(const std::string& str)
    {
        const size_t N = str.size();
        bool isPSstr[N][N];
        std::fill_n(&isPSstr[0][0], N*N, false);
        
        size_t max_len = 1, start = 0; //
        for (size_t i = 0; i < N; ++i) {
            isPSstr[i][i] = true;
            for (size_t j = 0; j < i; ++j) {
                isPSstr[j][i] = (str[i] == str[j] && (i - j < 2 || isPSstr[j+1][i-1]));
                if (isPSstr[j][i] && max_len < (i-j+1)) {
                    max_len = i - j + 1;
                    start = j;
                }
            }
        }
        return str.substr(start, max_len);
    }
};


/*
 3.6：regular expression matching
 问题：”。“ matches any single character, "*" matches zero or more of the preceding element
 例如：
 isMatch("aa","a") → false
 isMatch("aa","aa") → true
 isMatch("aaa","aa") → false
 isMatch("aa", "a*") → true
 isMatch("aa", ".*") → true
 isMatch("ab", ".*") → true
 isMatch("aab", "c*a*b") → true
 */
class RegularMatching {
public:
    bool isMatch(const std::string& s, const std::string& p)
    {
        return isMatches(s.c_str(), p.c_str());
    }
    
private:
    bool isMatches(const char* s, const char* p)
    {
        if (*p == '\0') {
            return *s == '\0';
        }
        
        // next char is not "*", then must match current character
        if (*(p+1) != '*') {
            if (*p == *s || (*p == '.' && *s != '\0')) {
                return isMatches(s+1, p+1);
            } else {
                return false;
            }
        } else { // next char is '*'
            while (*p == *s || (*p == '.' && *s != '\0')) {
                if (isMatches(s, p+2)) {
                    return true;
                }
                ++s;
            }
            return isMatches(s, p+2);
        }
    }
};


/*
 3.7：wildcard matching
 问题：'?' matches any single character, '*' matches any sequence (including empty)
 例如：
 isMatch("aa","a") → false
 isMatch("aa","aa") → true
 isMatch("aaa","aa") → false
 isMatch("aa", "*") → true
 isMatch("aa", "a*") → true
 isMatch("ab", "?*") → true
 isMatch("aab", "c*a*b") → false
 */
class WildcardMatching {
public:
    bool wildcardMatch(const std::string& s, const std::string& p)
    {
        return isMatch_rev(s.c_str(), p.c_str());
    }
    
private:
    // reverse version (out of time)
    bool isMatch_rev(const char* s, const char* p)
    {
        if (*p == '*') {
            while (*p == '*') {
                ++p; // skip continuous '*'
            }
            if (*p == '\0') {
                return true;
            }
            while (*s != '\0' && !isMatch_rev(s, p)) {
                ++s;
            }
            return *s != '\0';
        } else if (*p == '\0' || *s == '\0') {
            return *p == *s;
        } else if (*p == *s || *p == '?') {
            return isMatch_rev(++s, ++p);
        } else {
            return false;
        }
    }
    
    // iterate version (O(m*n))
    bool isMatch_ite(const char* s, const char* p)
    {
        bool star = false;
        const char* str, *ptr;
        for (str = s, ptr = p; *str != '\0'; ++str, ++ptr) {
            switch (*ptr) {
                case '?':
                    break;
                    
                case '*':
                    star = true;
                    s = str, p = ptr;
                    while (*p == '*') {
                        ++p; // skip continuous '*'
                    }
                    if (*p == '\0') {
                        return true;
                    }
                    str = s - 1;
                    ptr = p - 1;
                    break;
                    
                default:
                    if (*str != *ptr) {
                        if (!star) {
                            return false; // has no '*' before, mismatch
                        }
                        ++s;
                        str = s - 1;
                        ptr = p - 1;
                    }
                    break;
            }
        }
        while (*ptr == '*') {
            ++ptr;
        }
        return (*ptr == '\0');
    }
};


/*
 3.：
 问题：
 例如：->
 */



/*
 3.：
 问题：
 例如：->
 */



/*
 3.：
 问题：
 例如：->
 */



/*
 3.：
 问题：
 例如：->
 */



/*
 3.：
 问题：
 例如：->
 */

