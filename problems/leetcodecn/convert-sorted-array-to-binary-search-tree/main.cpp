#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        function<TreeNode *(int, int)> build = [&](int l, int r) -> TreeNode * {
            if (l > r)
                return nullptr;
            int m = (l + r) / 2;
            TreeNode *root = new TreeNode(nums[m]);
            root->left = build(l, m - 1);
            root->right = build(m + 1, r);
            return root;
        };
        return build(0, nums.size() - 1);
    }
};

vector<int> inorder;

void dfs(TreeNode *r) {
    if (!r)
        return;
    dfs(r->left);
    inorder.push_back(r->val);
    dfs(r->right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    auto r = Solution().sortedArrayToBST(a);
    dfs(r);
    for (int x : inorder)
        cout << x << ' ';
    return 0;
}
