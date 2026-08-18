/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-18 00:51
 * update_at: 2026-08-18 01:19
 */
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// main.cpp：O(n log^2 n) 满分做法。
// 先筛选可能的第一次聚拢中心，再共享历史事件模拟候选根。

// 基准根上的树链剖分、欧拉序 RMQ 与路径工具。
struct Tree {
  int n, cur = 0, o1 = 0;
  vector<int> siz, par, dep, in, out, top, seq, fir, eul, lg;
  vector<vector<int>> rmq;
  vector<vector<int>> G;
  Tree(int size = 0)
      : n(size), siz(size), par(size), dep(size), in(size), out(size),
        top(size), seq(size), fir(size), G(size) {}
  void addEdge(int u, int v) {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  void init(int rt = 0) {
    par[rt] = -1;
    dfs1(rt);
    dfs2(rt, rt);
    dfs3(rt);
    lg.resize((int)eul.size() + 1);
    for (int i = 2; i <= (int)eul.size(); i++) lg[i] = lg[i / 2] + 1;
    rmq.push_back(eul);
    for (int k = 1; (1 << k) <= (int)eul.size(); k++) {
      int len = (int)eul.size() - (1 << k) + 1;
      rmq.push_back(vector<int>(len));
      for (int i = 0; i < len; i++) {
        int u = rmq[k - 1][i];
        int v = rmq[k - 1][i + (1 << (k - 1))];
        rmq[k][i] = dep[u] < dep[v] ? u : v;
      }
    }
  }
  void dfs1(int u) {
    if (par[u] != -1) {
      G[u].erase(find(G[u].begin(), G[u].end(), par[u]));
    }
    siz[u] = 1;
    for (int i = 0; i < (int)G[u].size(); i++) {
      int &v = G[u][i];
      par[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[G[u][0]]) {
        swap(v, G[u][0]);
      }
    }
  }
  void dfs2(int u, int x) {
    in[u] = cur++;
    seq[in[u]] = u;
    top[u] = x;
    for (int i = 0; i < (int)G[u].size(); i++) {
      int v = G[u][i];
      dfs2(v, v == G[u][0] ? x : v);
    }
    out[u] = cur;
  }
  void dfs3(int u) {
    fir[u] = (int)eul.size();
    eul.push_back(u);
    for (int i = 0; i < (int)G[u].size(); i++) {
      int v = G[u][i];
      dfs3(v);
      eul.push_back(u);
    }
  }
  int lca(int u, int v) {
    int l = fir[u], r = fir[v];
    if (l > r) swap(l, r);
    int k = lg[r - l + 1];
    u = rmq[k][l];
    v = rmq[k][r - (1 << k) + 1];
    return dep[u] < dep[v] ? u : v;
  }
  int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
  }
  bool on_path(int p, int u, int v) {
    return (is_ancester(p, u) || is_ancester(p, v)) && dep[p] >= dep[lca(u, v)];
  }
  int jump(int u, int k) {
    if (dep[u] < k) {
      return -1;
    }
    int d = dep[u] - k;
    while (dep[top[u]] > d) {
      u = par[top[u]];
    }
    return seq[in[u] + d - dep[u]];
  }
  bool is_ancester(int u, int v) {
    return in[u] <= in[v] && in[v] < out[u];
  }
  int findChild(int u, int v) {
    assert(u != v);
    if (!is_ancester(u, v)) {
      return par[u];
    }
    int left = 0;
    int right = (int)G[u].size();
    while (left < right) {
      int mid = (left + right) / 2;
      if (in[G[u][mid]] <= in[v]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    assert(left > 0);
    return G[u][left - 1];
  }
};

constexpr int N = 1e5 + 5;
constexpr int INF = 1e9;

int n;
vector<int> G[N];
Tree tr;

// 固定第一次聚拢中心后，用红点压缩树求这个起点的最优结果。
struct FixedRootSolver {
  int root;
  vector<int> parent, order, root_order, answer_buffer;
  vector<int> minimum_child, red_parent;
  vector<int> bucket, next_bucket, red_head, red_tail, red_to, red_next;
  vector<char> active, in_frontier, is_red;
  set<pair<int, int> > frontier, visible_red;

  FixedRootSolver(int start)
      : root(start), parent(n, -1), answer_buffer(2 * n + 5),
        minimum_child(n, INF), red_parent(n, -2), bucket(n, -1),
        next_bucket(n, -1), red_head(n, -1), red_tail(n, -1),
        active(n), in_frontier(n), is_red(n) {
    order.reserve(n);
    root_order.reserve(G[root].size() + 1);
    red_to.reserve(n);
    red_next.reserve(n);
  }

  int child_count(int u) {
    return (int)G[u].size() - (u != root);
  }

  int first_child(int u) {
    for (int i = 0; i < (int)G[u].size(); i++) {
      int v = G[u][i];
      if (v != parent[u]) return v;
    }
    return INF;
  }

  void add_red_edge(int x, int y) {
    int edge = (int)red_to.size();
    red_to.push_back(y);
    red_next.push_back(-1);
    if (red_head[x] == -1) {
      red_head[x] = red_tail[x] = edge;
    } else {
      red_next[red_tail[x]] = edge;
      red_tail[x] = edge;
    }
  }

  // 删除一个已失效红点，并把它的红色儿子接到上一层。
  void erase_red(int x) {
    if (!is_red[x]) return;
    is_red[x] = 0;
    int p = red_parent[x];
    if (p == -1) visible_red.erase(make_pair(minimum_child[x], x));
    for (int edge = red_head[x]; edge != -1; edge = red_next[edge]) {
      int y = red_to[edge];
      if (!is_red[y] || red_parent[y] != x) continue;
      red_parent[y] = p;
      if (p == -1) {
        visible_red.insert(make_pair(minimum_child[y], y));
      } else {
        add_red_edge(p, y);
      }
    }
  }

  int first_not_less(int u, int value) {
    if (u == root) {
      vector<int>::iterator it = lower_bound(root_order.begin(), root_order.end(), value);
      return it == root_order.end() ? -1 : *it;
    }
    vector<int>::iterator it = lower_bound(G[u].begin(), G[u].end(), value);
    while (it != G[u].end() && *it == parent[u]) ++it;
    return it == G[u].end() ? -1 : *it;
  }

  vector<int> solve() {
    order.push_back(root);
    for (int i = 0; i < (int)order.size(); i++) {
      int u = order[i];
      for (int j = 0; j < (int)G[u].size(); j++) {
        int v = G[u][j];
        if (v == parent[u]) continue;
        parent[v] = u;
        order.push_back(v);
      }
    }

    bool root_inserted = false;
    for (int i = 0; i < (int)G[root].size(); i++) {
      int v = G[root][i];
      if (!root_inserted && root < v) {
        root_order.push_back(root);
        root_inserted = true;
      }
      root_order.push_back(v);
    }
    if (!root_inserted) root_order.push_back(root);

    int left = n;
    int right = n;
    for (int i = 0; i < (int)root_order.size(); i++) {
      answer_buffer[right++] = root_order[i];
    }
    int head = answer_buffer[left];
    int length = right - left;

    for (int u = 0; u < n; u++) {
      if (u == root || child_count(u) == 0) continue;
      active[u] = 1;
      minimum_child[u] = first_child(u);
      if (minimum_child[u] < head) {
        is_red[u] = 1;
        next_bucket[u] = bucket[minimum_child[u]];
        bucket[minimum_child[u]] = u;
      }
    }
    for (int i = 0; i < (int)G[root].size(); i++) {
      int v = G[root][i];
      if (!active[v]) continue;
      in_frontier[v] = 1;
      frontier.insert(make_pair(minimum_child[v], v));
    }

    vector<pair<int, int> > stack;
    stack.push_back(make_pair(root, -1));
    while (!stack.empty()) {
      int u = stack.back().first;
      int last_red = stack.back().second;
      stack.pop_back();
      for (int i = (int)G[u].size() - 1; i >= 0; i--) {
        int v = G[u][i];
        if (v == parent[u]) continue;
        if (is_red[v]) {
          red_parent[v] = last_red;
          if (last_red == -1) {
            visible_red.insert(make_pair(minimum_child[v], v));
          } else {
            add_red_edge(last_red, v);
          }
          stack.push_back(make_pair(v, v));
        } else {
          stack.push_back(make_pair(v, last_red));
        }
      }
    }

    while (length < n) {
      int x = -1;
      int bad = -1;
      int after_bad = -1;
      if (!visible_red.empty()) {
        bad = visible_red.rbegin()->second;
        after_bad = first_not_less(bad, head);
      }

      int first_frontier = -1;
      set<pair<int, int> >::iterator it = frontier.upper_bound(make_pair(head, INF));
      if (it != frontier.end()) first_frontier = it->second;

      if (first_frontier != -1 &&
          (bad == -1 || !in_frontier[bad] ||
           (after_bad != -1 && minimum_child[first_frontier] < after_bad))) {
        x = first_frontier;
      } else {
        x = bad;
      }
      if (x == -1) break;

      if (in_frontier[x]) {
        frontier.erase(make_pair(minimum_child[x], x));
        in_frontier[x] = 0;
      }
      erase_red(x);

      int old_head = head;
      if (x == root) {
        vector<int>::iterator cut = lower_bound(root_order.begin(), root_order.end(), old_head);
        vector<int>::iterator it_left = cut;
        while (it_left != root_order.begin()) answer_buffer[--left] = *--it_left;
        for (vector<int>::iterator it_right = cut; it_right != root_order.end(); ++it_right) {
          answer_buffer[right++] = *it_right;
        }
      } else {
        int cut = (int)(lower_bound(G[x].begin(), G[x].end(), old_head) - G[x].begin());
        for (int i = cut - 1; i >= 0; i--) {
          if (G[x][i] != parent[x]) answer_buffer[--left] = G[x][i];
        }
        for (int i = cut; i < (int)G[x].size(); i++) {
          if (G[x][i] != parent[x]) answer_buffer[right++] = G[x][i];
        }
      }
      length = right - left;

      active[x] = 0;
      for (int i = 0; i < (int)G[x].size(); i++) {
        int v = G[x][i];
        if (v == parent[x] || !active[v]) continue;
        in_frontier[v] = 1;
        frontier.insert(make_pair(minimum_child[v], v));
      }

      int new_head = answer_buffer[left];
      if (new_head < old_head) {
        for (int value = old_head - 1; value >= new_head; value--) {
          for (int y = bucket[value]; y != -1; y = next_bucket[y]) erase_red(y);
        }
        head = new_head;
      }
    }

    return vector<int>(answer_buffer.begin() + left, answer_buffer.begin() + right);
  }
};

vector<int> solve_fixed_root(int root) {
  FixedRootSolver solver(root);
  return solver.solve();
}

struct DSU {
  vector<int> f, s;
  DSU(int size = 0) : f(size), s(size, 1) {
    iota(f.begin(), f.end(), 0);
  }
  int find(int u) {
    while (u != f[u]) u = f[u] = f[f[u]];
    return u;
  }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return 0;
    s[v] += s[u], f[u] = v;
    return 1;
  }
  bool same(int u, int v) {return find(u) == find(v);}
  int size(int u) {return s[find(u)];}
} dsu;

struct BIT {
  int n;
  vector<int> a;
  BIT(int size = 0) : n(size), a(size + 1) {}
  void add(int x, int v) {
    for (int i = x + 1; i <= n; i += i & -i) a[i] += v;
  }
  int qry(int x) {
    int r = 0;
    for (int i = x; i > 0; i -= i & -i) r += a[i];
    return r;
  }
  int sum(int l, int r) {
    return qry(r) - qry(l);
  }
};

struct EraseSet {
  int n, cnt;
  vector<int> f;
  vector<char> on;
  EraseSet(int size = 0) : n(size), cnt(size), f(size + 1), on(size, 1) {
    iota(f.begin(), f.end(), 0);
  }
  int find(int u) {
    while (u != f[u]) u = f[u] = f[f[u]];
    return u;
  }
  void erase(int u) {
    if (!on[u]) return;
    on[u] = 0;
    cnt--;
    f[u] = find(u + 1);
  }
  bool has(int u) {
    return 0 <= u && u < n && on[u];
  }
  int first() {
    return find(0);
  }
  int size() {
    return cnt;
  }
};

// 对每个点的有序邻接表维护“下一个还没有被消费的邻点”。
struct NextSet {
  int n;
  vector<int> off, f;
  NextSet(int size = 0) : n(size), off(size + 1) {
    for (int u = 0; u < n; u++) off[u + 1] = off[u] + (int)G[u].size() + 1;
    f.resize(off[n]);
    iota(f.begin(), f.end(), 0);
  }
  int find(int u) {
    while (u != f[u]) u = f[u] = f[f[u]];
    return u;
  }
  void erase(int u, int v) {
    int p = (int)(lower_bound(G[u].begin(), G[u].end(), v) - G[u].begin());
    assert(p < (int)G[u].size() && G[u][p] == v);
    p += off[u];
    if (find(p) == p) f[p] = find(p + 1);
  }
  int first(int u) {
    int p = find(off[u]);
    return p == off[u + 1] - 1 ? INF : G[u][p - off[u]];
  }
  int lower(int u, int x) {
    int p = (int)(lower_bound(G[u].begin(), G[u].end(), x) - G[u].begin()) + off[u];
    p = find(p);
    return p == off[u + 1] - 1 ? INF : G[u][p - off[u]];
  }
};

// 欧拉序线段树套 AVL 树，维护对不同候选根有效的历史红点。
struct RedTree {
  struct Node {
    int l = -1, r = -1, id = -1;
    unsigned char hei = 1, act = 0, any = 0;
  };
  int n, s = 1;
  vector<int> rt, val;
  vector<unsigned char> built;
  vector<Node> a;
  RedTree(int size = 0) : n(size), val(size, -1), built(size) {
    while (s < n) s *= 2;
    rt.assign(2 * s, -1);
    a.reserve(35 * n);
  }
  int xid(int p) {
    return a[p].id;
  }
  int height(int p) {
    return p == -1 ? 0 : a[p].hei;
  }
  bool active(int p) {
    return a[p].act;
  }
  bool has(int p) {
    return p != -1 && a[p].any;
  }
  bool less_key(int x, int y) {
    return val[x] != val[y] ? val[x] < val[y] : x < y;
  }
  bool less_key(int v, int x, int y) {
    return v != val[y] ? v < val[y] : x < y;
  }
  void pull(int p) {
    a[p].hei = static_cast<unsigned char>(
        max(height(a[p].l), height(a[p].r)) + 1);
    a[p].any = active(p) || has(a[p].l) || has(a[p].r);
  }
  void pull_any(int p) {
    a[p].any = active(p) || has(a[p].l) || has(a[p].r);
  }
  int node(int x, bool on) {
    int p = (int)a.size();
    a.push_back({-1, -1, x, 1, static_cast<unsigned char>(on), static_cast<unsigned char>(on)});
    return p;
  }
  int left_rotate(int p) {
    int q = a[p].r;
    a[p].r = a[q].l;
    a[q].l = p;
    pull(p);
    pull(q);
    return q;
  }
  int right_rotate(int p) {
    int q = a[p].l;
    a[p].l = a[q].r;
    a[q].r = p;
    pull(p);
    pull(q);
    return q;
  }
  int balance(int p) {
    pull(p);
    if (height(a[p].l) - height(a[p].r) == 2) {
      if (height(a[a[p].l].l) < height(a[a[p].l].r)) a[p].l = left_rotate(a[p].l);
      return right_rotate(p);
    }
    if (height(a[p].r) - height(a[p].l) == 2) {
      if (height(a[a[p].r].r) < height(a[a[p].r].l)) a[p].r = right_rotate(a[p].r);
      return left_rotate(p);
    }
    return p;
  }
  int ins(int p, int x, int v, bool on) {
    if (p == -1) return node(x, on);
    if (less_key(v, x, xid(p))) {
      a[p].l = ins(a[p].l, x, v, on);
    } else {
      assert(less_key(xid(p), x));
      a[p].r = ins(a[p].r, x, v, on);
    }
    return balance(p);
  }
  bool set_node(int p, int x, int v, bool on) {
    assert(p != -1);
    if (xid(p) == x) {
      a[p].act = on;
    } else if (less_key(v, x, xid(p))) {
      if (!set_node(a[p].l, x, v, on)) return false;
    } else {
      if (!set_node(a[p].r, x, v, on)) return false;
    }
    bool old = has(p);
    pull_any(p);
    return old != has(p);
  }
  int last(int p) {
    assert(has(p));
    if (has(a[p].r)) return last(a[p].r);
    if (active(p)) return xid(p);
    return last(a[p].l);
  }
  int pred(int p, int h) {
    if (!has(p)) return -1;
    int x = xid(p);
    if (val[x] >= h) return pred(a[p].l, h);
    int q = pred(a[p].r, h);
    if (q != -1) return q;
    if (active(p)) return x;
    return has(a[p].l) ? last(a[p].l) : -1;
  }
  void change_range(int l, int r, int x, bool on, bool first) {
    int v = val[x];
    l += s;
    r += s;
    if (first) {
      for (; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) rt[l] = ins(rt[l], x, v, on), l++;
        if (r % 2 == 1) --r, rt[r] = ins(rt[r], x, v, on);
      }
    } else {
      for (; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) set_node(rt[l++], x, v, on);
        if (r % 2 == 1) set_node(rt[--r], x, v, on);
      }
    }
  }
  void add(int x, int v, int d) {
    bool first = !built[x];
    if (first) {
      val[x] = v;
      built[x] = 1;
    } else {
      assert(val[x] == v);
    }
    bool on = d == 1;
    int first_neighbor = G[x][0];
    int second_neighbor = (int)G[x].size() > 1 ? G[x][1] : INF;
    if (v == first_neighbor) {
      if (tr.par[first_neighbor] == x) {
        if (tr.in[first_neighbor] > 0) {
          change_range(0, tr.in[first_neighbor], x, on, first);
        }
        if (tr.out[first_neighbor] < n) {
          change_range(tr.out[first_neighbor], n, x, on, first);
        }
      } else {
        change_range(tr.in[x], tr.out[x], x, on, first);
      }
    } else {
      assert(v == second_neighbor);
      if (tr.par[first_neighbor] == x) {
        change_range(tr.in[first_neighbor], tr.out[first_neighbor], x, on, first);
      } else {
        if (tr.in[x] > 0) change_range(0, tr.in[x], x, on, first);
        if (tr.out[x] < n) change_range(tr.out[x], n, x, on, first);
      }
    }
  }
  pair<int, int> qry(int x, int h) {
    int res = -1;
    for (int p = x + s; p; p /= 2) {
      int q = pred(rt[p], h);
      if (q != -1 && (res == -1 || less_key(res, q))) res = q;
    }
    return res == -1 ? pair<int, int>{-1, -1} : pair<int, int>{val[res], res};
  }
};

