/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:15
 * update_at: 2026-11-11 01:15
 */

// brute.cpp：小数据验证基线
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string c, p, q;
    if (!(cin >> c >> p >> q)) return 0;

    map<char, char> c2p, p2c;
    for (size_t i = 0; i < c.size(); ++i) {
        if (c2p.count(c[i]) && c2p[c[i]] != p[i]) {
            cout << "Failed\n";
            return 0;
        }
        if (p2c.count(p[i]) && p2c[p[i]] != c[i]) {
            cout << "Failed\n";
            return 0;
        }
        c2p[c[i]] = p[i];
        p2c[p[i]] = c[i];
    }

    if (p2c.size() < 26) {
        cout << "Failed\n";
        return 0;
    }

    string res = "";
    for (char ch : q) res += c2p[ch];
    cout << res << "\n";
    return 0;
}
