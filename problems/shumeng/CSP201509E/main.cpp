/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:58
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 105;
const long long NEG = -(1LL << 60); // 不可达状态，max 运算下的“负无穷”

// AC 自动机节点：next[c] 是字符 c 的转移，fail 是失配指针，
// score 是“以该状态结尾时能新增的匹配次数”。
struct Node {
    int next[26];
    int fail;
    int score;
};

// max-plus 意义下的转移矩阵：value[i][j] 表示从状态 i 走一步到 j 能得到的最大加分。
struct Matrix {
    long long value[MAXS][MAXS];
};

Node trie[MAXS]; // AC 自动机节点数组，下标 0 是根节点
int node_count = 1;

// 在 max-plus 代数下做矩阵乘法：C[i][j] = max_k (A[i][k] + B[k][j])。
Matrix multiply(const Matrix &left, const Matrix &right, int states) {
    Matrix result;
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < states; j++) result.value[i][j] = NEG;
    }
    for (int i = 0; i < states; i++) {
        for (int k = 0; k < states; k++) {
            if (left.value[i][k] == NEG) continue;
            for (int j = 0; j < states; j++) {
                if (right.value[k][j] == NEG) continue;
                result.value[i][j] = max(result.value[i][j],
                                         left.value[i][k] + right.value[k][j]);
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long length;
    cin >> n >> length;

    // 把每个单词插入 Trie，单词末尾的 score 加 1。
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        int current = 0;
        for (int j = 0; j < (int)word.size(); j++) {
            int c = word[j] - 'a';
            if (trie[current].next[c] == 0) trie[current].next[c] = node_count++;
            current = trie[current].next[c];
        }
        trie[current].score++;
    }

    // BFS 构建失配指针，并把子串的分数累加到父节点：让包含关系与重叠出现都被计数。
    queue<int> q;
    for (int c = 0; c < 26; c++) {
        int child = trie[0].next[c];
        if (child != 0) q.push(child);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        trie[u].score += trie[trie[u].fail].score;
        for (int c = 0; c < 26; c++) {
            int v = trie[u].next[c];
            if (v != 0) {
                trie[v].fail = trie[trie[u].fail].next[c];
                q.push(v);
            } else {
                trie[u].next[c] = trie[trie[u].fail].next[c];
            }
        }
    }

    // 构造一步转移矩阵：从状态 i 沿字符 c 走到 v，获得 score[v] 分。
    Matrix transition;
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) transition.value[i][j] = NEG;
        for (int c = 0; c < 26; c++) {
            int v = trie[i].next[c];
            transition.value[i][v] = max(transition.value[i][v], (long long)trie[v].score);
        }
    }

    // best[i] 表示写出的前缀落在状态 i 时能得到的最大重要度，起点只能是根。
    long long best[MAXS] = {};
    for (int i = 1; i < node_count; i++) best[i] = NEG;
    // 二进制快速幂：把 transition 当作“走一步”，对 length 步做 max-plus 幂。
    while (length > 0) {
        if (length & 1) {
            long long next_best[MAXS];
            for (int j = 0; j < node_count; j++) next_best[j] = NEG;
            for (int i = 0; i < node_count; i++) {
                if (best[i] == NEG) continue;
                for (int j = 0; j < node_count; j++) {
                    next_best[j] = max(next_best[j], best[i] + transition.value[i][j]);
                }
            }
            for (int i = 0; i < node_count; i++) best[i] = next_best[i];
        }
        transition = multiply(transition, transition, node_count);
        length >>= 1;
    }
    long long answer = 0;
    for (int i = 0; i < node_count; i++) answer = max(answer, best[i]);
    cout << answer << '\n';
    return 0;
}