// 合并已经模拟完成的连通区域，并维护区域边界的最小值。
struct DoneDSU {
  struct Node {
    int l = -1, r = -1, d = 1, v;
  };
  int n;
  vector<int> f, s, mn1, mn2;
  vector<char> on;
  vector<int> br;
  vector<Node> hp;
  vector<set<pair<int, int>>> bw;
  DoneDSU(int size = 0)
      : n(size), f(size), s(size, 1), mn1(size), mn2(size, INF),
        on(size), br(size, -1), bw(size) {
    iota(f.begin(), f.end(), 0);
    iota(mn1.begin(), mn1.end(), 0);
    hp.reserve(max(0, size - 1));
  }
  int find(int u) {
    while (u != f[u]) u = f[u] = f[f[u]];
    return u;
  }
  int val(int u, int p) {
    if (G[u].empty()) return INF;
    if (G[u][0] != p) return G[u][0];
    return (int)G[u].size() > 1 ? G[u][1] : INF;
  }
  void ins_min(int r, int x) {
    if (x < mn1[r]) {
      mn2[r] = mn1[r];
      mn1[r] = x;
    } else if (x != mn1[r] && x < mn2[r]) {
      mn2[r] = x;
    }
  }
  int meld(int u, int v) {
    if (u == -1) return v;
    if (v == -1) return u;
    if (hp[v].v < hp[u].v) swap(u, v);
    hp[u].r = meld(hp[u].r, v);
    int dl = hp[u].l == -1 ? 0 : hp[hp[u].l].d;
    int dr = hp[u].r == -1 ? 0 : hp[hp[u].r].d;
    if (dl < dr) swap(hp[u].l, hp[u].r);
    hp[u].d = dr + 1;
    return u;
  }
  int push(int r, int x) {
    int p = (int)hp.size();
    hp.push_back({-1, -1, 1, x});
    return meld(r, p);
  }
  void clean(int r) {
    while (br[r] != -1 && on[hp[br[r]].v]) {
      br[r] = meld(hp[br[r]].l, hp[br[r]].r);
    }
  }
  int merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return u;
    int su = s[u] + (int)bw[u].size();
    int sv = s[v] + (int)bw[v].size();
    if (su < sv) swap(u, v);
    f[v] = u;
    s[u] += s[v];
    ins_min(u, mn1[v]);
    ins_min(u, mn2[v]);
    br[u] = meld(br[u], br[v]);
    br[v] = -1;
    bw[u].merge(bw[v]);
    bw[v].clear();
    return u;
  }
  void add(int x) {
    assert(!on[x]);
    on[x] = 1;
    for (int i = 0; i < (int)G[x].size(); i++) {
      int y = G[x][i];
      if (!on[y]) {
        br[x] = push(br[x], y);
        int w = val(y, x);
        if (w != INF) bw[x].insert(make_pair(w, y));
      }
    }
    for (int i = 0; i < (int)G[x].size(); i++) {
      int y = G[x][i];
      if (on[y]) {
        int r = find(y);
        int w = val(x, y);
        if (w != INF) bw[r].erase(make_pair(w, x));
        merge(x, r);
      }
    }
  }
  int low(int r, int rt) {
    r = find(r);
    clean(r);
    int res = mn1[r] == rt ? mn2[r] : mn1[r];
    if (br[r] != -1) res = min(res, hp[br[r]].v);
    return res;
  }
  int nxt(int r, int h) {
    r = find(r);
    set<pair<int, int> >::iterator it = bw[r].upper_bound(make_pair(h, INF));
    return it == bw[r].end() ? -1 : it->second;
  }
  bool same(int u, int v) {
    return find(u) == find(v);
  }
};

