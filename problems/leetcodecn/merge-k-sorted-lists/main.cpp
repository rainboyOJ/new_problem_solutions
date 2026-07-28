/**
 * Author by Rainboy
 */
// main.cpp：小根堆 O(N log K)。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        for (auto h : lists) if (h) pq.push(h);
        ListNode dummy(0), *cur = &dummy;
        while (!pq.empty()) {
            auto node = pq.top(); pq.pop();
            cur->next = node;
            cur = cur->next;
            if (node->next) pq.push(node->next);
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
    int k; cin >> k;
    vector<ListNode*> lists(k);
    for (int i = 0; i < k; i++) {
        int n; cin >> n;
        lists[i] = build(cin, n);
    }
    auto head = Solution().mergeKLists(lists);
    for (auto p = head; p; p = p->next) cout << p->val << ' ';
    return 0;
}
