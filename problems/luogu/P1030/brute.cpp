#include <bits/stdc++.h>
using namespace std;

struct Node {
    char val;
    Node *left;
    Node *right;
    Node(char c) : val(c), left(nullptr), right(nullptr) {}
};

// 直接按定义切字符串建树，适合小数据验证与教学理解。
Node* build(const string &inorder_str, const string &postorder_str) {
    if (inorder_str.empty()) {
        return nullptr;
    }

    char root = postorder_str.back();
    int mid = (int)inorder_str.find(root);
    Node *node = new Node(root);

    string left_in = inorder_str.substr(0, mid);
    string right_in = inorder_str.substr(mid + 1);
    string left_post = postorder_str.substr(0, left_in.size());
    string right_post = postorder_str.substr(left_in.size(), right_in.size());

    node->left = build(left_in, left_post);
    node->right = build(right_in, right_post);
    return node;
}

void preorder(Node *node, string &ans) {
    if (node == nullptr) {
        return;
    }
    // 先序遍历：根、左、右。
    ans.push_back(node->val);
    preorder(node->left, ans);
    preorder(node->right, ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string inorder_str, postorder_str;
    cin >> inorder_str >> postorder_str;

    Node *root = build(inorder_str, postorder_str);
    string ans;
    preorder(root, ans);
    cout << ans << '\n';
    return 0;
}