// 在线筛选第一次聚拢中心，并让仍存活的候选根共享比较过程。
struct CandidateFinder {
  vector<int> directed_to;
  DSU root_dsu;
  BIT path_bit;
  EraseSet candidate_set, process_set;
  vector<int> prefix_mark, prefix_stack, visited;
  DoneDSU done;

  int event_count;
  vector<int> event_key, previous_event;
  vector<int> red_tag, red_event;
  vector<char> red_on;
  RedTree red_tree;
  bool candidate_alive;
  vector<pair<int, int> > pending_red;
  vector<int> temporary_red;
  vector<pair<int, int> > direct_stack;

  int current_candidate;
  bool current_candidate_alive;
  int last_vertex;

  int candidate;
  int candidate_version, candidate_cut, candidate_head;
  int block_vertex, block_limit;
  bool root_finished;
  vector<char> used_vertex;
  NextSet remaining;
  vector<int> parent_version, parent_value;
  int candidate_position;

  CandidateFinder()
      : directed_to(n, -1), root_dsu(n), path_bit(n),
        candidate_set(n), process_set(n), prefix_mark(n), visited(n), done(n),
        event_count(0), event_key(n), previous_event(n, -1),
        red_tag(n, -1), red_event(n, -1), red_on(n), red_tree(n),
        candidate_alive(false), current_candidate(-1),
        current_candidate_alive(false), last_vertex(-1), candidate(-1),
        candidate_version(0), candidate_cut(0), candidate_head(-1),
        block_vertex(-1), block_limit(0), root_finished(false),
        used_vertex(n), remaining(n), parent_version(n, -1),
        parent_value(n), candidate_position(0) {
    prefix_stack.reserve(n);
    pending_red.reserve(n);
    temporary_red.reserve(n);
    direct_stack.reserve(n);
    iota(event_key.begin(), event_key.end(), 0);
  }

