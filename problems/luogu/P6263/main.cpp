#include <bits/stdc++.h>
using namespace std;

string s;
int ans[8];
int belong[256];  // 每个字符由哪根手指负责，-1 表示不统计

void init_belong() {
    memset(belong, -1, sizeof(belong));

    string group[8] = {
        "1QAZ",
        "2WSX",
        "3EDC",
        "4RFV5TGB",
        "6YHN7UJM",
        "8IK,",
        "9OL.",
        "0P;/-['=]"
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < (int) group[i].size(); j++) {
            belong[(int) group[i][j]] = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, s);
    init_belong();
    memset(ans, 0, sizeof(ans));

    for (int i = 0; i < (int) s.size(); i++) {
        int id = belong[(int) s[i]];
        if (id != -1) {
            ans[id]++;
        }
    }

    for (int i = 0; i < 8; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
