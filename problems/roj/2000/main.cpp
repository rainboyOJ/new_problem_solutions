/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:04
 * update_at: 2026-10-06 02:04
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const ll MOD = 47;

// 计算名字所有字母对应数值（A=1..Z=26）的乘积模 47
ll name_score(const string &s) {
    ll res = 1;
    for (ll i = 0; i < (ll)s.size(); ++i) {
        res = (res * (s[i] - 'A' + 1)) % MOD;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;

    if (name_score(s1) == name_score(s2))
        cout << "GO\n";
    else
        cout << "STAY\n";

    return 0;
}
