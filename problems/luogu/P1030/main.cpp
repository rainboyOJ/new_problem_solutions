#include <bits/stdc++.h>
using namespace std;

static string inorder_str;
static string postorder_str;
static string preorder_str;
static int pos[256];

// 在后序和中序的对应区间内递归输出先序遍历。
void solve(int post_l, int post_r, int in_l, int in_r) {
    if (post_l > post_r) {
        return;
    }

    char root = postorder_str[post_r];
    int mid = pos[(unsigned char)root];
    int left_size = mid - in_l;

    // 先序遍历顺序是根、左、右。
    preorder_str.push_back(root);
    solve(post_l, post_l + left_size - 1, in_l, mid - 1);
    solve(post_l + left_size, post_r - 1, mid + 1, in_r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> inorder_str >> postorder_str;
    for (int i = 0; i < (int)inorder_str.size(); ++i) {
        // 记录每个字符在中序遍历中的位置，方便 O(1) 切分左右子树。
        pos[(unsigned char)inorder_str[i]] = i;
    }

    solve(0, (int)postorder_str.size() - 1, 0, (int)inorder_str.size() - 1);
    cout << preorder_str << '\n';
    return 0;
}
