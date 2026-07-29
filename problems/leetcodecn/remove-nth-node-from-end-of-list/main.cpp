/**
 * Author by Rainboy
 */
// main.cpp：dummy + 快慢指针相距 n+1，快到尾时慢在待删前一位。
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
        ListNode dummy(0);
        dummy.next = head;
        auto fast = &dummy, slow = &dummy;
        for (int i = 0; i < n; i++)
            fast = fast->next;
        while (fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
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
    int len, n;
    cin >> len >> n;
    auto head = build(cin, len);
    head = Solution().removeNthFromEnd(head, n);
    for (auto p = head; p; p = p->next)
        cout << p->val << ' ';
    return 0;
}
