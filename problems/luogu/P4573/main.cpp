#include <bits/stdc++.h>
using namespace std;

const int FULL_MASK = (1 << 9) - 1;

char h_rel[9][8]; // 同一行里相邻格子的左右大小关系
char v_rel[8][9]; // 同一列里相邻格子的上下大小关系

int peers[81][24];
int peer_cnt[81];

struct Arc {
    int u, v;
    char rel; // '<' 表示 u < v，'>' 表示 u > v
};

Arc arcs[200];
int arc_cnt;

int unit_cells[27][9];

int answer_mask[81];

int bit_count(int x) {
    return __builtin_popcount((unsigned int)x);
}

int lowbit_to_digit(int bit) {
    for (int d = 1; d <= 9; d++) {
        if (bit == (1 << (d - 1))) {
            return d;
        }
    }
    return 0;
}

void add_peer(int u, int v) {
    for (int i = 0; i < peer_cnt[u]; i++) {
        if (peers[u][i] == v) {
            return;
        }
    }
    peers[u][peer_cnt[u]++] = v;
}

void build_units_and_peers() {
    memset(peer_cnt, 0, sizeof(peer_cnt));

    int id = 0;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            unit_cells[id][c] = r * 9 + c;
        }
        id++;
    }

    for (int c = 0; c < 9; c++) {
        for (int r = 0; r < 9; r++) {
            unit_cells[id][r] = r * 9 + c;
        }
        id++;
    }

    for (int br = 0; br < 9; br += 3) {
        for (int bc = 0; bc < 9; bc += 3) {
            int pos = 0;
            for (int r = br; r < br + 3; r++) {
                for (int c = bc; c < bc + 3; c++) {
                    unit_cells[id][pos++] = r * 9 + c;
                }
            }
            id++;
        }
    }

    for (int u = 0; u < 81; u++) {
        for (int t = 0; t < 27; t++) {
            int found = -1;
            for (int j = 0; j < 9; j++) {
                if (unit_cells[t][j] == u) {
                    found = j;
                    break;
                }
            }
            if (found == -1) {
                continue;
            }
            for (int j = 0; j < 9; j++) {
                int v = unit_cells[t][j];
                if (v != u) {
                    add_peer(u, v);
                }
            }
        }
    }
}

void build_arcs() {
    arc_cnt = 0;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 8; c++) {
            if (h_rel[r][c] == 0) {
                continue;
            }
            int u = r * 9 + c;
            int v = r * 9 + c + 1;
            arcs[arc_cnt++] = {u, v, h_rel[r][c]};
        }
    }

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 9; c++) {
            if (v_rel[r][c] == 0) {
                continue;
            }
            int u = r * 9 + c;
            int v = (r + 1) * 9 + c;
            if (v_rel[r][c] == '^') {
                arcs[arc_cnt++] = {u, v, '<'};
            } else {
                arcs[arc_cnt++] = {u, v, '>'};
            }
        }
    }
}

// 根据不等式关系，删去不可能的候选数字。
bool revise_arc(int mask_u, int mask_v, char rel, int &new_u, int &new_v) {
    new_u = 0;
    new_v = 0;

    for (int du = 1; du <= 9; du++) {
        int bit_u = 1 << (du - 1);
        if ((mask_u & bit_u) == 0) {
            continue;
        }

        bool ok = false;
        for (int dv = 1; dv <= 9; dv++) {
            int bit_v = 1 << (dv - 1);
            if ((mask_v & bit_v) == 0) {
                continue;
            }
            if ((rel == '<' && du < dv) || (rel == '>' && du > dv)) {
                ok = true;
                break;
            }
        }
        if (ok) {
            new_u |= bit_u;
        }
    }

    for (int dv = 1; dv <= 9; dv++) {
        int bit_v = 1 << (dv - 1);
        if ((mask_v & bit_v) == 0) {
            continue;
        }

        bool ok = false;
        for (int du = 1; du <= 9; du++) {
            int bit_u = 1 << (du - 1);
            if ((mask_u & bit_u) == 0) {
                continue;
            }
            if ((rel == '<' && du < dv) || (rel == '>' && du > dv)) {
                ok = true;
                break;
            }
        }
        if (ok) {
            new_v |= bit_v;
        }
    }

    return new_u != 0 && new_v != 0;
}

