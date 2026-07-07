// brute_01_style.cpp：01 序列风格暴力，按位置依次决定这个括号翻或不翻。
#include <bits/stdc++.h>
using namespace std;

string s, current_string;
int n;
int flip_pos[105]; // flip_pos[i] = 0/1，表示第 i 个位置不翻/翻
int answer;

bool is_valid() {
    int balance = 0;
    for (int i = 0; i < n; i++) {
        char ch = s[i];
        if (flip_pos[i] == 1) {
            ch = (ch == '(' ? ')' : '(');
        }
        if (ch == '(') {
            balance++;
        } else {
            balance--;
        }
        if (balance < 0) {
            return false;
        }
    }
    return balance == 0;
}

int calc_answer() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (flip_pos[i] == 1) cnt++;
    }
    return cnt;
}

void dfs_flip(int dep) {
    if (dep == n) {
        if (is_valid()) {
            int value = calc_answer();
            if (answer > value) answer = value;
        }
        return;
    }

    // 第 dep 个位置的 01 选择：0 不翻，1 翻。
    for (int i = 0; i <= 1; i++) {
        flip_pos[dep] = i;
        dfs_flip(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    n = (int)s.size();

    answer = n + 1;
    dfs_flip(0);

    cout << answer << '\n';
    return 0;
}
