#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        function<bool(TreeNode*,long,long)> dfs = [&](TreeNode* r, long lo, long hi) {
            if (!r) return true;
            if (r->val <= lo || r->val >= hi) return false;
            return dfs(r->left, lo, r->val) && dfs(r->right, r->val, hi);
        };
        return dfs(root, LONG_MIN, LONG_MAX);
    }
};
TreeNode* build(istream& in, int n) {
    if (!n) return nullptr;
    vector<TreeNode*> nodes(n); queue<TreeNode*> q;
    for (int i = 0, v; i < n; i++) { in >> v; if (v != -1) nodes[i] = new TreeNode(v); }
    TreeNode* root = nodes[0]; if (root) q.push(root); int idx = 1;
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
    cout << Solution().isValidBST(r) << '\n';
    return 0;
}
