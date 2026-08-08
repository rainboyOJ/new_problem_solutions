#include <bits/stdc++.h>
using namespace std;

static string preorder;
static string postorder;
static int post_pos[256];

long long solve(int pre_l, int pre_r, int post_l, int post_r) {
    int len = pre_r - pre_l + 1;
    if (len <= 1) {
        return 1;
    }

    char child_root = preorder[pre_l + 1];
    int child_pos = post_pos[(unsigned char)child_root];

    // 整个剩余区间都被一个孩子占满时，这个孩子可以是左也可以是右。
    if (child_pos == post_r - 1) {
        return 2LL * solve(pre_l + 1, pre_r, post_l, post_r - 1);
    }

    int left_len = child_pos - post_l + 1;
    long long left_ans =
        solve(pre_l + 1, pre_l + left_len, post_l, child_pos);
    long long right_ans =
        solve(pre_l + left_len + 1, pre_r, child_pos + 1, post_r - 1);
    return left_ans * right_ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> preorder >> postorder;
    memset(post_pos, -1, sizeof(post_pos));
    for (int i = 0; i < (int)postorder.size(); ++i) {
        post_pos[(unsigned char)postorder[i]] = i;
    }

    cout << solve(0, (int)preorder.size() - 1, 0,
                  (int)postorder.size() - 1)
         << '\n';
    return 0;
}
