/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:02
 * update_at: 2026-10-06 17:02
 */

#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

const int N = 16;          // 16×16 数独
const int NCELL = N * N;   // 256 个格子
const int NCOL = 4 * NCELL; // 1024 个约束列
const int ROOT = NCOL;     // 总表头
const int MAXNODE = NCOL + 1 + NCELL * N * 5; // 列头 + 根 + 4096 行 × 4 节点

// Dancing Links 十字链表
int L[MAXNODE];
int R[MAXNODE];
int U[MAXNODE];
int D[MAXNODE];
int C[MAXNODE];   // 节点所属列
int S[NCOL + 1];  // 列的节点数
int ROW[MAXNODE]; // 节点对应的候选行编号

int row_cols[NCELL * N][4]; // 每个候选行覆盖的 4 个约束列

// 列编号：0..255 cell(p), 256..511 row(r,v), 512..767 col(c,v), 768..1023 box(b,v)

int node_cnt; // 当前已用节点数

void init_cols() {
    // 横向环：列头 0..NCOL-1 + 根 ROOT
    for (int i = 0; i <= NCOL; ++i) {
        L[i] = i - 1;
        R[i] = i + 1;
        U[i] = i;
        D[i] = i;
        C[i] = i;
        S[i] = 0;
        ROW[i] = -1;
    }
    L[0] = ROOT;
    R[ROOT] = 0;
    node_cnt = NCOL + 1;
}

void add_row(int row_id, int cols[4]) {
    int first = node_cnt;
    for (int k = 0; k < 4; ++k) {
        int cid = cols[k];
        // 竖向插入到列尾
        U[node_cnt] = U[cid];
        D[node_cnt] = cid;
        D[U[cid]] = node_cnt;
        U[cid] = node_cnt;
        C[node_cnt] = cid;
        ROW[node_cnt] = row_id;
        S[cid]++;
        node_cnt++;
    }
    // 横向成环
    for (int k = 0; k < 4; ++k) {
        int i = first + k;
        L[i] = first + (k + 3) % 4;
        R[i] = first + (k + 1) % 4;
    }
}

void build() {
    init_cols();
    // 预计算每个候选行 (p, v) 的 4 个约束列
    for (int p = 0; p < NCELL; ++p) {
        int r = p >> 4;
        int c = p & 15;
        int b = (r / 4) * 4 + (c / 4);
        for (int v = 0; v < N; ++v) {
            int rid = p * N + v;
            row_cols[rid][0] = p;               // cell(p)
            row_cols[rid][1] = 256 + r * N + v; // row(r,v)
            row_cols[rid][2] = 512 + c * N + v; // col(c,v)
            row_cols[rid][3] = 768 + b * N + v; // box(b,v)
        }
    }
    // 建 4096 个候选行
    for (int rid = 0; rid < NCELL * N; ++rid) {
        add_row(rid, row_cols[rid]);
    }
}

void cover(int cid) {
    L[R[cid]] = L[cid];
    R[L[cid]] = R[cid];
    for (int i = D[cid]; i != cid; i = D[i]) {
        for (int j = R[i]; j != i; j = R[j]) {
            D[U[j]] = D[j];
            U[D[j]] = U[j];
            S[C[j]]--;
        }
    }
}

void uncover(int cid) {
    for (int i = U[cid]; i != cid; i = U[i]) {
        for (int j = L[i]; j != i; j = L[j]) {
            S[C[j]]++;
            D[U[j]] = j;
            U[D[j]] = j;
        }
    }
    L[R[cid]] = cid;
    R[L[cid]] = cid;
}

int sol[300]; // 选中的候选行
int sol_len;

bool search() {
    if (R[ROOT] == ROOT) {
        return true; // 全部覆盖
    }
    // 最小列启发式
    int c = R[ROOT];
    int best = c;
    int best_s = S[c];
    while (c != ROOT) {
        if (S[c] < best_s) {
            best_s = S[c];
            best = c;
        }
        c = R[c];
    }
    if (best_s == 0) {
        return false; // 矛盾
    }
    cover(best);
    for (int i = D[best]; i != best; i = D[i]) {
        sol[sol_len++] = ROW[i];
        for (int j = R[i]; j != i; j = R[j]) {
            cover(C[j]);
        }
        if (search()) {
            return true;
        }
        for (int j = L[i]; j != i; j = L[j]) {
            uncover(C[j]);
        }
        sol_len--;
    }
    uncover(best);
    return false;
}

// 备份数组，用于恢复初始矩阵
int base_L[MAXNODE];
int base_R[MAXNODE];
int base_U[MAXNODE];
int base_D[MAXNODE];
int base_S[NCOL + 1];

char board[NCELL];

void solve_puzzle(const string &puzzle, string &out) {
    // 恢复矩阵到初始状态
    for (int i = 0; i < node_cnt; ++i) {
        L[i] = base_L[i];
        R[i] = base_R[i];
        U[i] = base_U[i];
        D[i] = base_D[i];
    }
    for (int i = 0; i <= NCOL; ++i) {
        S[i] = base_S[i];
    }
    sol_len = 0;
    for (int p = 0; p < NCELL; ++p) {
        board[p] = '-';
    }
    // 处理给定格
    for (int p = 0; p < (int)puzzle.size() && p < NCELL; ++p) {
        char ch = puzzle[p];
        if (ch != '-' && ch != '.') {
            int v = ch - 'A';
            int rid = p * N + v;
            board[p] = ch;
            for (int k = 0; k < 4; ++k) {
                cover(row_cols[rid][k]);
            }
            sol[sol_len++] = rid;
        }
    }
    search();
    for (int i = 0; i < sol_len; ++i) {
        int rid = sol[i];
        int p = rid / N;
        int v = rid % N;
        board[p] = char('A' + v);
    }
    // 输出 16 行
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            out.push_back(board[i * N + j]);
        }
        if (i + 1 < N) {
            out.push_back('\n');
        }
    }
}

char buf[1000000];

int main() {
    build();
    // 备份初始矩阵
    for (int i = 0; i < node_cnt; ++i) {
        base_L[i] = L[i];
        base_R[i] = R[i];
        base_U[i] = U[i];
        base_D[i] = D[i];
    }
    for (int i = 0; i <= NCOL; ++i) {
        base_S[i] = S[i];
    }
    // 读入全部数据
    string all;
    while (fgets(buf, sizeof(buf), stdin)) {
        all += buf;
    }
    // 分词，去掉 end，拼接
    string body;
    int n = all.size();
    int i = 0;
    while (i < n) {
        // 跳过空白
        while (i < n && isspace((unsigned char)all[i])) {
            ++i;
        }
        if (i >= n) break;
        int j = i;
        while (j < n && !isspace((unsigned char)all[j])) {
            ++j;
        }
        string token = all.substr(i, j - i);
        if (token != "end") {
            body += token;
        }
        i = j;
    }
    vector<string> outputs;
    for (size_t pos = 0; pos + NCELL <= body.size(); pos += NCELL) {
        string out;
        solve_puzzle(body.substr(pos, NCELL), out);
        outputs.push_back(out);
    }
    for (size_t k = 0; k < outputs.size(); ++k) {
        if (k > 0) {
            printf("\n\n");
        }
        printf("%s", outputs[k].c_str());
    }
    printf("\n");
    return 0;
}