  void put_red(int from, int x) {
    if (x == -1 || G[x].empty() || done.on[x] || red_on[x]) return;
    int first = G[x][0];
    int second = (int)G[x].size() > 1 ? G[x][1] : INF;
    if (from != first && from != second) return;
    red_tree.add(x, from, 1);
    red_on[x] = 1;
  }

  void take_red(int x) {
    if (!red_on[x]) return;
    red_tree.add(x, red_tag[x], -1);
    red_on[x] = 0;
  }

  void add_red(int event_id, int from, int x) {
    if (x == -1 || G[x].empty()) return;
    int first = G[x][0];
    int second = (int)G[x].size() > 1 ? G[x][1] : INF;
    if (from != first && from != second) return;
    red_tag[x] = from;
    red_event[x] = event_id;
    if (candidate_alive) {
      pending_red.push_back(make_pair(from, x));
    } else {
      put_red(from, x);
    }
  }

  void flush_red() {
    for (int i = 0; i < (int)pending_red.size(); i++) {
      put_red(pending_red[i].first, pending_red[i].second);
    }
    pending_red.clear();
  }

  void restore_red() {
    for (int i = 0; i < (int)temporary_red.size(); i++) {
      int x = temporary_red[i];
      if (!done.on[x]) put_red(red_tag[x], x);
    }
    temporary_red.clear();
  }

