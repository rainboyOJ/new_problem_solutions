/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-17 16:56
 * update_at: 2026-09-19 08:29
 */
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

typedef long long ll;

// #define NO_DEBUG // switch debug
#if defined(onlinejudge) || defined(ONLINE_JUDGE) || defined(NO_DEBUG)
#define log(...)
#define fenc
#else
#define log(args...)                                                           \
  {                                                                            \
    cout << "LINE:" << __LINE__ << " : ";                                      \
    string _s = #args;                                                         \
    replace(_s.begin(), _s.end(), ',', ' ');                                   \
    stringstream _ss(_s);                                                      \
    istream_iterator<string> _it(_ss);                                         \
    err(_it, args);                                                            \
  }
#define fenc cout << "================================";
void err(istream_iterator<string> it) {}

template <typename T> void err(istream_iterator<string> it, T a) {
  cerr << *it << " = " << a << "\n";
}

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " = " << a << ", ";
  err(++it, args...);
}
#endif
const int maxn = 1e6 + 5;
int n, m;
int last_answer;
int a[maxn];
int front_pos, back_pos, max_pos;

// ==============================================================================
// 一个用户块同时对应一段连续 id 和一段连续位置，两段长度相同。
// id_map 按 id 左端点索引，pos_map 按位置左端点索引。
// 两张表保存同一个块的正向和反向信息，必须同时插入、同时删除。
// ==============================================================================
struct IdInterval {
  int L, R;      // 用户 id 区间 [L, R]
  int start_pos; // id=L 对应的绝对坐标
};

struct PosInterval {
  int L, R;     // 绝对坐标区间 [L, R]
  int start_id; // pos=L 对应的用户 id
};

map<int, IdInterval> id_map;   // id 左端点 -> id 区间及位置起点
map<int, PosInterval> pos_map; // 位置左端点 -> 位置区间及 id 起点

// 同时向两张表加入一个块：[id_L,id_R] <-> [pos_L,pos_R]。
void insert_interval(int id_L, int id_R, int pos_L) {
  int pos_R = pos_L + (id_R - id_L);
  id_map[id_L] = {id_L, id_R, pos_L};
  pos_map[pos_L] = {pos_L, pos_R, id_L};
}

// 同时从两张表删除一个块。
void erase_interval(int id_L, int pos_L) {
  id_map.erase(id_L);
  pos_map.erase(pos_L);
}

// ==============================================================================
// 动态开点线段树：维护绝对坐标轴上每个坐标是否有人
// 排名 = 坐标上前缀被占用个数；第 k 名 = 第 k 个被占用坐标
// ==============================================================================
// 单点修改次数上限：op2/op3 各做 2 次 update，共 2m 次；
// V=n+2m<=3e8，树深 <= 29，故最多 2e5*29 ≈ 5.8e6 个点。
// 取 6e6 留余量（6e6*3*4B ≈ 72MB）。
const int max_nodes = 6e6 + 5;

struct node {
  int ls, rs, sum;
};
node tree[max_nodes];
int root = 0;

int get_new_node_idx() {
  static int tot = 0;
  return ++tot;
}

// the count of people virtual node in sgt
int default_sum(int l, int r) {
  int L = max(l, m + 1);
  int R = min(r, m + n);
  return L <= R ? (R - L + 1) : 0;
}

void push_up(int p, int l, int r) {
  int mid = (l + r) >> 1;
  int lv = tree[p].ls ? tree[tree[p].ls].sum : default_sum(l, mid);
  int rv = tree[p].rs ? tree[tree[p].rs].sum : default_sum(mid + 1, r);
  tree[p].sum = lv + rv;
}

void update(int &p, int l, int r, int pos, int val) {
  if (!p) {
    p = get_new_node_idx();
    tree[p].sum = default_sum(l, r);
  }

  if (l == r) {
    tree[p].sum = val;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid)
    update(tree[p].ls, l, mid, pos, val);
  else
    update(tree[p].rs, mid + 1, r, pos, val);
  push_up(p, l, r);
}

