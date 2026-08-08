#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 200005;
const int MAXK = 55;
const int HASH_SIZE = 1 << 20;

struct Key {
    unsigned long long x0, x1, x2;

    bool operator==(const Key &other) const {
        return x0 == other.x0 && x1 == other.x1 && x2 == other.x2;
    }
};

struct HashNode {
    Key key;
    int value;
    int next;
};

struct HashTable {
    int head[HASH_SIZE];
    vector<HashNode> nodes;
    vector<int> free_list;

    void init() {
        memset(head, -1, sizeof(head));
        nodes.clear();
        free_list.clear();
        nodes.reserve(400000);
        free_list.reserve(200000);
    }

    unsigned int hash_key(const Key &key) const {
        unsigned long long h = key.x0 * 1000003ULL;
        h ^= key.x1 * 1000033ULL;
        h ^= key.x2 * 1000211ULL;
        h ^= h >> 32;
        return (unsigned int)(h & (HASH_SIZE - 1));
    }

    int get(const Key &key) const {
        unsigned int bucket = hash_key(key);
        for (int i = head[bucket]; i != -1; i = nodes[i].next) {
            if (nodes[i].key == key) {
                return nodes[i].value;
            }
        }
        return 0;
    }

    void add(const Key &key, int delta) {
        unsigned int bucket = hash_key(key);
        int prev = -1;
        for (int i = head[bucket]; i != -1; i = nodes[i].next) {
            if (nodes[i].key == key) {
                nodes[i].value += delta;
                if (nodes[i].value == 0) {
                    if (prev == -1) {
                        head[bucket] = nodes[i].next;
                    }
                    else {
                        nodes[prev].next = nodes[i].next;
                    }
                    free_list.push_back(i);
                }
                return;
            }
            prev = i;
        }

        if (delta <= 0) {
            return;
        }

        int id;
        if (!free_list.empty()) {
            id = free_list.back();
            free_list.pop_back();
            nodes[id].key = key;
            nodes[id].value = delta;
            nodes[id].next = head[bucket];
        }
        else {
            id = (int)nodes.size();
            nodes.push_back({key, delta, head[bucket]});
        }
        head[bucket] = id;
    }
};

struct Operation {
    int type;
    int a, b;
    int k;
    int id;
    string s;
};

int n, m;
int worm_len[MAXN];
vector<Operation> ops;
vector<int> query_k_list;
vector<int> query_answer;
bool need_k[MAXK];

int pre_node[MAXN], nxt_node[MAXN];
int left_digits[MAXK], right_digits[MAXK], concat_digits[MAXK * 2];

unsigned long long mask0, mask1, mask2;

void clear_key(Key &key) {
    key.x0 = key.x1 = key.x2 = 0;
}

unsigned long long build_mask(int bits) {
    if (bits <= 0) {
        return 0;
    }
    if (bits >= 64) {
        return ~0ULL;
    }
    return (1ULL << bits) - 1;
}

void set_key_mask(int k) {
    int total_bits = 3 * k;
    mask0 = build_mask(min(total_bits, 64));
    mask1 = build_mask(min(max(total_bits - 64, 0), 64));
    mask2 = build_mask(min(max(total_bits - 128, 0), 64));
}

void append_digit(Key &key, int digit) {
    unsigned long long nx2 = (key.x2 << 3) | (key.x1 >> 61);
    unsigned long long nx1 = (key.x1 << 3) | (key.x0 >> 61);
    unsigned long long nx0 = (key.x0 << 3) | (unsigned long long)digit;
    key.x0 = nx0 & mask0;
    key.x1 = nx1 & mask1;
    key.x2 = nx2 & mask2;
}

int get_left_digits(int u, int limit, int out[]) {
    int tmp[MAXK];
    int cnt = 0;
    while (u != 0 && cnt < limit) {
        tmp[cnt++] = worm_len[u];
        u = pre_node[u];
    }
    for (int i = 0; i < cnt; i++) {
        out[i] = tmp[cnt - 1 - i];
    }
    return cnt;
}

