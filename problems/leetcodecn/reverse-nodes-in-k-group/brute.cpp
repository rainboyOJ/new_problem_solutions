/**
 * Author by Rainboy
 */
// brute.cpp：递归分组版。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        auto cur = head;
        for (int i = 0; i < k; i++) {
            if (!cur)
                return head;
            cur = cur->next;
        }
        auto prev = reverseKGroup(cur, k);
        cur = head;
        for (int i = 0; i < k; i++) {
            auto nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }
        return prev;
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
    int n, k;
    cin >> n >> k;
    auto head = build(cin, n);
    head = Solution().reverseKGroup(head, k);
    for (auto p = head; p; p = p->next)
        cout << p->val << ' ';
    return 0;
}