// 反复做三类传播：
// 1. 单点定值后删同行/同列/同宫候选
// 2. 按不等式删候选
// 3. 行列宫里的隐藏单点
bool propagate(int dom[]) {
    while (true) {
        bool changed = false;

        for (int u = 0; u < 81; u++) {
            if (dom[u] == 0) {
                return false;
            }
            if (bit_count(dom[u]) != 1) {
                continue;
            }

            int bit = dom[u];
            for (int i = 0; i < peer_cnt[u]; i++) {
                int v = peers[u][i];
                if ((dom[v] & bit) == 0) {
                    continue;
                }
                int new_mask = dom[v] ^ bit;
                if (new_mask == 0) {
                    return false;
                }
                if (new_mask != dom[v]) {
                    dom[v] = new_mask;
                    changed = true;
                }
            }
        }

        for (int i = 0; i < arc_cnt; i++) {
            int u = arcs[i].u;
            int v = arcs[i].v;
            int new_u, new_v;
            if (!revise_arc(dom[u], dom[v], arcs[i].rel, new_u, new_v)) {
                return false;
            }
            if (new_u != dom[u]) {
                dom[u] = new_u;
                changed = true;
            }
            if (new_v != dom[v]) {
                dom[v] = new_v;
                changed = true;
            }
        }

        for (int t = 0; t < 27; t++) {
            for (int digit = 1; digit <= 9; digit++) {
                int bit = 1 << (digit - 1);
                int pos = -1;
                int cnt = 0;

                for (int j = 0; j < 9; j++) {
                    int u = unit_cells[t][j];
                    if (dom[u] & bit) {
                        cnt++;
                        pos = u;
                    }
                }

                if (cnt == 0) {
                    return false;
                }
                if (cnt == 1 && dom[pos] != bit) {
                    dom[pos] = bit;
                    changed = true;
                }
            }
        }

        if (!changed) {
            return true;
        }
    }
}

bool dfs(int dom[]) {
    int cur[81];
    for (int i = 0; i < 81; i++) {
        cur[i] = dom[i];
    }

    if (!propagate(cur)) {
        return false;
    }

    int best = -1;
    int best_cnt = 10;

    for (int i = 0; i < 81; i++) {
        int cnt = bit_count(cur[i]);
        if (cnt > 1 && cnt < best_cnt) {
            best_cnt = cnt;
            best = i;
        }
    }

    if (best == -1) {
        for (int i = 0; i < 81; i++) {
            answer_mask[i] = cur[i];
        }
        return true;
    }

    int mask = cur[best];
    while (mask != 0) {
        int bit = mask & (-mask);
        mask -= bit;

        int next_dom[81];
        for (int i = 0; i < 81; i++) {
            next_dom[i] = cur[i];
        }
        next_dom[best] = bit;

        if (dfs(next_dom)) {
            return true;
        }
    }

    return false;
}

void read_relations() {
    vector<string> token_lines;
    string line;

    while ((int)token_lines.size() < 15 && getline(cin, line)) {
        if (line.empty()) {
            continue;
        }
        token_lines.push_back(line);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 8; j++) {
            h_rel[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 9; j++) {
            v_rel[i][j] = 0;
        }
    }

    for (int idx = 0; idx < 15; idx++) {
        vector<char> arr;
        for (int p = 0; p < (int)token_lines[idx].size(); p++) {
            char ch = token_lines[idx][p];
            if (ch == '<' || ch == '>' || ch == '^' || ch == 'v') {
                arr.push_back(ch);
            }
        }

        if ((int)arr.size() == 6) {
            int row = (idx / 5) * 3 + ((idx % 5) / 2);
            int cols[6] = {0, 1, 3, 4, 6, 7};
            for (int i = 0; i < 6; i++) {
                h_rel[row][cols[i]] = arr[i];
            }
        } else {
            int row = (idx / 5) * 3 + ((idx % 5 - 1) / 2);
            for (int i = 0; i < 9; i++) {
                v_rel[row][i] = arr[i];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_relations();
    build_units_and_peers();
    build_arcs();

    int dom[81];
    for (int i = 0; i < 81; i++) {
        dom[i] = FULL_MASK;
    }

    if (!dfs(dom)) {
        return 0;
    }

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (c) {
                cout << ' ';
            }
            cout << lowbit_to_digit(answer_mask[r * 9 + c]);
        }
        cout << '\n';
    }

    return 0;
}
