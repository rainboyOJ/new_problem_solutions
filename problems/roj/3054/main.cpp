/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:52
 * update_at: 2026-10-06 16:52
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;              // A 串长度上限
const int MAXM = 200005;              // B 串长度上限
const int MAXS = MAXN + MAXM + 5;     // 拼接串长度上限：B + 分隔符 + A

typedef long long ll;

ll n, m, q;
char A[MAXN];       // 被匹配的文本串
char B[MAXM];       // 模式串
char s[MAXS];       // 拼接串 s = B + 分隔符 + A，下标从 1 开始
int z[MAXS];        // z[i] 表示 s 与 s[i..] 的最长公共前缀长度
int hit[MAXM];      // hit[len] 表示匹配长度恰好为 len 的后缀个数

// 计算 s[1..len] 的 Z 数组，均摊 O(len)。
void z_function(int len) {
    z[1] = 0;
    int left = 1, right = 1; // 当前右端最靠后的匹配段 [left, right)
    for (int i = 2; i <= len; i++) {
        if (i < right) {
            // 借用左侧对称位置的答案，并截断到已知段的右端
            z[i] = min(right - i, z[i - left + 1]);
        }
        // 从下界继续往右逐字符比较
        while (i + z[i] <= len && s[z[i] + 1] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    cin >> (A + 1);
    cin >> (B + 1);

    // 拼接：s[1..m] 放 B，s[m+1] 放分隔符，s[m+2..m+1+n] 放 A
    for (int i = 1; i <= m; i++) {
        s[i] = B[i];
    }
    s[m + 1] = 'z' + 1; // 大于所有小写字母，保证匹配不会跨过分隔符
    for (int i = 1; i <= n; i++) {
        s[m + 1 + i] = A[i];
    }
    z_function(m + 1 + n);

    // A 的起点 i 在 s 中的下标是 m+1+i，其 z 值就是它与 B 的最长公共前缀
    for (int i = 1; i <= n; i++) {
        hit[z[m + 1 + i]]++;
    }

    // 每个询问 O(1) 回答；匹配长度不会超过 M
    for (int i = 1; i <= q; i++) {
        ll x;
        cin >> x;
        if (x >= 0 && x <= m) {
            cout << hit[x] << '\n';
        } else {
            cout << 0 << '\n';
        }
    }

    return 0;
}
