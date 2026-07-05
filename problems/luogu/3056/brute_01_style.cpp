// brute_01_style.cpp：01 序列风格暴力，按位置依次决定这个括号翻或不翻。
#include <bits/stdc++.h>
using namespace std;

string s, current_string;
int n;
int answer;

bool is_valid() {
    int balance = 0;
    for (int i = 0; i < n; i++) {
        if (current_string[i] == '(') {
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

void dfs_flip(int pos, int flip_count) {
    if (flip_count >= answer) {
        return;
    }
    if (pos == n) {
        if (is_valid()) {
            answer = flip_count;
        }
        return;
    }

    // 选择 0：当前位置不翻。
    dfs_flip(pos + 1, flip_count);

    // 选择 1：翻转当前位置。
    current_string[pos] = (current_string[pos] == '(' ? ')' : '(');
    dfs_flip(pos + 1, flip_count + 1);
    current_string[pos] = (current_string[pos] == '(' ? ')' : '(');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    current_string = s;
    n = (int)s.size();

    answer = n;
    dfs_flip(0, 0);

    cout << answer << '\n';
    return 0;
}
