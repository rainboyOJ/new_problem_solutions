#include <bits/stdc++.h>
using namespace std;

struct Node {
    char val;
    Node *left;
    Node *right;
    Node(char c) : val(c), left(nullptr), right(nullptr) {}
};

// 直接按定义切字符串建树，适合小数据验证与教学理解。
Node* build(const string &inorder_str, const string &preorder_str) {
    if (inorder_str.empty()) {
        return nullptr;
    }

    char root = preorder_str[0];
    int mid = (int)inorder_str.find(root);
    Node *node = new Node(root);

    string left_in = inorder_str.substr(0, mid);
    string right_in = inorder_str.substr(mid + 1);
    string left_pre = preorder_str.substr(1, left_in.size());
    string right_pre = preorder_str.substr(1 + left_in.size());

    node->left = build(left_in, left_pre);
    node->right = build(right_in, right_pre);
    return node;
}

void postorder(Node *node, string &ans) {
    if (node == nullptr) {
        return;
    }
    // 后序遍历：左、右、根。
    postorder(node->left, ans);
    postorder(node->right, ans);
    ans.push_back(node->val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string inorder_str, preorder_str;
    cin >> inorder_str >> preorder_str;

    Node *root = build(inorder_str, preorder_str);
    string ans;
    postorder(root, ans);
    cout << ans << '\n';
    return 0;
}
