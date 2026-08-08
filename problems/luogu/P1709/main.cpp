#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000005;

int n;
char s[MAXN];     // 原字符串
char t[MAXN * 2]; // 把字符串复制一遍，方便按区间比较循环位移

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    for (int i = 0; i < n; i++) {
        t[i] = s[i];
        t[i + n] = s[i];
    }
    t[n + n] = '\0';

    int i = 0; // 当前第一个候选起点
    int j = 1; // 当前第二个候选起点
    int k = 0; // 已经比较过的公共前缀长度

    // 最小表示法：
    // 比较从 i 和 j 开始的两个循环串，淘汰较大的那个起点。
    while (i < n && j < n && k < n) {
        if (t[i + k] == t[j + k]) {
            k++;
            continue;
        }

        if (t[i + k] > t[j + k]) {
            // 以 i 开头的串更大，那么 [i, i + k] 这些起点都不可能更优。
            i = i + k + 1;
            if (i == j) {
                i++;
            }
        } else {
            // 同理，淘汰以 j 为起点的一段候选。
            j = j + k + 1;
            if (i == j) {
                j++;
            }
        }
        // 重新比较新的两个候选。
        k = 0;
    }

    cout << min(i, j) << '\n';
    return 0;
}
