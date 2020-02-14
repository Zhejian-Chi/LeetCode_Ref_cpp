//
//  _221-225_AddTwoNum-RemoveDuplicate.cpp
//  LeetCode
//
//  Created by chizhejian on 11/25/19.
//  Copyright © 2019 chizhejian. All rights reserved.
//
#include <vector>
#include <functional>
#include <string>
//#include <unordered_map>
#include <algorithm>
#include <numeric>
//#include <cstdlib>
//#include <cmath>

//Node of LinkList
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr) {}
};



/*
 2.2.1：add two numbers
 问题：两个链表代表两个非负整数，数字是逆序排列的，将他们相加，返回结果链表（逆序），每个节点存储一位。
 例如：(2->4->3)+(5->6->4)=(7->0->8)
 */
class AddTwoNumbers {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) //输入为两个链表的头指针
    {
        ListNode dummy(-1); //定义一个头节点
        int carry = 0; //记录进位
        ListNode *prev = &dummy; //创建一个移动指针指向头节点，此指针用于创建新节点后链接到链表上
        for (ListNode *pa=l1, *pb=l2; pa!=nullptr || pb!=nullptr; //都为空时结束
             pa = (pa == nullptr) ? nullptr: pa->next,
             pb = (pb == nullptr) ? nullptr: pb->next,
             prev = prev->next) {
            const int ai = (pa == nullptr) ? 0 : pa->val;  //若节点非空，取出元素值val，否则赋值为0
            const int bi = (pb == nullptr) ? 0 : pb->val; //同上
            const int value = (ai+bi+carry) % 10;  //求和，并加上进位值，再取余数
            carry = (ai+bi+carry) / 10;  //求进位值
            prev->next = new ListNode(value);  //创建一个新节点，并链接到新链表上
        }
        if (carry > 0) {
            prev->next = new ListNode(carry); //最后一位也有进位，再生成一个节点存放
        }
        return dummy.next; //返回头节点的指针，即新链表的头指针
    }
};


/*
 2.2.2：Reverse Linked List II
 问题：逆转一个链表，从m到n的位置，一次性就地完成。
 例如：1->2->3->4->5->nullptr，m＝2，n＝4. 返回1->4->3->2->5->nullptr
        m与n的范围为1到链表长度之间，且m小于等于n
  （最后增加通常到链表逆序）
 */
class ReverseLinkedListII {
public:
    ListNode *reverseLinkedList_m2n(ListNode *head, int m, int n)
    {
        ListNode dummy(-1);//定义一个头节点
//        ListNode *dummy = new ListNode(-1);//定义一个头节点指针
        dummy.next = head;//头节点的指针指向传入的链表头指针
//        dummy->next = head;
        
        ListNode *prev = &dummy;//创建一个移动（修改）指针指向头节点，并遍历找到需要修改的位置
        
        for (int i=0; i<m-1; i++) {//这里prev先找到修改位置节点的前一个节点作为第二个头节点，因为这里prev最早是指向dummy这个头节点的，而真正的链表是从head开始的，所以dummy相当于0的位置，故i从0开始
            prev = prev->next;
        }
        
        ListNode *const head2 = prev;//以需要修改的位置为第二头指针，它是指针常量，可以修改所指位置的内容
        prev = head2->next; //当前位置的前一个位置（相对于cur的前驱节点）
        ListNode *cur = prev->next;//指针操作的当前位置，通过prev的next得到
        for (int i=m; i<n; i++) {
            prev->next = cur->next; //总是从前驱节点开始操作，先让其前驱节点prev的next指向后继节点，用于最后让cur能移动到后即节点的位置；
            cur->next = head2->next;//然后逆序，让当前节点的next指向其前驱节点
            head2->next = cur;//让head2的next指向当前节点cur，也就是下一次操作时cur的前驱节点。
            cur = prev->next;//cur往后移的一位。（可以看到，每一步操作赋值号右边的值都是下一步操作赋值号左边的值）
        }
        return dummy.next;
    }
};

class ReverseLinkedList {
public:
    //头插法
    ListNode *reverseLinkedList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode new_head(-1);
        while (head) {
            ListNode *next = head->next;
            head->next = new_head.next;
            new_head.next = head;
            head = next;
        }
        return new_head.next;
    }
    
    //就地逆置法
    ListNode *reverseLinkedList1(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *new_head = nullptr;
        while (head) {
            ListNode *next = head->next;
            head->next = new_head;
            new_head = head;
            head = next;
        }
        return new_head;
    }
    
    //递归法
    ListNode *reverseList_recur(ListNode *head)
    {
        if (!(head->next) || !head) {//head是否已经遍历到最后一个节点
            return head;
        }
        ListNode *new_head = reverseList_recur(head->next);//递归找到最后一个节点，作为新的头节点
        head->next->next = head;//因为是递归函数的原因，刚好从后往前开始逆序，让当前节点的下一个节点指针域指向向当前节点，完成逆序
        head->next = nullptr;//当前节点指针域指向空
        return new_head;
    }
};


/*
 2.2.3：Partition List
 问题：给定一个单链表，一个值x，将链表分成两个部分，前半部分值小于x，后半部分大于等于x，并且保持每个数原来的次序
 例如：1->4->3->2->5->2，x＝3，则返回1->2->2->4->3->5
 */