  void add_event(int from, int type, int x = -1) {
    if (from == -1) return;
    int event_id = event_count++;
    if (type != 0 && x != -1) {
      event_key[x] = from;
      previous_event[x] = event_id;
      add_red(event_id, from, x);
    }
  }

  // 给已经确定朝向的一整棵分支定向，并从候选根集合中删除它。
  void direct_branch(int u, int parent) {
    direct_stack.clear();
    direct_stack.push_back(make_pair(u, parent));
    while (!direct_stack.empty()) {
      int x = direct_stack.back().first;
      int from = direct_stack.back().second;
      direct_stack.pop_back();
      if (visited[x] && visited[from]) dsu.merge(x, from);
      if (!candidate_set.has(x)) continue;
      directed_to[x] = from;
      root_dsu.merge(x, from);
      candidate_set.erase(x);
      for (int i = 0; i < (int)G[x].size(); i++) {
        int y = G[x][i];
        if (y == from || !candidate_set.has(y)) continue;
        direct_stack.push_back(make_pair(y, x));
      }
    }
  }

  int query_path(int u, int v) {
    int result = 0;
    while (tr.top[u] != tr.top[v]) {
      if (tr.dep[tr.top[u]] < tr.dep[tr.top[v]]) swap(u, v);
      result += path_bit.sum(tr.in[tr.top[u]], tr.in[u] + 1);
      u = tr.par[tr.top[u]];
    }
    if (tr.dep[u] > tr.dep[v]) swap(u, v);
    result += path_bit.sum(tr.in[u], tr.in[v] + 1);
    return result;
  }

