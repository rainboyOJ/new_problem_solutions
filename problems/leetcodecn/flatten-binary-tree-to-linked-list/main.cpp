#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* prev = nullptr;
        function<void(TreeNode*)> dfs = [&](TreeNode* r) {
            if (!r) return;
            dfs(r->right); dfs(r->left);
            r->right = prev; r->left = nullptr;
            prev = r;
        };
        dfs(root);
    }
};
TreeNode* build(istream& in, int n) { /* same as before */ vector<TreeNode*> nodes(n); queue<TreeNode*> q;
    for (int i = 0, v; i < n; i++) { in >> v; if (v != -1) nodes[i] = new TreeNode(v); }
    TreeNode* root = nodes[0]; if (root) q.push(root); int idx = 1;
    while (!q.empty() && idx < n) { auto cur = q.front(); q.pop();
        if (idx < n) { cur->left = nodes[idx]; if (nodes[idx]) q.push(nodes[idx]); idx++; }
        if (idx < n) { cur->right = nodes[idx]; if (nodes[idx]) q.push(nodes[idx]); idx++; }
    } return root;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; auto r = build(cin, n);
    Solution().flatten(r);
    for (auto p = r; p; p = p->right) cout << p->val << ' ';
    return 0;
}
