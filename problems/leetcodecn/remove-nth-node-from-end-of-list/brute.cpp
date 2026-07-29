/**
 * Author by Rainboy
 */
// brute.cpp：两次遍历，先求长度再删倒数第 n 个。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        int len = 0;
        for (auto p = head; p; p = p->next)
            len++;
        if (len == n)
            return head->next;
        auto cur = head;
        for (int i = 0; i < len - n - 1; i++)
            cur = cur->next;
        cur->next = cur->next->next;
        return head;
    }
};

ListNode *build(istream &in, int n) {
    if (!n)
        return nullptr;
    auto head = new ListNode(0), cur = head;
    for (int i = 0, v; i < n; i++) {
        in >> v;
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return head->next;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int len, n;
    cin >> len >> n;
    auto head = build(cin, len);
    head = Solution().removeNthFromEnd(head, n);
    for (auto p = head; p; p = p->next)
        cout << p->val << ' ';
    return 0;
}
