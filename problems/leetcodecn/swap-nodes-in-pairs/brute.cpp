/**
 * Author by Rainboy
 */
// brute.cpp = main.cpp（无更简单基线）
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode dummy(0);
        dummy.next = head;
        auto prev = &dummy;
        while (prev->next && prev->next->next) {
            auto a = prev->next, b = a->next;
            a->next = b->next;
            b->next = a;
            prev->next = b;
            prev = a;
        }
        return dummy.next;
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
    int n;
    cin >> n;
    auto head = build(cin, n);
    head = Solution().swapPairs(head);
    for (auto p = head; p; p = p->next)
        cout << p->val << ' ';
    return 0;
}
