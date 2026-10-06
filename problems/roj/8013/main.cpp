/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:51
 * update_at: 2026-10-06 16:51
 */

#include <iostream>
using namespace std;

typedef long long ll;

ll v[3]; // 三个桶：0=D, 1=G, 2=Z，净额：正=欠别人，负=借给别人

// 把字母 D/G/Z 映射成下标 0/1/2
ll idx(char c) {
    if (c == 'D') return 0;
    if (c == 'G') return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    char a, b;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a >> b;
        v[idx(a)]++; // 欠账人净额 +1
        v[idx(b)]--; // 被欠人净额 -1
    }

    cout << "D " << v[0] << "\n";
    cout << "G " << v[1] << "\n";
    cout << "Z " << v[2] << "\n";
    return 0;
}
