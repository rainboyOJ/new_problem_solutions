#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 按题意逐个插入 BST，适合小数据验证与教学理解。
void insert_node(Node *root, int x, int depth, int &max_depth) {
    max_depth = max(max_depth, depth);
    if (x < root->val) {
        if (root->left == nullptr) {
            root->left = new Node(x);
            max_depth = max(max_depth, depth + 1);
            return;
        }
        insert_node(root->left, x, depth + 1, max_depth);
    } else {
        if (root->right == nullptr) {
            root->right = new Node(x);
            max_depth = max(max_depth, depth + 1);
            return;
        }
        insert_node(root->right, x, depth + 1, max_depth);
    }
}

void postorder(Node *node, vector<int> &ans) {
    if (node == nullptr) {
        return;
    }
    postorder(node->left, ans);
    postorder(node->right, ans);
    ans.push_back(node->val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    Node *root = new Node(a[1]);
    int max_depth = 1;
    for (int i = 2; i <= n; ++i) {
        insert_node(root, a[i], 1, max_depth);
    }

    vector<int> ans;
    postorder(root, ans);

    cout << "deep=" << max_depth << '\n';
    for (int x : ans) {
        cout << x << '\n';
    }
    return 0;
}
