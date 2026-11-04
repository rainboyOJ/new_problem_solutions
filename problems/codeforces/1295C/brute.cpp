/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 19:35
 * update_at: 2026-11-04 19:42
 */
// brute.cpp：直接模拟每一趟——在 s 上从左到右扫一遍，尽量匹配 t 剩下的部分。
// 复杂度 O(|s| * 答案)，与 main.cpp 的算法思路相同，但找下一个字符是线性扫描。
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;

string s, t;

void sol(){
    cin >> s >> t;

    int ans = 0;
    int i = 0;                          // t 已匹配到的位置
    while (i < (int)t.size()) {
        ans++;
        int before = i;
        for (char ch : s) {             // 这一趟在 s 里尽量往后匹配
            if (i < (int)t.size() && ch == t[i])
                i++;
        }
        if (i == before) {              // 这一趟一个字符都没匹配上，永远做不到
            cout << -1 << "\n";
            return;
        }
    }
    cout << ans << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        sol();
    return 0;
}
