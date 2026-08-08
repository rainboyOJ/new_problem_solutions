#include <bits/stdc++.h>
using namespace std;

static string bits;

struct Node {
    char type;
    Node *left;
    Node *right;

    Node(char type_) : type(type_), left(nullptr), right(nullptr) {}
};

// 直接扫描区间，按定义判断这个子串对应的结点类型。
char segment_type(int l, int r) {
    bool has_zero = false;
    bool has_one = false;
    for (int i = l; i <= r; ++i) {
        if (bits[i - 1] == '0') {
            has_zero = true;
        } else {
            has_one = true;
        }
    }

    if (has_zero && has_one) {
        return 'F';
    }
    if (has_zero) {
        return 'B';
    }
    return 'I';
}

// 按题意显式建出整棵树，更适合教学理解与小数据对拍。
Node* build(int l, int r) {
    Node *node = new Node(segment_type(l, r));
    if (l == r) {
        return node;
    }

    int mid = (l + r) >> 1;
    node->left = build(l, mid);
    node->right = build(mid + 1, r);
    return node;
}

void postorder(Node *node) {
    if (node == nullptr) {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    cout << node->type;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> bits;
    int m = 1 << n;

    Node *root = build(1, m);
    postorder(root);
    cout << '\n';
    return 0;
}
