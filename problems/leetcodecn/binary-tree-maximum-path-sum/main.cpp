#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} };
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        function<int(TreeNode*)> dfs = [&](TreeNode* r) {
            if (!r) return 0;
            int l = max(0, dfs(r->left)), rd = max(0, dfs(r->right));
            ans = max(ans, l + rd + r->val);
            return max(l, rd) + r->val;
        };
        dfs(root);
        return ans;
    }
};
TreeNode* build(istream& in, int n) {
    vector<TreeNode*> nodes(n); queue<TreeNode*> q;
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
    cout << Solution().maxPathSum(r) << '\n';
    return 0;
}