class PartitionList {
public:
    //time：O（n）
    ListNode *partitionList(ListNode *head, int x)
    {
        ListNode *p = head;
        ListNode *prev = p;//当前操作节点的前驱
        bool isFirst = true;//第一个元素是否大于等于x
        while (p && prev->next) { //遍历链表，将小于x的数一个个插入到前面去
            if (p->val < x) {
                while (prev->next->val >= x) {//找到第一个小于x的前驱节点
                    prev = prev->next;
                }
                ListNode *cur = prev->next;//小于x的节点作为cur
                prev->next = cur->next;
                cur->next = p->next;
                p->next = cur;
                
                p = p->next;
            } else {
                while (prev->next->val >= x) {
                    prev = prev->next;
                }
                ListNode *cur = prev->next;
                prev->next = cur->next;
                cur->next = p;
                p = cur;
                if (isFirst) {
                    head = p;//将第一个元素更新后将isFirst置成false
                    isFirst = false;
                }
            }
        }
        return head;
    }
    
    ListNode *partitionList_ver2(ListNode *head, int x)
    {
        //定义两个头节点，扫描链表，将值小于x的节点存入第一个头节点后，大于等于x的存入第二个头节点后。最后将第一个两个链表链接起来
        ListNode left_dummy(-1);//head node
        ListNode right_dummy(-1);//head node
        auto left_cur = &left_dummy;
        auto right_cur = &right_dummy;
        
        for (ListNode *cur=head; cur; cur=cur->next) {
            if (cur->val < x) {
                left_cur->next = cur;
                left_cur = cur;
            } else {
                right_cur->next = cur;
                right_cur = cur;
            }
        }
        left_cur->next = right_dummy.next;
        right_cur->next = nullptr;
        return left_dummy.next;
    }
};


/*
 2.2.4：Remove Duplicate from sorted list
 问题：删除有序链表里的多余元素。
 例如：1->1->2 返回 1->2
 */
class RemoveDuplicateFromSortedList {
public:
    // 迭代版
    ListNode *removeDuplicate(ListNode *head)
    {
        if (!head) {
            return nullptr;
        }
        for (ListNode *prev=head, *cur=head->next; cur; cur=prev->next) {
            if (prev->val == cur->val) {
                prev->next = cur->next;
                delete cur;
            } else {
                prev = cur;
            }
        }
        return head;
    }
    
    // 递归版
    ListNode *removeDuplicate_recur_ver(ListNode *head)
    {
        if (!head) {
            return head;
        }
        ListNode dummy(head->val+1); //only require different value from head
        dummy.next = head;
        recurr(&dummy, head);
        return dummy.next;
    }
private:
    static void recurr(ListNode *prev, ListNode *cur)// 递归函数的作用是删除cur这个重复节点
    {
        if (!cur) {
            return;
        }
        if (prev->val == cur->val) {
            prev->next = cur->next;
            delete cur;
            recurr(prev, prev->next);// 当存在重复节点时，要删除prev->next
        } else {
            recurr(prev->next, cur->next);
        }
    }
};


/*
 2.2.5：Remove Duplicate from sorted list II
 问题：删除有序链表中存在的两个以上的元素。
 例如：1->1->1->2->3 返回 2->3； 2 3 4 4 5 5 返回 2－》3
 */
class RemoveDuplicateFromSortedListII {
public:
    // 迭代版
    ListNode *removeDuplicated2(ListNode *head)
    {
        if (!head) {
            return nullptr;
        }
        ListNode dummy(-1);//head node
        dummy.next = head;
        ListNode *prev = &dummy, *cur = head;
        while (cur != nullptr) {
            bool duplicated = false;//用于判断是否存在重复
            while (cur->next != nullptr && cur->val == cur->next->val) {
                duplicated = true;
                ListNode *tmp = cur;
                cur = cur->next;
                delete tmp;
            }
            if (duplicated) {//delete last same element
                ListNode *tmp = cur;
                cur = cur->next;
                delete tmp;
                continue;
            }
            prev->next = cur;
            cur = cur->next;
            prev = prev->next;
        }
        prev->next = cur;//循环退出时cur指向null，故prev为最后一个元素，所以其next指针指向null
        return dummy.next;
    }
    
    
    // 递归版
    ListNode *removeDuplicated2_recurr_ver(ListNode *head)
    {
        if (!head || !head->next) {//递归结束条件
            return head;
        }
        ListNode *p = head->next; //第二个节点指针
        if (head->val == p->val) {//若第一个节点值等于第二个
            while (p && head->val == p->val) {//用p找到与head不等的节点，同时删除这些相同节点
                ListNode *tmp = p;
                p = p->next;
                delete tmp;
            }
            delete head; //删除第一个相同的节点
            return removeDuplicated2_recurr_ver(p);//递归返回剩下的内容，p为头节点的子序列进行递归操作
        } else {//若第一个节点值不等于第二个，递归返回头节点之后的内容
            head->next = removeDuplicated2_recurr_ver(head->next);
            return head;
        }
    }
};

