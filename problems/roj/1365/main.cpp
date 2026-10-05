/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-05 12:07
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 1 << 10; // N <= 10，最大长度 1024

char s[MAXN + 5]; // 输入的 01 串

// 判断子串 s[l..r-1] 的结点类型：全 0 为 B，全 1 为 I，否则为 F
char node_kind(int l, int r) {
    bool has0 = false, has1 = false;
    for (int i = l; i < r; ++i) {
        if (s[i] == '0') has0 = true;
        else has1 = true;
        if (has0 && has1) return 'F';
    }
    if (has0) return 'B';
    return 'I';
}

// 递归返回子串 s[l..r-1] 对应 FBI 树的后序遍历序列
string postorder(int l, int r) {
    if (r - l == 1) {
        return string(1, node_kind(l, r));
    }
    int mid = (l + r) >> 1;
    return postorder(l, mid) + postorder(mid, r) + node_kind(l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> s;
    int len = 1 << n; // 2^N
    cout << postorder(0, len) << '\n';
    return 0;
}
