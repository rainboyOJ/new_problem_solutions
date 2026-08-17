/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:52
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const long long NEG = -(1LL << 60) * 4;

struct Matrix {
    long long a[3][3]; // max-plus 矩阵，用于路径上状态 (F,G) 的复合变换
};

int n, m;
long long value_weight[MAXN + 1]; // 每个景点的收费，可能为负
int fa[MAXN + 1];                 // Splay 树父亲
int son[MAXN + 1][2];             // Splay 树左右孩子
bool reversed_tag[MAXN + 1];      // 翻转懒标记
Matrix forward_matrix[MAXN + 1];  // 正方向复合矩阵（链头->链尾）
Matrix backward_matrix[MAXN + 1]; // 反方向复合矩阵（链尾->链头）
Matrix node_matrix[MAXN + 1];     // 单个节点的变换矩阵

long long virtual_sum[MAXN + 1];  // 虚子树 max(0,F) 之和
long long virtual_best[MAXN + 1]; // 虚子树 G 的最大值
multiset<pair<long long, int> > virtual_f[MAXN + 1]; // 虚子树按 (F, 节点) 排序，便于删除
multiset<pair<long long, int> > virtual_g[MAXN + 1]; // 虚子树按 (G, 节点) 排序，便于删除
long long saved_f[MAXN + 1];      // 记录虚子树接入时的 F 值
long long saved_g[MAXN + 1];      // 记录虚子树接入时的 G 值

// 单位矩阵：对角线为 0，其余为负无穷
Matrix identity_matrix() {
    Matrix result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.a[i][j] = (i == j) ? 0 : NEG;
        }
    }
    return result;
}

// max-plus 矩阵乘法：C[i][j] = max_k(A[i][k] + B[k][j])
Matrix compose(const Matrix &left, const Matrix &right) {
    Matrix result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.a[i][j] = NEG;
            for (int k = 0; k < 3; k++) {
                if (left.a[i][k] <= NEG / 2 || right.a[k][j] <= NEG / 2) {
                    continue;
                }
                result.a[i][j] = max(result.a[i][j],
                                     left.a[i][k] + right.a[k][j]);
            }
        }
    }
    return result;
}

Matrix get_forward(int u) {
    if (u == 0) {
        return identity_matrix();
    }
    return forward_matrix[u];
}

Matrix get_backward(int u) {
    if (u == 0) {
        return identity_matrix();
    }
    return backward_matrix[u];
}

// 根据当前节点(含其虚子树)重新计算节点矩阵。
// a = 本节点收费 + 虚子树 max(0,F) 之和；b = 虚子树 G 的最大值。
void update_node_matrix(int u) {
    long long a = value_weight[u] + virtual_sum[u];
    long long b = virtual_best[u];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            node_matrix[u].a[i][j] = NEG;
        }
    }
    // F' = max(a + F, a), G' = max(a + F, G, a, b).
    node_matrix[u].a[0][0] = a;
    node_matrix[u].a[0][2] = a;
    node_matrix[u].a[1][0] = a;
    node_matrix[u].a[1][1] = 0;
    node_matrix[u].a[1][2] = max(a, b);
    node_matrix[u].a[2][2] = 0;
}

// 更新 u 的正向/反向矩阵：左儿子矩阵 * 本节点矩阵 * 右儿子矩阵
void pull(int u) {
    update_node_matrix(u);
    Matrix left_forward = get_forward(son[u][0]);
    Matrix right_forward = get_forward(son[u][1]);
    Matrix middle = compose(left_forward, node_matrix[u]);
    forward_matrix[u] = compose(middle, right_forward);

    Matrix right_backward = get_backward(son[u][1]);
    Matrix left_backward = get_backward(son[u][0]);
    middle = compose(right_backward, node_matrix[u]);
    backward_matrix[u] = compose(middle, left_backward);
}

// 给 u 打上区间翻转标记：交换左右儿子，并交换正反矩阵
void apply_reverse(int u) {
    if (u == 0) {
        return;
    }
    swap(son[u][0], son[u][1]);
    swap(forward_matrix[u], backward_matrix[u]);
    reversed_tag[u] = !reversed_tag[u];
}

void push_down(int u) {
    if (!reversed_tag[u]) {
        return;
    }
    apply_reverse(son[u][0]);
    apply_reverse(son[u][1]);
    reversed_tag[u] = false;
}

bool is_splay_root(int u) {
    return son[fa[u]][0] != u && son[fa[u]][1] != u;
}

void rotate(int u) {
    int y = fa[u];
    int z = fa[y];
    int direction = (son[y][1] == u);
    int middle = son[u][direction ^ 1];
    if (!is_splay_root(y)) {
        son[z][son[z][1] == y] = u;
    }
    fa[u] = z;
    son[u][direction ^ 1] = y;
    fa[y] = u;
    son[y][direction] = middle;
    if (middle != 0) {
        fa[middle] = y;
    }
    pull(y);
    pull(u);
}

