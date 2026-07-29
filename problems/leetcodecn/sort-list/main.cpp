/**
 * Author by Rainboy
 */
// main.cpp：快慢指针拆半，递归归并 O(n log n) O(log n)。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (!head || !head->next)
            return head;
        auto slow = head, fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        auto mid = slow->next;
        slow->next = nullptr;
        auto l = sortList(head), r = sortList(mid);
        ListNode dummy(0), *cur = &dummy;
        while (l && r) {
            if (l->val < r->val) {
                cur->next = l;
                l = l->next;
            } else {
                cur->next = r;
                r = r->next;
            }
            cur = cur->next;
        }
        cur->next = l ? l : r;
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
    head = Solution().sortList(head);
    for (auto p = head; p; p = p->next)
        cout << p->val << ' ';
    return 0;
}
