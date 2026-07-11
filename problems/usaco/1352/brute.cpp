/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:10
 * update_at: 2026-07-11 21:13
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int target_count, command_count;
set<int> targets;
string cmd;

int simulate(string s) {
    int pos = 0;
    set<int> hit;

    for (int i = 0; i < command_count; i++) {
        if (s[i] == 'L') {
            pos--;
        } else if (s[i] == 'R') {
            pos++;
        } else {
            if (targets.count(pos)) {
                hit.insert(pos);
            }
        }
    }

    return (int)hit.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target_count >> command_count;
    for (int i = 1; i <= target_count; i++) {
        int x;
        cin >> x;
        targets.insert(x);
    }
    cin >> cmd;

    int ans = simulate(cmd);
    char choices[3] = {'L', 'F', 'R'};

    for (int i = 0; i < command_count; i++) {
        char old = cmd[i];
        for (int j = 0; j < 3; j++) {
            if (choices[j] == old) continue;
            cmd[i] = choices[j];
            ans = max(ans, simulate(cmd));
        }
        cmd[i] = old;
    }

    cout << ans << '\n';

    return 0;
}