  void add_prefix(int x, int from = -1) {
    if (x != -1 && prefix_mark[x] == 0) {
      prefix_stack.push_back(x);
      prefix_mark[x] = 1;
      path_bit.add(tr.in[x], 1);
      add_event(from, 1, x);
    } else if (x != -1 && from != -1 && event_key[x] < from && from < x &&
               !(current_candidate_alive && from == current_candidate) &&
               prefix_mark[from] == 0 && previous_event[x] != -1) {
      int event_id = previous_event[x];
      int old_key = event_key[x];
      prefix_stack.push_back(from);
      prefix_mark[from] = 1;
      path_bit.add(tr.in[from], 1);
      event_key[from] = old_key;
      event_key[x] = from;
      previous_event[from] = event_id;
    }
  }

  bool valid(int x, int target = -1) {
    if (candidate_set.has(x)) return true;
    if (directed_to[x] == -1) return false;
    if (directed_to[directed_to[x]] == -1) return true;
    int count = query_path(directed_to[x], root_dsu.find(x));
    if (count == 0) return true;
    if (count == 1 && prefix_mark[directed_to[x]] == 1 &&
        !prefix_stack.empty() && prefix_stack.back() == directed_to[x]) {
      return target == -1 || tr.dist(target, x) <= 2;
    }
    return false;
  }

