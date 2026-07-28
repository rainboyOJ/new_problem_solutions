/**
 * Author by Rainboy
 */
// brute.cpp：转换数组排序再重建。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        vector<int> v;
        for (auto p = head; p; p = p->next) v.push_back(p->val);
        sort(v.begin(), v.end());
        auto cur = head;
        for (int x : v) { cur->val = x; cur = cur->next; }
        return head;
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
    head = Solution().sortList(head);
    for (auto p = head; p; p = p->next) cout << p->val << ' ';
    return 0;
}
