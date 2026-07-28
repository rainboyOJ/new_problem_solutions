/**
 * Author by Rainboy
 */
// brute.cpp：遍历 A 每个节点，在 B 中查找 O(mn)。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        for (auto a = headA; a; a = a->next)
            for (auto b = headB; b; b = b->next)
                if (a == b) return a;
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
    int n, m; cin >> n >> m;
    auto a = build(cin, n), b = build(cin, m);
    auto ans = Solution().getIntersectionNode(a, b);
    cout << (ans ? ans->val : -1) << '\n';
    return 0;
}