// 前缀人数：坐标 [1,pos] 内共有多少人，也就是坐标 pos 上用户的名次
int query_rank(int p, int l, int r, int pos) {
  if (!p) return default_sum(max(l, 1), min(r, pos));

  if (l == r) return tree[p].sum;
  int mid = (l + r) >> 1;

  if (pos <= mid) return query_rank(tree[p].ls, l, mid, pos);

  int lv = tree[p].ls ? tree[tree[p].ls].sum : default_sum(l, mid);
  return lv + query_rank(tree[p].rs, mid + 1, r, pos);
}

// 线段树上二分：第 k 个被占用的坐标
int query_kth(int p, int l, int r, int k) {
  if (l == r) return l;
  int mid = (l + r) >> 1;
  int lv = tree[p].ls ? tree[tree[p].ls].sum : default_sum(l, mid);
  if (k <= lv) return query_kth(tree[p].ls, l, mid, k);
  return query_kth(tree[p].rs, mid + 1, r, k - lv);
}

// ==============================================================================
// 区间撕裂：把含 id 的块切成 [L,id-1] [id,id] [id+1,R]，返回 id 的绝对坐标
// ==============================================================================
int split_and_get_pos(int id) {
  map<int, IdInterval>::iterator it = id_map.upper_bound(id);
  --it;
  int L = it->second.L;
  int R = it->second.R;
  int start_pos = it->second.start_pos;

  int target_pos = start_pos + (id - L);

  // 题目保证 id 存在；这里额外保留边界断言，便于检查两张表是否失步。
  assert(L <= id && id <= R);

  if (L != R) { // 不是单点块，需要撕裂
    erase_interval(L, start_pos);

    // 左半段 [L, id-1]
    if (L <= id - 1) {
      insert_interval(L, id - 1, start_pos);
    }

    // 独立单点 [id, id]
    insert_interval(id, id, target_pos);

    // 右半段 [id+1, R]
    if (id + 1 <= R) {
      insert_interval(id + 1, R, target_pos + 1);
    }
  }

  return target_pos;
}

// 已知坐标 pos 处有人，反查用户编号
int get_id_by_pos(int pos) {
  map<int, PosInterval>::iterator it = pos_map.upper_bound(pos);
  --it;
  int L = it->second.L;
  int R = it->second.R;
  int start_id = it->second.start_id;

  assert(L <= pos && pos <= R);
  return start_id + (pos - L);
}

// 把已经撕裂成单点的用户从 old_pos 挪到 new_pos
void move_user(int id, int old_pos, int new_pos) {
  update(root, 1, max_pos, old_pos, 0);
  update(root, 1, max_pos, new_pos, 1);

  erase_interval(id, old_pos);
  insert_interval(id, id, new_pos);
}

void init() {
  // read(n);
  std::cin >> n >> m;
  front_pos = m + 1;
  back_pos = n + m;
  max_pos = n + 2 * m;

  // init first range
  insert_interval(1, n, m + 1);
}

int main() {

  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); // 关闭io同步
  init();
  last_answer = 0;
  for (int i = 1; i <= m; ++i) {
    int op, x, y;
    std::cin >> op >> x;
    x -= last_answer;

    // change id x to y
    if (op == 1) {
      std::cin >> y;
      y -= last_answer;

      int pos = split_and_get_pos(x);
      last_answer = query_rank(root, 1, max_pos, pos);

      // x 已被撕裂成单点, 把该点的编号改成 y
      erase_interval(x, pos);
      insert_interval(y, y, pos);
    }
    // brow id x to first postion
    else if (op == 2) {
      int pos = split_and_get_pos(x);
      last_answer = query_rank(root, 1, max_pos, pos);

      --front_pos; // 占用一个左边预留坐标
      move_user(x, pos, front_pos);
    }
    // brow id x to last postion
    else if (op == 3) {
      int pos = split_and_get_pos(x);
      last_answer = query_rank(root, 1, max_pos, pos);

      ++back_pos; // 占用一个右边预留坐标
      move_user(x, pos, back_pos);
    }
    // find rank k's id
    else if (op == 4) {
      // first : find rank's pos
      int pos = query_kth(root, 1, max_pos, x);
      // second: get id by pos
      last_answer = get_id_by_pos(pos);
    }

    std::cout << last_answer << '\n';
  }

  return 0;
}
