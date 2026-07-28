/**
 * Author by Rainboy
 */
// main.cpp：三指针迭代反转 O(n) O(1)。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr, *cur = head;
        while (cur) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
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
    head = Solution().reverseList(head);
    for (auto p = head; p; p = p->next) cout << p->val << ' ';
    return 0;
}
