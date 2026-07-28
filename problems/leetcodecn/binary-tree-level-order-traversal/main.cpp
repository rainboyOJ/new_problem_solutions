#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> ans;
        queue<TreeNode*> q; q.push(root);
        while (!q.empty()) {
            ans.push_back({});
            for (int sz = q.size(); sz--; q.pop()) {
                auto cur = q.front();
                ans.back().push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
        return ans;
    }
};
TreeNode* build(istream& in, int n) {
    if (!n) return nullptr;
    vector<TreeNode*> nodes(n);
    for (int i = 0, v; i < n; i++) { in >> v; if (v != -1) nodes[i] = new TreeNode(v); }
    queue<TreeNode*> q; TreeNode* root = nodes[0];
    if (root) q.push(root);
    int idx = 1;
    while (!q.empty() && idx < n) {
        auto cur = q.front(); q.pop();
        if (idx < n) { cur->left = nodes[idx]; if (nodes[idx]) q.push(nodes[idx]); idx++; }
        if (idx < n) { cur->right = nodes[idx]; if (nodes[idx]) q.push(nodes[idx]); idx++; }
    }
    return root;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; auto r = build(cin, n);
    for (auto& v : Solution().levelOrder(r)) { for (int x : v) cout << x << ' '; cout << '\n'; }
    return 0;
}