void splay(int u) {
    static int stack_nodes[MAXN + 1];
    int top = 0;
    int x = u;
    stack_nodes[++top] = x;
    while (!is_splay_root(x)) {
        x = fa[x];
        stack_nodes[++top] = x;
    }
    while (top > 0) {
        push_down(stack_nodes[top--]);
    }
    while (!is_splay_root(u)) {
        int y = fa[u];
        int z = fa[y];
        if (!is_splay_root(y)) {
            if ((son[y][0] == u) == (son[z][0] == y)) {
                rotate(y);
            } else {
                rotate(u);
            }
        }
        rotate(u);
    }
    pull(u);
}

int leftmost(int u) {
    int x = u;
    while (true) {
        push_down(x);
        if (son[x][0] == 0) {
            return x;
        }
        x = son[x][0];
    }
}

long long evaluate_f(int u) {
    if (u == 0) {
        return NEG;
    }
    return forward_matrix[u].a[0][2];
}

long long evaluate_g(int u) {
    if (u == 0) {
        return NEG;
    }
    return forward_matrix[u].a[1][2];
}

// access 时把一条实链换成虚子树：向父节点登记/撤销它的 F 与 G 贡献
void add_virtual(int parent, int path_root) {
    if (path_root == 0) {
        return;
    }
    int child = leftmost(path_root);
    long long f = max(0LL, evaluate_f(path_root));
    long long g = evaluate_g(path_root);
    saved_f[child] = f;
    saved_g[child] = g;
    virtual_f[parent].insert(make_pair(f, child));
    virtual_g[parent].insert(make_pair(g, child));
    virtual_sum[parent] += f;
    virtual_best[parent] = max(virtual_best[parent], g);
}

// 从父节点的虚子树集合中删除某个实链根对应的贡献
void remove_virtual(int parent, int path_root) {
    if (path_root == 0) {
        return;
    }
    int child = leftmost(path_root);
    long long f = saved_f[child];
    long long g = saved_g[child];
    multiset<pair<long long, int> >::iterator it_f;
    multiset<pair<long long, int> >::iterator it_g;
    it_f = virtual_f[parent].find(make_pair(f, child));
    it_g = virtual_g[parent].find(make_pair(g, child));
    if (it_f != virtual_f[parent].end()) {
        virtual_f[parent].erase(it_f);
    }
    if (it_g != virtual_g[parent].end()) {
        virtual_g[parent].erase(it_g);
    }
    virtual_sum[parent] -= f;
    if (virtual_g[parent].empty()) {
        virtual_best[parent] = NEG;
    } else {
        virtual_best[parent] = virtual_g[parent].rbegin()->first;
    }
}

// access(u)：把 u 到当前根的路径变成实链，途中维护虚实子树集合
void access(int u) {
    int last = 0;
    for (int x = u; x != 0; x = fa[x]) {
        splay(x);
        int old_right = son[x][1];
        if (old_right != 0) {
            add_virtual(x, old_right);
        }
        if (last != 0) {
            remove_virtual(x, last);
        }
        son[x][1] = last;
        if (last != 0) {
            fa[last] = x;
        }
        pull(x);
        last = x;
    }
    splay(u);
}

// 换根：access 后翻转整条实链使 u 成为根
void make_root(int u) {
    access(u);
    apply_reverse(u);
}

// 加边 u-v：先换根再挂到 v 的虚子树
void link_tree(int u, int v) {
    make_root(u);
    access(v);
    add_virtual(v, u);
    fa[u] = v;
    pull(v);
}

// 删边 u-v：换根后这条边位于 v 实链最左侧，直接断开
void cut_tree(int u, int v) {
    make_root(u);
    access(v);
    // The edge u-v is now the leftmost edge of v's preferred path.
    if (son[v][0] == u) {
        son[v][0] = 0;
        fa[u] = 0;
        pull(v);
    }
}

// 以 root 为根时，整个树的基本费用：必须包含根的最大连通权和
long long query_root_value(int root) {
    make_root(root);
    access(root);
    long long answer = value_weight[root] + virtual_sum[root];
    return answer;
}

// 以 root 为根、只看 u 子树：允许游客从子树内任意点进入，取 G_u 与 F_u 的较大者
long long query_subtree_value(int root, int u) {
    make_root(root);
    access(u);
    long long containing = value_weight[u] + virtual_sum[u];
    long long anywhere = max(containing, virtual_best[u]);
    return anywhere;
}

// 修改节点权值并更新受影响矩阵
void modify_weight(int u, long long value) {
    access(u);
    value_weight[u] = value;
    pull(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> value_weight[i];
        virtual_best[i] = NEG;
        pull(i);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        link_tree(u, v);
    }

    int current_root = 1;
    cout << query_root_value(current_root) << '\n';
    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int u;
            cin >> u;
            cout << query_subtree_value(current_root, u) << '\n';
        } else if (type == 2) {
            int u;
            long long x;
            cin >> u >> x;
            modify_weight(u, x);
            cout << query_root_value(current_root) << '\n';
        } else if (type == 3) {
            cin >> current_root;
            cout << query_root_value(current_root) << '\n';
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cut_tree(a, b);
            link_tree(c, d);
            cout << query_root_value(current_root) << '\n';
        }
    }
    return 0;
}
