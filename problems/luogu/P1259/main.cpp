/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n, cnt;
string states[100];

void dfs(int depth) {
    if (depth == 4) {
        string tail = "";
        for (int i = 0; i < n - 4; i++) tail += "o*";
        states[cnt++] = "oooo****--" + tail;
        states[cnt++] = "ooo--***o*" + tail;
        states[cnt++] = "ooo*o**--*" + tail;
        states[cnt++] = "o--*o**oo*" + tail;
        states[cnt++] = "o*o*o*--o*" + tail;
        states[cnt++] = "--o*o*o*o*" + tail;
        return;
    }
    string s = string(depth, 'o') + string(depth, '*') + "--";
    for (int i = 0; i < n - depth; i++) s += "o*";
    states[cnt++] = s;
    s = string(depth - 1, 'o') + "--" + string(depth - 1, '*');
    for (int i = 0; i < n - depth + 1; i++) s += "o*";
    states[cnt++] = s;
    dfs(depth - 1);
}

int main() {
    cin >> n;
    dfs(n);
    for (int i = 0; i < cnt; i++) cout << states[i] << endl;
    return 0;
}
