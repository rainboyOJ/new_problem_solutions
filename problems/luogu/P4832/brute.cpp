#include <bits/stdc++.h>
using namespace std;

const int NEG_INF = -0x3f3f3f3f;

int n;
vector<int> diff_val, len_val;
int best_answer;

void dfs(int idx, int diff_sum, int len_sum) {
    if (idx == n) {
        if (diff_sum == 0) {
            best_answer = max(best_answer, len_sum / 2);
        }
        return;
    }

    // 不选当前式子。
    dfs(idx + 1, diff_sum, len_sum);
    // 选当前式子。
    dfs(idx + 1, diff_sum + diff_val[idx], len_sum + len_val[idx]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力枚举。
    // 直接枚举每个式子选或不选，统计总差值是否为 0。
    cin >> n;
    diff_val.resize(n);
    len_val.resize(n);

    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        int cnt_s = 0;
        int cnt_c = 0;
        for (unsigned int j = 0; j < str.size(); j++) {
            if (str[j] == 's') {
                cnt_s++;
            } else if (str[j] == 'c') {
                cnt_c++;
            }
        }
        diff_val[i] = cnt_s - cnt_c;
        len_val[i] = cnt_s + cnt_c;
    }

    best_answer = 0;
    dfs(0, 0, 0);
    cout << best_answer << '\n';
    return 0;
}
