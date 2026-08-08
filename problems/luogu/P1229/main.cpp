#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string preorder, postorder;
    cin >> preorder >> postorder;

    int pos[256];
    memset(pos, -1, sizeof(pos));
    for (int i = 0; i < (int)postorder.size(); ++i) {
        pos[(unsigned char)postorder[i]] = i;
    }

    long long ans = 1;
    for (int i = 0; i + 1 < (int)preorder.size(); ++i) {
        // 如果前序里相邻的父子，在后序里也刚好反向相邻，
        // 说明这个父节点只有一个孩子，左右方向无法确定。
        if (pos[(unsigned char)preorder[i]] ==
            pos[(unsigned char)preorder[i + 1]] + 1) {
            ans *= 2;
        }
    }

    cout << ans << '\n';
    return 0;
}
