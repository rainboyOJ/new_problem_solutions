#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXL = 105;
const int RENKO = 0;
const int MERRY = 1;

struct Op {
    int type;
    int val;
};

int n, q, L;
long long m;
int c[MAXN][MAXL];
int d[MAXN];
vector<Op> ops;

int pos_[2];
long long money[2];
int owner[MAXN];         // -1 表示无建筑，0 表示莲子，1 表示梅莉
int level_[MAXN];        // 建筑当前等级
long long value_[MAXN];  // 当前建筑的 a_i

void give_round_income() {
    for (int i = 1; i <= n; i++) {
        if (owner[i] != -1) {
            money[owner[i]] += d[i];
        }
    }
}

bool move_player(int who, int step) {
    int other = who ^ 1;

    for (int i = 1; i <= step; i++) {
        pos_[who]++;
        if (pos_[who] > n) {
            pos_[who] = 1;
        }

        int p = pos_[who];
        if (owner[p] == who) {
            money[who] += value_[p];
        }
        else if (owner[p] == other) {
            money[who] -= value_[p];
            money[other] += value_[p];
            if (money[who] < 0) {
                return false;
            }
        }
    }

    return true;
}

void build_or_upgrade(int who, int times) {
    int p = pos_[who];

    if (owner[p] != -1 && owner[p] != who) {
        return;
    }

    if (owner[p] == -1) {
        if (times >= 1 && money[who] >= c[p][0]) {
            money[who] -= c[p][0];
            owner[p] = who;
            level_[p] = 1;
            value_[p] = c[p][0];
            times--;
        }
        else {
            return;
        }
    }

    while (times > 0) {
        if (level_[p] >= L) {
            break;
        }
        if (money[who] < c[p][level_[p]]) {
            break;
        }
        money[who] -= c[p][level_[p]];
        value_[p] += c[p][level_[p]];
        level_[p]++;
        times--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q >> L;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= L - 1; j++) {
            cin >> c[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    while (true) {
        Op op;
        if (!(cin >> op.type >> op.val)) {
            break;
        }
        ops.push_back(op);
    }

    for (int i = 1; i <= n; i++) {
        owner[i] = -1;
    }
    pos_[RENKO] = 1;
    pos_[MERRY] = 1;
    money[RENKO] = m;
    money[MERRY] = m;

    int move_cnt = 0;
    for (int i = 0; i < (int)ops.size(); i++) {
        if (ops[i].type != 1) {
            continue;
        }

        int who = move_cnt % 2;
        if (!move_player(who, ops[i].val)) {
            if (who == RENKO) {
                cout << "Renko\n";
            }
            else {
                cout << "Merry\n";
            }
            return 0;
        }

        if (i + 1 < (int)ops.size() && ops[i + 1].type == 2) {
            build_or_upgrade(who, ops[i + 1].val);
            i++;
        }

        move_cnt++;
        if (move_cnt % 2 == 0) {
            give_round_income();
        }
    }

    cout << money[RENKO] << ' ' << money[MERRY] << '\n';

    return 0;
}
