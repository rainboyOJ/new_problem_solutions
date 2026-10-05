/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:01
 * update_at: 2026-10-05 10:01
 */
#include <cstdio>
#include <stack>

typedef long long ll;

const int MAXN = 35;
const ll EMPTY_SCORE = 1; // 空子树的加分，即长度 0 区间的值

int n;
ll d[MAXN];          // d[i]：中序第 i 个节点的分数（0-based 下标）
ll score[MAXN][MAXN]; // score[l][r]：中序半开区间 [l, r) 组成的子树的最大加分
int root[MAXN][MAXN]; // root[l][r]：该最优子树的根下标，用于还原前序遍历

// 前序遍历 = 根 + 左子树 + 右子树；用显式栈展开，避免深递归与递归实现细节
void print_preorder() {
    std::stack<int> st_l;
    std::stack<int> st_r;
    st_l.push(0);
    st_r.push(n);
    bool first = true;
    while (!st_l.empty()) {
        int l = st_l.top();
        int r = st_r.top();
        st_l.pop();
        st_r.pop();
        if (l >= r) {
            continue; // 空区间没有根
        }
        int k = root[l][r];
        if (!first) {
            printf(" ");
        }
        printf("%d", k + 1); // 还原成 1-based 的节点编号
        first = false;
        // 栈后进先出：先压右子树，才能先弹出左子树
        st_l.push(k + 1);
        st_r.push(r);
        st_l.push(l);
        st_r.push(k);
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &d[i]);
    }

    // 空区间（l == r）加分恒为 1
    for (int l = 0; l <= n; l++) {
        for (int r = 0; r <= n; r++) {
            score[l][r] = EMPTY_SCORE;
            root[l][r] = 0;
        }
    }

    // 长度 1 的区间是叶子：加分就是节点自己的分数，不套用 l*r+a
    for (int i = 0; i < n; i++) {
        score[i][i + 1] = d[i];
        root[i][i + 1] = i;
    }

    // 按区间长度递增递推，保证左右两个子区间都已算好
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            ll best = 0;
            for (int k = l; k < r; k++) {
                // 枚举根 k：左子树 [l, k)，右子树 [k+1, r)
                ll cand = score[l][k] * score[k + 1][r] + d[k];
                if (cand > best) {
                    best = cand;
                    root[l][r] = k;
                }
            }
            score[l][r] = best;
        }
    }

    printf("%lld\n", score[0][n]);
    print_preorder();
    return 0;
}
