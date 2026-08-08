#include <bits/stdc++.h>
using namespace std;

// brute.cpp：每次查找最早出现的敏感词并删除，只适合小数据。

string s;
int n;
vector<string> words;

void solve_brute() {
    while (true) {
        int best_pos = -1;
        int best_id = -1;

        for (int i = 0; i < n; i++) {
            size_t pos_value = s.find(words[i]);
            if (pos_value == string::npos) {
                continue;
            }
            int pos = (int)pos_value;
            if (best_pos == -1 || pos < best_pos) {
                best_pos = pos;
                best_id = i;
            }
        }

        if (best_pos == -1) {
            break;
        }
        s.erase(best_pos, words[best_id].size());
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string t;
        cin >> t;
        words.push_back(t);
    }

    solve_brute();
    cout << s << '\n';

    return 0;
}
