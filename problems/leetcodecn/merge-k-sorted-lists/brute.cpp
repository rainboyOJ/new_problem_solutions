/**
 * Author by Rainboy
 */
// brute.cpp：分治两两合并。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    ListNode* mergeTwo(ListNode* a, ListNode* b) {
        ListNode dummy(0), *cur = &dummy;
        while (a && b) {
            if (a->val < b->val) { cur->next = a; a = a->next; }
            else { cur->next = b; b = b->next; }
            cur = cur->next;
        }
        cur->next = a ? a : b;
        return dummy.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        int n = lists.size();
        while (n > 1) {
            int idx = 0;
            for (int i = 0; i < n; i += 2) {
                if (i + 1 < n) lists[idx++] = mergeTwo(lists[i], lists[i + 1]);
                else lists[idx++] = lists[i];
            }
            n = idx;
        }
        return lists[0];
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
