/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:30
 * update_at: 2026-10-06 16:30
 */
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

char s[1005]; // 每组输入串，长度不超过 1000

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        int n = strlen(s);
        int cnt1 = 0; // 1 的个数
        for (int i = 0; i < n; ++i)
            if (s[i] == '1') ++cnt1;
        // 每合并一次 1 的个数奇偶翻转，合并 n-1 次后末位为圆当且仅当 cnt1 + n - 1 为偶数
        if ((cnt1 + n - 1) % 2 == 0)
            cout << "Win\n";
        else
            cout << "Lost\n";
    }
    return 0;
}
