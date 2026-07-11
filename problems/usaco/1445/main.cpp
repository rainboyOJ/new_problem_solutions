/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:38
 * update_at: 2026-07-11 15:41
 */
#include <bits/stdc++.h>
using namespace std;

const int C = 26;

int n, f;
string s;
int occ[C][C];       // occ[a][b] 表示当前字符串中 abb 的出现次数。
bool possible[C][C]; // possible[a][b] 表示 abb 可能是答案。

bool is_moo_at(int pos) {
    if (pos < 0 || pos + 2 >= n) return false;
    if (s[pos] == s[pos + 1]) return false;
    if (s[pos + 1] != s[pos + 2]) return false;
    return true;
}

void update_at(int pos, int delta) {
    if (!is_moo_at(pos)) return;

    int a = s[pos] - 'a';
    int b = s[pos + 1] - 'a';

    occ[a][b] += delta;
    if (occ[a][b] >= f) {
        possible[a][b] = true;
    }
}

void update_around(int pos, int delta) {
    // 修改 pos 只会影响以 pos-2、pos-1、pos 开始的三个长度为 3 的子串。
    update_at(pos - 2, delta);
    update_at(pos - 1, delta);
    update_at(pos, delta);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> f;
    cin >> s;

    for (int i = 0; i + 2 < n; i++) {
        update_at(i, 1);
    }

    for (int i = 0; i < n; i++) {
        char old = s[i];

        update_around(i, -1);
        for (char c = 'a'; c <= 'z'; c++) {
            s[i] = c;
            update_around(i, 1);
            update_around(i, -1);
        }
        s[i] = old;
        update_around(i, 1);
    }

    int total = 0;
    for (int a = 0; a < C; a++) {
        for (int b = 0; b < C; b++) {
            if (a != b && possible[a][b]) total++;
        }
    }

    cout << total << '\n';
    for (int a = 0; a < C; a++) {
        for (int b = 0; b < C; b++) {
            if (a == b || !possible[a][b]) continue;
            cout << char('a' + a) << char('a' + b) << char('a' + b) << '\n';
        }
    }

    return 0;
}