  void mark_used(int x) {
    if (used_vertex[x]) return;
    used_vertex[x] = 1;
    for (int i = 0; i < (int)G[x].size(); i++) {
      remaining.erase(G[x][i], x);
    }
  }

  int candidate_parent(int u) {
    if (u == candidate) return -1;
    if (parent_version[u] != candidate_version) {
      parent_version[u] = candidate_version;
      parent_value[u] = tr.findChild(u, candidate);
    }
    return parent_value[u];
  }

  int candidate_minimum_child(int u) {
    int parent = candidate_parent(u);
    if (G[u].empty()) return INF;
    if (G[u][0] != parent) return G[u][0];
    return (int)G[u].size() > 1 ? G[u][1] : INF;
  }

  void finish_component(int u) {
    if (!done.on[u]) {
      assert(used_vertex[u]);
      for (int i = 0; i < (int)G[u].size(); i++) {
        assert(used_vertex[G[u][i]]);
      }
      take_red(u);
      done.add(u);
    }
    candidate_head = min(candidate_head, done.low(u, candidate));
  }

  bool is_open(int u) {
    if (u == candidate || done.on[u]) return false;
    int parent = candidate_parent(u);
    return parent != -1 && done.on[parent] && done.same(parent, candidate);
  }

  int first_open_vertex() {
    return done.nxt(candidate, candidate_head);
  }

  int blocking_red_vertex() {
    if (candidate_head <= 0) return -1;
    pair<int, int> result = red_tree.qry(candidate_position, candidate_head);
    int tag = result.first;
    int u = result.second;
    if (u == -1) return -1;
    assert(!done.on[u] && red_on[u]);
    assert(red_tag[u] == tag && red_event[u] < candidate_cut &&
           candidate_minimum_child(u) == tag);
    return u;
  }

  void expand_candidate(int u) {
    assert(is_open(u));
    int old_head = candidate_head;
    block_vertex = u;
    block_limit = old_head;
    int value = candidate_minimum_child(u);
    if (value < candidate_head) {
      int event_id = red_event[u];
      if (event_id != -1 && event_id < candidate_cut &&
          red_tag[u] == value && red_on[u]) {
        take_red(u);
        temporary_red.push_back(u);
      }
      candidate_head = value;
    }
  }

  // 返回当前候选根还会产生的下一个字符。
  int peek_candidate() {
    while (true) {
      if (!root_finished) {
        int u = used_vertex[candidate] ? INF : candidate;
        u = min(u, remaining.first(candidate));
        if (u != INF) return u;
        finish_component(candidate);
        root_finished = true;
      }
      if (block_vertex != -1) {
        int v = remaining.lower(block_vertex, block_limit);
        if (v != INF) return v;
        finish_component(block_vertex);
        block_vertex = -1;
      }

      int bad = blocking_red_vertex();
      int after_bad = -1;
      if (bad != -1) {
        int parent = candidate_parent(bad);
        vector<int>::iterator it = lower_bound(G[bad].begin(), G[bad].end(), candidate_head);
        while (it != G[bad].end() && *it == parent) ++it;
        if (it != G[bad].end()) after_bad = *it;
      }
      int first = first_open_vertex();
      int u;
      if (first != -1 &&
          (bad == -1 || !is_open(bad) ||
           (after_bad != -1 && candidate_minimum_child(first) < after_bad))) {
        u = first;
      } else {
        u = bad;
      }
      if (u == -1) return INF;
      expand_candidate(u);
    }
  }

