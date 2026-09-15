/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-15 14:26
 * update_at: 2026-09-15 16:59
 */
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const int maxn = 250000 + 5;
const ull base = 233;

struct Node {
    int l, r;
    int siz;
    int val;
    unsigned int fix;
    ull hash_value;
} tr[maxn];

int root, node_cnt;
int m;
int query_x, query_y;
ull pw[maxn];
mt19937 rnd(712367821);

int new_node(int val) {
    node_cnt++;
    tr[node_cnt].l = tr[node_cnt].r = 0;
    tr[node_cnt].siz = 1;
    tr[node_cnt].val = val;
    tr[node_cnt].fix = rnd();
    tr[node_cnt].hash_value = val;
    return node_cnt;
}

// 维护“左子串 + 当前字符 + 右子串”的长度与哈希。
void push_up(int u) {
    int left_siz = tr[tr[u].l].siz;
    int right_siz = tr[tr[u].r].siz;
    tr[u].siz = left_siz + 1 + right_siz;
    tr[u].hash_value = tr[tr[u].l].hash_value * pw[right_siz + 1]
                     + (ull)tr[u].val * pw[right_siz]
                     + tr[tr[u].r].hash_value;
}

// 按排名分裂：x 保存前 k 个字符，y 保存剩余字符。
void split(int u, int k, int &x, int &y) {
    if (u == 0) {
        x = y = 0;
        return;
    }

    if (tr[tr[u].l].siz >= k) {
        y = u;
        split(tr[u].l, k, x, tr[y].l);
        push_up(y);
    }
    else {
        x = u;
        split(tr[u].r, k - tr[tr[u].l].siz - 1, tr[x].r, y);
        push_up(x);
    }
}

// 合并两段相邻的字符串。
int merge(int x, int y) {
    if (x == 0 || y == 0) return x + y;

    if (tr[x].fix > tr[y].fix) {
        tr[x].r = merge(tr[x].r, y);
        push_up(x);
        return x;
    }
    else {
        tr[y].l = merge(x, tr[y].l);
        push_up(y);
        return y;
    }
}

// 取得子树 u 内第 l 到第 r 个字符的哈希，位置从 1 开始。
//
// 这里不使用 split 把区间切出来，而是只读地沿 Treap 查询。
// 好处是：一次 LCQ 要二分很多次；若每次查询都 split、merge，常数会较大。
//
// 当前子树的中序字符串可看成：
//
//     左子树字符串 + 当前字符 + 右子树字符串
//
// 我们把查询区间和这三段分别求交。完全被查询区间覆盖的子树，
// 可以直接使用该子树已经维护好的 hash_value，无须继续递归。
ull range_hash(int u, int l, int r) {
    // 整棵子树都被取到：直接返回预处理好的整段哈希。
    if (l == 1 && r == tr[u].siz) return tr[u].hash_value;

    // 左子树占据位置 [1, left_siz]，当前字符的位置是 middle_pos。
    int left_siz = tr[tr[u].l].siz;
    int middle_pos = left_siz + 1;
    ull ans = 0;

    // 1. 查询区间与左子树有交集。
    if (l <= left_siz) {
        int part_l = l;
        int part_r = min(r, left_siz);

        // 先拼接左边这一段。若它长 len，则旧 ans 要左移 len 位：
        // hash(ans + part) = hash(ans) * base^len + hash(part)。
        ans = ans * pw[part_r - part_l + 1]
            + range_hash(tr[u].l, part_l, part_r);
    }

    // 2. 查询区间包含当前节点的字符。
    if (l <= middle_pos && middle_pos <= r) {
        ans = ans * base + tr[u].val;
    }

    // 3. 查询区间与右子树有交集。
    // 右子树的内部编号从 1 开始，因此要减去 middle_pos。
    if (r > middle_pos) {
        int part_l = max(1, l - middle_pos);
        int part_r = r - middle_pos;

        // 最后把右边这一段接在 ans 后面，保持字符串从左到右的顺序。
        ans = ans * pw[part_r - part_l + 1]
            + range_hash(tr[u].r, part_l, part_r);
    }

    // ans 按“左段 + 当前字符 + 右段”的顺序拼好，正是 [l, r] 的哈希。
    return ans;
}

void insert_after(int pos, int val) {
    int x, y;
    split(root, pos, x, y);
    root = merge(merge(x, new_node(val)), y);
}

// 找到第 pos 个节点，修改字符后沿递归路径更新哈希。
void change(int u, int pos, int val) {
    int left_siz = tr[tr[u].l].siz;
    if (pos <= left_siz) change(tr[u].l, pos, val);
    else if (pos == left_siz + 1) tr[u].val = val;
    else change(tr[u].r, pos - left_siz - 1, val);
    push_up(u);
}

bool check(int x, int y, int len) {
    if (len == 0) return true;
    return range_hash(root, x, x + len - 1)
        == range_hash(root, y, y + len - 1);
}

bool check_len(int len) {
    return check(query_x, query_y, len);
}

// 由 rbook 的 first_true 模板改造而来：
// 在 [left, right] 中寻找第一个 check_len(len) 为假的长度。
// right 可以是虚拟失败位置，循环中不会用它调用 check_len。
int first_fail(int left, int right) {
    while (left < right) {
        int mid = (left + right) / 2;
        if (check_len(mid)) left = mid + 1;
        else right = mid;
    }
    return left;
}

void solve() {
    string s;
    cin >> s >> m;

    pw[0] = 1;
    int limit = (int)s.size() + m + 1;
    for (int i = 1; i <= limit; i++) {
        pw[i] = pw[i - 1] * base;
    }

    for (int i = 0; i < (int)s.size(); i++) {
        root = merge(root, new_node(s[i] - 'a' + 1));
    }

    for (int i = 1; i <= m; i++) {
        char op, ch;
        int x, y;
        cin >> op >> x;

        if (op == 'I') {
            cin >> ch;
            insert_after(x, ch - 'a' + 1);
        }
        else if (op == 'R') {
            cin >> ch;
            change(root, x, ch - 'a' + 1);
        }
        else {
            cin >> y;
            int length = tr[root].siz;
            if (x == y) {
                cout << length - x + 1 << '\n';
                continue;
            }

            query_x = x;
            query_y = y;
            int upper = min(length - x + 1, length - y + 1);
            cout << first_fail(0, upper + 1) - 1 << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
