/**
 * Author by Rainboy
 */
// main.cpp：相遇后从头和相遇点各走一步，第二次相遇即入环点。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        auto slow = head, fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                slow = head;
                while (slow != fast) { slow = slow->next; fast = fast->next; }
                return slow;
            }
        }
        return nullptr;
    }
};

ListNode* build(istream& in, int n) {
    if (!n) return nullptr;
    auto head = new ListNode(0), cur = head;
    for (int i = 0, v; i < n; i++) { in >> v; cur->next = new ListNode(v); cur = cur->next; }
    return head->next;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    auto head = build(cin, n);
    auto ans = Solution().detectCycle(head);
    cout << (ans ? ans->val : -1) << '\n';
    return 0;
}
