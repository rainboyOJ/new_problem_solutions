/**
 * Author by Rainboy
 */
// main.cpp：先找第 k 个节点，翻转这一段并接回；不足 k 段保持原样。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;
        auto prev = &dummy;
        while (true) {
            auto end = prev;
            for (int i = 0; i < k && end; i++) end = end->next;
            if (!end) break;
            auto start = prev->next, nxt = end->next;
            auto a = start, b = a->next;
            while (b != nxt) {
                auto c = b->next;
                b->next = a;
                a = b;
                b = c;
            }
            start->next = nxt;
            prev->next = a;
            prev = start;
        }
        return dummy.next;
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
    int n, k; cin >> n >> k;
    auto head = build(cin, n);
    head = Solution().reverseKGroup(head, k);
    for (auto p = head; p; p = p->next) cout << p->val << ' ';
    return 0;
}
