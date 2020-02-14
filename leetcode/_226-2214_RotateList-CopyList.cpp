//
//  _226-2210_RotateList-CopyList.cpp
//  LeetCode
//
//  Created by chizhejian on 11/26/19.
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
 2.2.6：Rotate List
 问题：给一个链表，将后面k个节点移动到前面，k非负
 例如：1->2->3->4->5->null，k＝2，返回4->5->1->2->3->null
 */
class RotateList {
public:
    ListNode *rotateList(ListNode *head, int k)
    {
        if (head==nullptr || k == 0) {
            return head;
        }
        ListNode *p = head;
        int countn = 1;//用于统计节点个数
        while (p->next) {
            countn++;
            p = p->next;
        }
        
        k = countn - k % countn;//计算出从头需要遍历几个节点
        p->next = head;//首位相连形成循环链表
        for (int i=0; i<k; i++) {
            p = p->next;
        }
        head = p->next;//找到断开位置p后，新的头节点就是p的后继
        p->next = nullptr;//断开
        return head;
    }
};

/*
 2.2.7：Remove Nth Node from end of list
 问题：删除链表从后往前数的第n个节点
 例如：1->2->3->4->5，n＝2，返回1->2->3->5
 */
class RemoveNthNode {
public:
    ListNode *removeNthNode(ListNode *head, int n)
    {
        if (head) {
            return head;
        }
        ListNode *p1 = head;
        ListNode *p2 = head;
        for (int i=0; i<n; i++) {
            p1 = p1->next;
        }
        while (p1->next) {
            p1 = p1->next;
            p2 = p2->next;
        }
        ListNode *tmp = p2->next;
        p2->next = p2->next->next;
        tmp->next =nullptr;
        delete tmp;
        return head;
    }
};

/*
 2.2.8：swap nodes in pairs
 问题：给一个链表，交换两个连续的节点
 例如：1->2->3->4，返回2->1->4->3
 要去使用常数的空间，不能改变节点内部的值，只能移动节点
 */
class SwapNodeInPairs {
public:
    ListNode *swapNodes(ListNode *head)
    {
        if (!head || !head->next) {
            return head;
        }
        ListNode dummy(-1);
        dummy.next = head;
        for (ListNode *prev=&dummy, *cur=prev->next, *next=cur->next; next;
             prev=cur, cur=cur->next, next = cur?cur->next:nullptr) {
            prev->next = next;
            cur->next = next->next;
            next->next = cur;
        }
        return dummy.next;
    }
};

/*
 2.2.9：reverse node in k-group
 问题：
 例如：->
 */


/*
 2.2.10：
 问题：
 例如：->
 */


/*
 2.2.11：
 问题：单链表是否有环
 例如：->
 */
class LinkedListCircle {
public:
    bool hasCircle(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head;
        bool hasCircle = false;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCircle = true;
            }
        }
        return hasCircle;
    }
};


/*
 2.2.12：
 问题：找环的入口点
 例如：->
 */
class FindEntryOfCircle{
public:
    ListNode* findEntry(ListNode* head)
    {
        ListNode* slow1 = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow1 = slow1->next;
            fast = fast->next->next;
            if (slow1 == fast) {
                ListNode* slow2 = head;
                while (slow1 != slow2) {
                    slow1 = slow1->next;
                    slow2 = slow2->next;
                }
                return slow2;
            }
        }
        return nullptr;
    }
};

/*
 2.2.13：
 问题：reorder list
 例如：1 2 3 4 5 -> 1 5 2 4 3
     6 8 5 1 -> 6 1 8 5
 */
class ReorderList {
public:
    void reorderList(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        
        ListNode* prev = nullptr, *slow = head, *fast = head;
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        prev->next = nullptr; // cut in middle
        
        slow = reverseList(slow);
        
        // merge two list
        ListNode* cur = head;
        while (cur->next) {
            ListNode* tmp = cur->next;
            cur->next = slow;
            slow = slow->next;
            cur->next->next = tmp;
            cur = tmp;
        }
        cur->next = slow;
    }
    
    ListNode* reverseList(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        ListNode* prev = reverseList(head->next);
        prev->next->next = prev;
        return prev;
    }
};


/*
 2.2.14：
 问题：
 例如：->
 */
