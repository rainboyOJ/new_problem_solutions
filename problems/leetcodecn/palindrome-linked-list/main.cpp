/**
 * Author by Rainboy
 */
// main.cpp：快慢指针找中点，反转后半段，比较。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        auto slow = head, fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        auto mid = slow->next;
        slow->next = nullptr;
        ListNode *prev = nullptr;
        while (mid) { auto nxt = mid->next; mid->next = prev; prev = mid; mid = nxt; }
        auto a = head, b = prev;
        while (b) {
            if (a->val != b->val) return false;
            a = a->next; b = b->next;
        }
        return true;
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
    cout << Solution().isPalindrome(head) << '\n';
    return 0;
}
