#include <bits/stdc++.h>
using namespace std;

static string inorder_str;
static string preorder_str;
static string postorder_str;
static int pos[256];

// 在前序和中序的对应区间内递归输出后序遍历。
void solve(int pre_l, int pre_r, int in_l, int in_r) {
    if (pre_l > pre_r) {
        return;
    }

    char root = preorder_str[pre_l];
    int mid = pos[(unsigned char)root];
    int left_size = mid - in_l;

    // 后序遍历顺序是左、右、根。
    solve(pre_l + 1, pre_l + left_size, in_l, mid - 1);
    solve(pre_l + left_size + 1, pre_r, mid + 1, in_r);
    postorder_str.push_back(root);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> inorder_str >> preorder_str;
    for (int i = 0; i < (int)inorder_str.size(); ++i) {
        // 记录每个字符在中序遍历中的位置，方便 O(1) 切分左右子树。
        pos[(unsigned char)inorder_str[i]] = i;
    }

    solve(0, (int)preorder_str.size() - 1, 0, (int)inorder_str.size() - 1);
    cout << postorder_str << '\n';
    return 0;
}
