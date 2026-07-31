/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:40
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 105;
const long long NEG = -(1LL << 60);

struct Node {
    int next[26];
    int fail;
    int score;
};

struct Matrix {
    long long value[MAXS][MAXS];
};

Node trie[MAXS];
int node_count = 1;

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

    Matrix transition;
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) transition.value[i][j] = NEG;
        for (int c = 0; c < 26; c++) {
            int v = trie[i].next[c];
            transition.value[i][v] = max(transition.value[i][v], (long long)trie[v].score);
        }
    }
    long long best[MAXS] = {};
    for (int i = 1; i < node_count; i++) best[i] = NEG;
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