int get_right_digits(int u, int limit, int out[]) {
    int cnt = 0;
    while (u != 0 && cnt < limit) {
        out[cnt++] = worm_len[u];
        u = nxt_node[u];
    }
    return cnt;
}

void update_cross_boundary(int left_tail, int right_head, int k, int delta, HashTable &counter) {
    if (k == 1 || left_tail == 0 || right_head == 0) {
        return;
    }

    int len_left = get_left_digits(left_tail, k - 1, left_digits);
    int len_right = get_right_digits(right_head, k - 1, right_digits);
    int total = len_left + len_right;
    if (total < k) {
        return;
    }

    for (int i = 0; i < len_left; i++) {
        concat_digits[i] = left_digits[i];
    }
    for (int i = 0; i < len_right; i++) {
        concat_digits[len_left + i] = right_digits[i];
    }

    int start_count = min(len_left, total - k + 1);
    if (start_count <= 0) {
        return;
    }

    Key key;
    clear_key(key);
    for (int i = 0; i < k; i++) {
        append_digit(key, concat_digits[i]);
    }
    counter.add(key, delta);

    for (int start = 1; start < start_count; start++) {
        append_digit(key, concat_digits[start + k - 1]);
        counter.add(key, delta);
    }
}

int query_string_product(const string &s, int k, const HashTable &counter) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '1' || s[i] > '6') {
            return 0;
        }
    }

    Key key;
    clear_key(key);
    for (int i = 0; i < k; i++) {
        append_digit(key, s[i] - '0');
    }

    long long answer = counter.get(key);
    if (answer == 0) {
        return 0;
    }

    for (int i = k; i < (int)s.size(); i++) {
        append_digit(key, s[i] - '0');
        int ways = counter.get(key);
        if (ways == 0) {
            return 0;
        }
        answer = answer * ways % MOD;
    }
    return (int)answer;
}

void simulate_one_k(int k) {
    set_key_mask(k);

    for (int i = 1; i <= n; i++) {
        pre_node[i] = 0;
        nxt_node[i] = 0;
    }

    HashTable counter;
    counter.init();

    if (k == 1) {
        for (int i = 1; i <= n; i++) {
            Key key;
            clear_key(key);
            append_digit(key, worm_len[i]);
            counter.add(key, 1);
        }
    }

    for (int idx = 0; idx < (int)ops.size(); idx++) {
        Operation &op = ops[idx];
        if (op.type == 1) {
            update_cross_boundary(op.a, op.b, k, 1, counter);
            nxt_node[op.a] = op.b;
            pre_node[op.b] = op.a;
        }
        else if (op.type == 2) {
            int right_head = nxt_node[op.a];
            update_cross_boundary(op.a, right_head, k, -1, counter);
            if (right_head != 0) {
                pre_node[right_head] = 0;
            }
            nxt_node[op.a] = 0;
        }
        else if (op.k == k) {
            query_answer[op.id] = query_string_product(op.s, k, counter);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> worm_len[i];
    }

    ops.reserve(m);
    int query_cnt = 0;
    for (int i = 1; i <= m; i++) {
        Operation op;
        cin >> op.type;
        op.id = -1;
        op.a = op.b = op.k = 0;
        op.s.clear();

        if (op.type == 1) {
            cin >> op.a >> op.b;
        }
        else if (op.type == 2) {
            cin >> op.a;
        }
        else {
            cin >> op.s >> op.k;
            op.id = query_cnt++;
            if (!need_k[op.k]) {
                need_k[op.k] = true;
                query_k_list.push_back(op.k);
            }
        }
        ops.push_back(op);
    }

    query_answer.assign(query_cnt, 0);
    for (int i = 0; i < (int)query_k_list.size(); i++) {
        simulate_one_k(query_k_list[i]);
    }

    for (int i = 0; i < query_cnt; i++) {
        cout << query_answer[i] << '\n';
    }

    return 0;
}
