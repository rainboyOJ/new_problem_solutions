/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:25
 * update_at: 2026-10-05 02:25
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1000005;

ll a[MAXN]; // 输入数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int best = 0; // 最长平台长度
    int run = 0;  // 以当前元素结尾的平台长度
    for (int i = 1; i <= n; ++i) {
        if (i > 1 && a[i] == a[i - 1]) {
            run = run + 1;
        } else {
            run = 1;
        }
        if (run > best) {
            best = run;
        }
    }

    cout << best << '\n';
    return 0;
}
