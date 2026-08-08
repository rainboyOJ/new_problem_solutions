#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 205;

int n, m;
int worm_len[MAXN];
int pre_node[MAXN], nxt_node[MAXN];

string forward_string(int u, int k) {
    string res = "";
    while (u != 0 && k > 0) {
        res.push_back(char('0' + worm_len[u]));
        u = nxt_node[u];
        k--;
    }
    if (k > 0) {
        return "";
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> worm_len[i];
        pre_node[i] = nxt_node[i] = 0;
    }

    for (int opi = 1; opi <= m; opi++) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, j;
            cin >> i >> j;
            nxt_node[i] = j;
            pre_node[j] = i;
        }
        else if (type == 2) {
            int i;
            cin >> i;
            int x = nxt_node[i];
            nxt_node[i] = 0;
            if (x != 0) {
                pre_node[x] = 0;
            }
        }
        else {
            string s;
            int k;
            cin >> s >> k;

            map<string, int> cnt;
            for (int i = 1; i <= n; i++) {
                string t = forward_string(i, k);
                if (!t.empty()) {
                    cnt[t]++;
                }
            }

            long long answer = 1;
            for (int i = 0; i + k <= (int)s.size(); i++) {
                string t = s.substr(i, k);
                answer = answer * cnt[t] % MOD;
            }
            cout << answer << '\n';
        }
    }

    return 0;
}
