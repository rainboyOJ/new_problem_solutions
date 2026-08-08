// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, m, max_k;
int base_ability[MAXN], current_ability[MAXN], query_c[MAXN];
int draw_round[10][MAXN];
set<int> possible_winner;

int ceil_power_log(int x) {
    int k = 0;
    while ((1 << k) < x) {
        k++;
    }
    return k;
}

int simulate_tournament(int total_players, int k, int ability[]) {
    vector<int> player;
    for (int i = 1; i <= total_players; i++) {
        player.push_back(i);
    }

    for (int round_id = 1; round_id <= k; round_id++) {
        vector<int> next_player;
        int games = (int)player.size() / 2;
        for (int g = 1; g <= games; g++) {
            int left = player[(g - 1) * 2];
            int right = player[(g - 1) * 2 + 1];
            int lord, other;

            if (draw_round[round_id][g] == 0) {
                lord = left;
                other = right;
            } else {
                lord = right;
                other = left;
            }

            if (ability[lord] >= round_id) {
                next_player.push_back(lord);
            } else {
                next_player.push_back(other);
            }
        }
        player = next_player;
    }

    return player[0];
}

void enumerate_unknown(int pos, int total_players, int known_count, int k, int ability[]) {
    if (pos > total_players) {
        possible_winner.insert(simulate_tournament(total_players, k, ability));
        return;
    }

    if (pos <= known_count) {
        enumerate_unknown(pos + 1, total_players, known_count, k, ability);
        return;
    }

    // 补充选手只需要枚举 0..k，能力超过 k 与 k 等价。
    for (int value = 0; value <= k; value++) {
        ability[pos] = value;
        enumerate_unknown(pos + 1, total_players, known_count, k, ability);
    }
}

long long champion_sum_for_prefix(int prefix_len) {
    int k = ceil_power_log(prefix_len);
    int total_players = 1 << k;
    int ability[MAXN];

    for (int i = 1; i <= total_players; i++) {
        if (i <= prefix_len) {
            ability[i] = current_ability[i];
        } else {
            ability[i] = 0;
        }
    }

    possible_winner.clear();
    enumerate_unknown(1, total_players, prefix_len, k, ability);

    long long sum = 0;
    for (set<int>::iterator it = possible_winner.begin(); it != possible_winner.end(); ++it) {
        sum += *it;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    max_k = ceil_power_log(n);

    for (int i = 1; i <= n; i++) {
        cin >> base_ability[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> query_c[i];
    }

    for (int round_id = 1; round_id <= max_k; round_id++) {
        string s;
        cin >> s;
        for (int j = 0; j < (int)s.size(); j++) {
            draw_round[round_id][j + 1] = s[j] - '0';
        }
    }

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int mask_value[4];
        for (int i = 0; i < 4; i++) {
            cin >> mask_value[i];
        }

        for (int i = 1; i <= n; i++) {
            current_ability[i] = base_ability[i] ^ mask_value[i & 3];
        }

        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            ans ^= 1LL * i * champion_sum_for_prefix(query_c[i]);
        }

        cout << ans << '\n';
    }

    return 0;
}
