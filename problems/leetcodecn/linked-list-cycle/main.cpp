/**
 * Author by Rainboy
 */
// main.cpp：Floyd 快慢指针，O(n) O(1)。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        auto slow = head, fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
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
    cout << Solution().hasCycle(head) << '\n';
    return 0;
}
