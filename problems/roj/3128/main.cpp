/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 营业额统计：treap 按营业额建 BST，逐天查最近的营业额。
#include <cstdio>
#include <vector>

typedef long long ll;

const ll INF = 1000000000000000000LL;

std::vector<ll> left_son; // 左儿子下标，0 表示空
std::vector<ll> right_son;
std::vector<ll> key;     // 该天营业额，同时是 BST 的键
std::vector<ll> prio;    // 随机优先级，小根堆保证期望树高 O(log n)
std::vector<ll> path;

ll rng_state = 20261010; // 固定种子：随机优先级可复现

ll rand30() {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return rng_state & ((1LL << 30) - 1);
}

// 把 node 插入以 root 为根的 treap，返回插入后的新根
ll insert_node(ll root, ll node) {
    if (!root) return node;
    path.clear();
    ll cur = root;
    while (cur) {
        path.push_back(cur);
        cur = (key[node] < key[cur]) ? left_son[cur] : right_son[cur]; // 相等时往右挂
    }
    if (key[node] < key[path.back()]) {
        left_son[path.back()] = node;
    } else {
        right_son[path.back()] = node;
    }
    // 自底向上修正：node 的优先级比父节点小就旋转上浮
    while (!path.empty() && prio[node] < prio[path.back()]) {
        ll parent = path.back();
        path.pop_back();
        ll grand = path.empty() ? 0 : path.back();
        if (left_son[parent] == node) { // 右旋
            left_son[parent] = right_son[node];
            right_son[node] = parent;
        } else { // 左旋
            right_son[parent] = left_son[node];
            left_son[node] = parent;
        }
        if (grand) { // 换根后要接回祖父
            if (left_son[grand] == parent) left_son[grand] = node;
            else right_son[grand] = node;
        } else {
            root = node;
        }
    }
    return root;
}

// 在已插入的营业额里找与 value 距离最近的一个，返回该距离
ll nearest(ll root, ll value) {
    ll best = INF;
    ll cur = root;
    while (cur) {
        ll gap = value - key[cur];
        if (gap < 0) gap = -gap;
        if (gap < best) best = gap;
        if (value < key[cur]) cur = left_son[cur];
        else if (value > key[cur]) cur = right_son[cur];
        else return 0; // 出现过同一天营业额，波动值为 0
    }
    return best;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    std::vector<ll> amount(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &amount[i]);
    }

    left_son.assign(n + 1, 0);
    right_son.assign(n + 1, 0);
    key.assign(n + 1, 0);
    prio.assign(n + 1, 0);
    for (ll i = 0; i < n; i++) {
        key[i + 1] = amount[i];
        prio[i + 1] = rand30();
    }

    ll ans = 0;
    ll root = 0; // 空树
    for (ll day = 0; day < n; day++) {
        ll value = amount[day];
        ll gap = (day == 0) ? value : nearest(root, value); // 第一天的最小波动值就是 a_1
        ans += gap;
        root = insert_node(root, day + 1); // 当天营业额进入集合
    }

    printf("%lld\n", ans);
    return 0;
}