  void add_candidate(int root) {
    if (candidate_alive) return;
    restore_red();
    flush_red();
    candidate = root;
    current_candidate = root;
    current_candidate_alive = true;
    candidate_alive = true;
    candidate_version++;
    candidate_position = tr.in[candidate];
    candidate_cut = event_count;
    root_finished = false;
    block_vertex = -1;
    block_limit = 0;
    candidate_head = G[root].empty() ? root : min(root, G[root][0]);
  }

  int check_candidate(int x) {
    if (!candidate_alive) return -1;
    int y = peek_candidate();
    if (y == INF) return -1;
    if (y < x) return candidate;
    if (y > x) {
      candidate_alive = false;
      current_candidate_alive = false;
      restore_red();
      flush_red();
      return -1;
    }
    mark_used(y);
    return -1;
  }

  // 处理当前最小未处理点，必要时继续给分支定向。
  int process_vertex(int x) {
    for (int i = 0; i < (int)G[x].size(); i++) {
      int y = G[x][i];
      if (visited[y] && directed_to[y] == -1) {
        assert(candidate_set.has(y));
        assert(last_vertex == y);
        add_candidate(y);
      }
    }
    process_set.erase(x);
    while (process_set.size() > 0) {
      int y = process_set.first();
      if (candidate_set.has(y) || valid(y, x)) {
        int found = check_candidate(y);
        if (found != -1) return found;
        int distance = tr.dist(x, y);
        if (distance >= 3) {
          int u = tr.findChild(x, y);
          int v = tr.findChild(u, y);
          if (!candidate_set.has(v)) {
            process_set.erase(y);
            continue;
          }
          if (last_vertex != -1 && u != last_vertex) {
            add_prefix(x, last_vertex);
            last_vertex = -1;
          }
          direct_branch(u, v);
          add_prefix(directed_to[x], x);
        } else if (distance == 2) {
          int u = tr.findChild(x, y);
          if (!candidate_set.has(u)) {
            process_set.erase(y);
            continue;
          }
          if (last_vertex != -1 && u != last_vertex) add_prefix(x, last_vertex);
          direct_branch(x, u);
          add_prefix(directed_to[x], x);
        } else {
          if (last_vertex != -1 && y != last_vertex) add_prefix(x, last_vertex);
          for (int i = 0; i < (int)G[x].size(); i++) {
            int v = G[x][i];
            if (v != y && directed_to[v] != x) direct_branch(v, x);
          }
          last_vertex = x;
        }
        break;
      }
      process_set.erase(y);
    }
    return -1;
  }

  vector<int> find_answer() {
    while (candidate_set.size() > 2) {
      int x = process_set.first();
      visited[x] = 1;
      mark_used(x);
      for (int i = 0; i < (int)G[x].size(); i++) {
        int y = G[x][i];
        if (visited[y] && (directed_to[y] == x || directed_to[x] == y)) {
          dsu.merge(x, y);
        }
      }

      if (candidate_set.has(x)) {
        int found = process_vertex(x);
        if (found != -1) return solve_fixed_root(found);
      } else {
        if (!valid(x)) {
          process_set.erase(x);
          continue;
        }
        add_prefix(directed_to[x], x);
        process_set.erase(x);
        if (candidate_set.has(directed_to[x])) {
          while (process_set.size() > 0) {
            int y = process_set.first();
            if (candidate_set.has(y) || valid(y, x)) {
              int found = check_candidate(y);
              if (found != -1) return solve_fixed_root(found);
              if (tr.dist(x, y) >= 3) {
                int u = tr.findChild(x, y);
                int v = tr.findChild(u, y);
                if (u != directed_to[x]) {
                  process_set.erase(y);
                  continue;
                }
                direct_branch(u, v);
              }
              break;
            }
            process_set.erase(y);
          }
          continue;
        }
      }
    }

    vector<int> answer(n, INF);
    for (int root = candidate_set.first(); root < n;
         root = candidate_set.find(root + 1)) {
      vector<int> current = solve_fixed_root(root);
      if (current < answer) answer = current;
    }
    if (candidate_alive && candidate != -1) {
      vector<int> current = solve_fixed_root(candidate);
      if (current < answer) answer = current;
    }
    return answer;
  }
};

vector<int> find_answer() {
  CandidateFinder finder;
  return finder.find_answer();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  tr = Tree(n);
  dsu = DSU(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    G[u].push_back(v);
    G[v].push_back(u);
    tr.addEdge(u, v);
  }
  tr.init();
  for (int i = 0; i < n; i++) sort(G[i].begin(), G[i].end());
  vector<int> answer = find_answer();
  for (int i = 0; i < n; i++) {
    cout << answer[i] + 1 << " \n"[i == n - 1];
  }
  return 0;
}
