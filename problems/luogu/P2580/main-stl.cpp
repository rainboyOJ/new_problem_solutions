/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 01:15
 * update_at: 2026-10-07 01:20
 */
// 这是 STL 写法：用 map<string, int> 建立“姓名 -> 状态”的对照表。
// 状态含义：1 表示在名单里且还没被点到，2 表示已经被点到过；
// 查询用 find，不用 state[name]，因为下标访问会把没见过的姓名插进表里，
// 那样就分不清“不在名单”和“在名单但没点过”。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<string, int> state; // state[name] 表示姓名 name 的状态：1 未点名，2 已点名

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        string name;
        cin >> name;
        state[name] = 1; // 名单里的姓名统一记成“未点名”
    }

    ll m;
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        string name;
        cin >> name;

        // find 只查询、不插入：返回 end() 就说明这个名字根本不在名单里
        auto it = state.find(name);
        if (it == state.end()) {
            cout << "WRONG\n";
        } else if (it->second == 1) {
            it->second = 2; // 第一次点到合法姓名，标记成已点名
            cout << "OK\n";
        } else {
            cout << "REPEAT\n";
        }
    }

    return 0;
}
