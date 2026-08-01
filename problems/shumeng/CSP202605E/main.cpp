/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 18:00
 */
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#define ALL(s) s.begin(), s.end()
#define SZ(s) int(s.size())

struct Tree {
  int n, cur = 0, o1 = 0;
  vector<int> siz, par, dep, in, out, top, seq, fir, eul, lg, hei, hson, lid, lpos;
  vector<vector<int>> rmq, anc, lad;
  vector<vector<int>> G;
  Tree(int n = 0) : n(n), siz(n), par(n), dep(n), in(n), out(n), top(n), seq(n), fir(n), hei(n), hson(n, -1), lid(n), lpos(n), G(n) {}
  void addEdge(int u, int v) {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  void init(int rt = 0) {
    par[rt] = -1;
    dfs1(rt);
    dfs2(rt, rt);
    dfs4(rt);
    build_ladder(rt);
    dfs3(rt);
    lg.resize(SZ(eul) + 1);
    for (int i = 2; i <= SZ(eul); i++) lg[i] = lg[i / 2] + 1;
    rmq.push_back(eul);
    for (int k = 1; (1 << k) <= SZ(eul); k++) {
      int len = SZ(eul) - (1 << k) + 1;
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
    for (auto &v : G[u]) {
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
    for (auto v : G[u]) {
      dfs2(v, v == G[u][0] ? x : v);
    }
    out[u] = cur;
  }
  void dfs3(int u) {
    fir[u] = SZ(eul);
    eul.push_back(u);
    for (auto v : G[u]) {
      dfs3(v);
      eul.push_back(u);
    }
  }
  void dfs4(int u) {
    hei[u] = 1;
    for (auto v : G[u]) {
      dfs4(v);
      if (hei[v] + 1 > hei[u]) {
        hei[u] = hei[v] + 1;
        hson[u] = v;
      }
    }
  }
  void build_ladder(int rt) {
    anc.push_back(vector<int>(n));
    for (int u = 0; u < n; u++) anc[0][u] = par[u] == -1 ? u : par[u];
    for (int k = 1; (1 << k) <= n; k++) {
      anc.push_back(vector<int>(n));
      for (int u = 0; u < n; u++) anc[k][u] = anc[k - 1][anc[k - 1][u]];
    }
    for (int u = 0; u < n; u++) if (u == rt || hson[par[u]] != u) {
      vector<int> path;
      for (int v = u; v != -1; v = hson[v]) path.push_back(v);
      vector<int> now;
      int v = par[u];
      for (int i = 0; i < SZ(path) && v != -1; i++, v = par[v]) now.push_back(v);
      reverse(ALL(now));
      int p = SZ(now);
      now.insert(now.end(), ALL(path));
      int x = SZ(lad);
      lad.push_back(move(now));
      for (int i = 0; i < SZ(path); i++) {
        lid[path[i]] = x;
        lpos[path[i]] = p + i;
      }
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
    if (!k) return u;
    int b = 31 - __builtin_clz(k);
    u = anc[b][u];
    k -= 1 << b;
    return lad[lid[u]][lpos[u] - k];
  }
  bool is_ancester(int u, int v) {
    return in[u] <= in[v] && in[v] < out[u];
  }
  int findChild(int u, int v) {
    assert(u != v);
    if (!is_ancester(u, v)) {
      return par[u];
    }
    return jump(v, dep[v] - dep[u] - 1);
  }
  int lca(int u, int v, int w) {
    u = min({in[u], in[v], in[w]});
    v = max({in[u], in[v], in[w]});
    return lca(seq[u], seq[v]);
  }
};

constexpr int N = 1e5 + 5;
constexpr int INF = 1e9;

int n;
vector<int> G[N];
Tree tr;

vector<int> sol(int r) {
  vector<int> fa(n, -1), ord;
  ord.reserve(n);
  ord.push_back(r);
  for (int i = 0; i < SZ(ord); i++) {
    int u = ord[i];
    for (auto v : G[u]) {
      if (v == fa[u]) continue;
      fa[v] = u;
      ord.push_back(v);
    }
  }

  auto cnt = [&](int u) {
    return SZ(G[u]) - (u != r);
  };
  auto first = [&](int u) {
    for (auto v : G[u]) if (v != fa[u]) return v;
    return INF;
  };

  vector<int> root;
  root.reserve(G[r].size() + 1);
  bool put = 0;
  for (auto v : G[r]) {
    if (!put && r < v) {
      root.push_back(r);
      put = 1;
    }
    root.push_back(v);
  }
  if (!put) root.push_back(r);

  vector<int> cur(2 * n + 5);
  int L = n, R = n;
  for (auto x : root) cur[R++] = x;
  int head = cur[L], len = R - L;

  vector<int> mn(n, INF), rp(n, -2);
  vector<int> buc(n, -1), nb(n, -1), hd(n, -1), tl(n, -1), to, nx;
  vector<char> act(n), fr(n), red(n);
  set<pair<int, int>> frt, visb;

  to.reserve(n);
  nx.reserve(n);
  auto add_rs = [&](int x, int y) {
    int p = SZ(to);
    to.push_back(y);
    nx.push_back(-1);
    if (hd[x] == -1) {
      hd[x] = tl[x] = p;
    } else {
      nx[tl[x]] = p;
      tl[x] = p;
    }
  };

  for (int u = 0; u < n; u++) {
    if (u == r || !cnt(u)) continue;
    act[u] = 1;
    mn[u] = first(u);
    if (mn[u] < head) {
      red[u] = 1;
      nb[u] = buc[mn[u]];
      buc[mn[u]] = u;
    }
  }
  for (auto v : G[r]) {
    if (!act[v]) continue;
    fr[v] = 1;
    frt.insert({mn[v], v});
  }

  vector<pair<int, int>> st;
  st.push_back({r, -1});
  while (!st.empty()) {
    auto [u, las] = st.back();
    st.pop_back();
    for (int i = SZ(G[u]) - 1; i >= 0; i--) {
      int v = G[u][i];
      if (v == fa[u]) continue;
      if (red[v]) {
        rp[v] = las;
        if (las == -1) {
          visb.insert({mn[v], v});
        } else {
          add_rs(las, v);
        }
        st.push_back({v, v});
      } else {
        st.push_back({v, las});
      }
    }
  }

  auto er = [&](int x) {
    if (!red[x]) return;
    red[x] = 0;
    int p = rp[x];
    if (p == -1) visb.erase({mn[x], x});
    for (int e = hd[x]; e != -1; e = nx[e]) {
      int y = to[e];
      if (!red[y] || rp[y] != x) continue;
      rp[y] = p;
      if (p == -1) {
        visb.insert({mn[y], y});
      } else {
        add_rs(p, y);
      }
    }
  };

  auto ge = [&](int u, int x) {
    if (u == r) {
      auto it = lower_bound(ALL(root), x);
      return it == root.end() ? -1 : *it;
    }
    auto it = lower_bound(ALL(G[u]), x);
    while (it != G[u].end() && *it == fa[u]) ++it;
    return it == G[u].end() ? -1 : *it;
  };

  while (len < n) {
    int x = -1, bad = -1, after = -1;
    if (!visb.empty()) {
      bad = visb.rbegin()->second;
      after = ge(bad, head);
    }

    int fi = -1;
    auto it = frt.upper_bound({head, INF});
    if (it != frt.end()) fi = it->second;

    if (fi != -1 && (bad == -1 || !fr[bad] || (after != -1 && mn[fi] < after))) {
      x = fi;
    } else {
      x = bad;
    }
    if (x == -1) break;

    if (fr[x]) {
      frt.erase({mn[x], x});
      fr[x] = 0;
    }
    er(x);

    int oh = head;
    if (x == r) {
      auto cut = lower_bound(ALL(root), oh);
      for (auto jt = cut; jt != root.begin();) cur[--L] = *--jt;
      for (auto jt = cut; jt != root.end(); ++jt) cur[R++] = *jt;
    } else {
      int cut = lower_bound(ALL(G[x]), oh) - G[x].begin();
      for (int i = cut - 1; i >= 0; i--) {
        if (G[x][i] != fa[x]) cur[--L] = G[x][i];
      }
      for (int i = cut; i < SZ(G[x]); i++) {
        if (G[x][i] != fa[x]) cur[R++] = G[x][i];
      }
    }
    len = R - L;

    act[x] = 0;
    for (auto v : G[x]) {
      if (v == fa[x] || !act[v]) continue;
      fr[v] = 1;
      frt.insert({mn[v], v});
    }

    int nh = cur[L];
    if (nh < oh) {
      for (int val = oh - 1; val >= nh; val--) {
        for (int y = buc[val]; y != -1; y = nb[y]) er(y);
      }
      head = nh;
    }
  }

  return vector<int>(cur.begin() + L, cur.begin() + R);
}
struct DSU {
  vector<int> f, s;
  DSU(int n = 0) : f(n), s(n, 1) {iota(ALL(f), 0);}
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
  BIT(int n = 0) : n(n), a(n + 1) {}
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
  EraseSet(int n = 0) : n(n), cnt(n), f(n + 1), on(n, 1) {
    iota(ALL(f), 0);
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

struct RedBlocks {
  struct Node {
    int l = -1, r = -1, v = 0;
  };
  int n, B, m;
  vector<int> rt;
  vector<Node> a;
  RedBlocks(int n = 0) : n(n) {
    int lg = 32 - __builtin_clz(max(1, n));
    B = max(1, int(sqrt(1.0 * max(1, n) * lg)) + 1);
    m = (n + B - 1) / B;
    rt.assign(m, -1);
  }
  int add(int p, int l, int r, int ql, int qr, int d) {
    if (ql >= r || l >= qr) return p;
    if (p == -1) {
      p = SZ(a);
      a.push_back({});
    }
    if (ql <= l && r <= qr) {
      a[p].v += d;
      assert(a[p].v >= 0);
      return p;
    }
    int md = (l + r) / 2;
    if (ql < md) {
      int x = add(a[p].l, l, md, ql, qr, d);
      a[p].l = x;
    }
    if (md < qr) {
      int y = add(a[p].r, md, r, ql, qr, d);
      a[p].r = y;
    }
    return p;
  }
  void add(int v, int l, int r, int d) {
    if (l >= r) return;
    rt[v / B] = add(rt[v / B], 0, n, l, r, d);
  }
  int qry(int b, int x) {
    int p = rt[b], l = 0, r = n, res = 0;
    while (p != -1) {
      res += a[p].v;
      if (r - l == 1) break;
      int md = (l + r) / 2;
      if (x < md) {
        p = a[p].l;
        r = md;
      } else {
        p = a[p].r;
        l = md;
      }
    }
    return res;
  }
};

struct NextSet {
  int n;
  vector<int> off, f;
  NextSet(int n = 0) : n(n), off(n + 1) {
    for (int u = 0; u < n; u++) off[u + 1] = off[u] + SZ(G[u]) + 1;
    f.resize(off[n]);
    iota(ALL(f), 0);
  }
  int find(int u) {
    while (u != f[u]) u = f[u] = f[f[u]];
    return u;
  }
  void erase(int u, int v) {
    int p = lower_bound(ALL(G[u]), v) - G[u].begin();
    assert(p < SZ(G[u]) && G[u][p] == v);
    p += off[u];
    if (find(p) == p) f[p] = find(p + 1);
  }
  int first(int u) {
    int p = find(off[u]);
    return p == off[u + 1] - 1 ? INF : G[u][p - off[u]];
  }
  int lower(int u, int x) {
    int p = lower_bound(ALL(G[u]), x) - G[u].begin() + off[u];
    p = find(p);
    return p == off[u + 1] - 1 ? INF : G[u][p - off[u]];
  }
};

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
  DoneDSU(int n = 0) : n(n), f(n), s(n, 1), mn1(n), mn2(n, INF), on(n), br(n, -1), bw(n) {
    iota(ALL(f), 0);
    iota(ALL(mn1), 0);
    hp.reserve(max(0, n - 1));
  }
  int find(int u) {
    while (u != f[u]) u = f[u] = f[f[u]];
    return u;
  }
  int val(int u, int p) {
    if (G[u].empty()) return INF;
    if (G[u][0] != p) return G[u][0];
    return SZ(G[u]) > 1 ? G[u][1] : INF;
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
    int p = SZ(hp);
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
    int su = s[u] + SZ(bw[u]);
    int sv = s[v] + SZ(bw[v]);
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
    for (auto y : G[x]) if (!on[y]) {
      br[x] = push(br[x], y);
      int w = val(y, x);
      if (w != INF) bw[x].insert({w, y});
    }
    for (auto y : G[x]) if (on[y]) {
      int r = find(y);
      int w = val(x, y);
      if (w != INF) bw[r].erase({w, x});
      merge(x, r);
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
    auto it = bw[r].upper_bound({h, INF});
    return it == bw[r].end() ? -1 : it->second;
  }
  bool same(int u, int v) {
    return find(u) == find(v);
  }
};

vector<int> fnd() {
  vector<int> to(n, -1);
  DSU rt(n);
  BIT bit(n);
  EraseSet id(n), has(n);
  vector<int> pre(n), ps, vis(n);
  ps.reserve(n);
  DoneDSU done(n);
  int ecnt = 0;
  vector<int> key(n);
  vector<int> pe(n, -1);
  vector<int> red_tag(n, -1), red_id(n, -1);
  vector<char> red_on(n);
  RedBlocks reds(n);
  bool alive = false;
  vector<pair<int, int>> pending_red;
  vector<int> temp_red;
  pending_red.reserve(n);
  temp_red.reserve(n);
  iota(ALL(key), 0);
  auto change_red = [&](int f, int x, int d) {
    int a = G[x][0];
    if (f == a) {
      if (tr.par[a] == x) {
        reds.add(f, 0, tr.in[a], d);
        reds.add(f, tr.out[a], n, d);
      } else {
        assert(tr.par[x] == a);
        reds.add(f, tr.in[x], tr.out[x], d);
      }
    } else {
      if (tr.par[a] == x) {
        reds.add(f, tr.in[a], tr.out[a], d);
      } else {
        assert(tr.par[x] == a);
        reds.add(f, 0, tr.in[x], d);
        reds.add(f, tr.out[x], n, d);
      }
    }
  };
  auto put_red = [&](int f, int x) {
    if (x == -1 || G[x].empty() || done.on[x] || red_on[x]) return;
    int a = G[x][0];
    int b = SZ(G[x]) > 1 ? G[x][1] : INF;
    if (f != a && f != b) return;
    change_red(f, x, 1);
    red_on[x] = 1;
  };
  auto take_red = [&](int x) {
    if (!red_on[x]) return;
    change_red(red_tag[x], x, -1);
    red_on[x] = 0;
  };
  auto add_red = [&](int p, int f, int x) {
    if (x == -1 || G[x].empty()) return;
    int a = G[x][0];
    int b = SZ(G[x]) > 1 ? G[x][1] : INF;
    if (f != a && f != b) return;
    red_tag[x] = f;
    red_id[x] = p;
    if (alive) {
      pending_red.push_back({f, x});
    } else {
      put_red(f, x);
    }
  };
  auto flush_red = [&]() {
    for (auto [f, x] : pending_red) put_red(f, x);
    pending_red.clear();
  };
  auto restore_red = [&]() {
    for (auto x : temp_red) if (!done.on[x]) put_red(red_tag[x], x);
    temp_red.clear();
  };
  auto add_ev = [&](int f, int t, int x = -1) {
    if (f == -1) return;
    int p = ecnt++;
    if (t && x != -1) {
      key[x] = f, pe[x] = p;
      add_red(p, f, x);
    }
  };
  vector<pair<int, int>> dst;
  dst.reserve(n);
  auto dir = [&](int u, int v) {
    dst.clear();
    dst.push_back({u, v});
    while (!dst.empty()) {
      auto [x, f] = dst.back();
      if (vis[x] && vis[f]) {
        dsu.merge(x, f);
      }
      dst.pop_back();
      if (!id.has(x)) continue;
      to[x] = f;
      rt.merge(x, f);
      id.erase(x);
      for (auto y : G[x]) {
        if (y == f || !id.has(y)) continue;
        dst.push_back({y, x});
      }
    }
  };
  auto qry_path = [&](int u, int v) {
    int res = 0;
    while (tr.top[u] != tr.top[v]) {
      if (tr.dep[tr.top[u]] < tr.dep[tr.top[v]]) swap(u, v);
      res += bit.sum(tr.in[tr.top[u]], tr.in[u] + 1);
      u = tr.par[tr.top[u]];
    }
    if (tr.dep[u] > tr.dep[v]) swap(u, v);
    res += bit.sum(tr.in[u], tr.in[v] + 1);
    return res;
  };
  int cur_cand = -1;
  bool cur_alive = false;
  auto add_pre = [&](int x, int f = -1) {
    if (x != -1 && pre[x] == 0) {
      ps.push_back(x);
      pre[x] = 1;
      bit.add(tr.in[x], 1);
      add_ev(f, 1, x);
    } else if (x != -1 && f != -1 && key[x] < f && f < x && !(cur_alive && f == cur_cand) && pre[f] == 0 && pe[x] != -1) {
      int p = pe[x];
      int old = key[x];
      ps.push_back(f);
      pre[f] = 1;
      bit.add(tr.in[f], 1);
      key[f] = old;
      key[x] = f;
      pe[f] = p;
    }
  };
  auto valid = [&](int x, int tar = -1) {
    if (id.has(x)) return true;
    if (to[x] == -1) return false;
    if (to[to[x]] == -1) return true;
    int c = qry_path(to[x], rt.find(x));
    if (c == 0) return true;
    if (c == 1 && pre[to[x]] == 1 && !ps.empty() && ps.back() == to[x]) {
      return tar == -1 || tr.dist(tar, x) <= 2;
    }
    return false;
  };
  int las = -1;
  int cand = -1;
  int cver = 0, ccut = 0, chead = -1;
  int cblk_u = -1, cblk_lim = 0;
  bool croot_done = false;
  vector<char> usedv(n);
  NextSet rem(n);
  vector<int> cpver(n, -1), cpval(n);
  int cpos = 0;
  auto used = [&](int x) {
    return usedv[x];
  };
  auto mark_used = [&](int x) {
    if (usedv[x]) return;
    usedv[x] = 1;
    for (auto v : G[x]) rem.erase(v, x);
  };
  auto cpar = [&](int u) {
    if (u == cand) return -1;
    if (cpver[u] != cver) {
      cpver[u] = cver;
      cpval[u] = tr.findChild(u, cand);
    }
    return cpval[u];
  };
  auto cmn = [&](int u) {
    int f = cpar(u);
    if (G[u].empty()) return INF;
    if (G[u][0] != f) return G[u][0];
    return SZ(G[u]) > 1 ? G[u][1] : INF;
  };
  auto cfinish = [&](int u) {
    if (!done.on[u]) {
      assert(used(u));
      for (auto v : G[u]) assert(used(v));
      take_red(u);
      done.add(u);
    }
    chead = min(chead, done.low(u, cand));
  };
  auto cisopen = [&](int u) {
    if (u == cand || done.on[u]) return false;
    int p = cpar(u);
    return p != -1 && done.on[p] && done.same(p, cand);
  };
  auto cfi = [&]() {
    return done.nxt(cand, chead);
  };
  auto cbad = [&]() {
    if (chead <= 0) return -1;
    int b = (chead - 1) / reds.B;
    for (; b >= 0; b--) {
      if (reds.qry(b, cpos) == 0) continue;
      int l = b * reds.B;
      int r = min(chead, min(n, l + reds.B));
      for (int z = r - 1; z >= l; z--) {
        if (z == cand) continue;
        int u = tr.findChild(z, cand);
        if (u == cand || done.on[u] || !red_on[u] || red_tag[u] != z) continue;
        int p = red_id[u];
        if (p == -1 || p >= ccut) continue;
        if (cmn(u) == z) return u;
      }
    }
    return -1;
  };
  auto cexpand = [&](int u) {
    assert(cisopen(u));
    int oh = chead;
    cblk_u = u;
    cblk_lim = oh;
    int v = cmn(u);
    if (v < chead) {
      int p = red_id[u];
      if (p != -1 && p < ccut && red_tag[u] == v && red_on[u]) {
        take_red(u);
        temp_red.push_back(u);
      }
      chead = v;
    }
  };
  auto cpeek = [&]() {
    while (1) {
      if (!croot_done) {
        int u = used(cand) ? INF : cand;
        u = min(u, rem.first(cand));
        if (u != INF) return u;
        cfinish(cand);
        croot_done = true;
      }
      if (cblk_u != -1) {
        int v = rem.lower(cblk_u, cblk_lim);
        if (v != INF) return v;
        cfinish(cblk_u);
        cblk_u = -1;
      }
      int bad = cbad();
      int after = -1;
      if (bad != -1) {
        int f = cpar(bad);
        auto it = lower_bound(ALL(G[bad]), chead);
        while (it != G[bad].end() && *it == f) ++it;
        if (it != G[bad].end()) after = *it;
      }
      int fi = cfi();
      int u;
      if (fi != -1 && (bad == -1 || !cisopen(bad) || (after != -1 && cmn(fi) < after))) {
        u = fi;
      } else {
        u = bad;
      }
      if (u == -1) return INF;
      cexpand(u);
    }
  };
  auto add_cand = [&](int r, int) {
    if (alive) return;
    restore_red();
    flush_red();
    cand = r;
    cur_cand = r;
    cur_alive = true;
    alive = true;
    cver++;
    cpos = tr.in[cand];
    ccut = ecnt;
    croot_done = false;
    cblk_u = -1;
    cblk_lim = 0;
    chead = G[r].empty() ? r : min(r, G[r][0]);
  };
  auto chk_cand = [&](int x) {
    if (!alive) return -1;
    int y = cpeek();
    if (y == INF) return -1;
    if (y < x) return cand;
    if (y > x) {
      alive = false;
      cur_alive = false;
      restore_red();
      flush_red();
      return -1;
    }
    mark_used(y);
    return -1;
  };
  while (id.size() > 2) {
    auto wk = [&](int x) {
      for (auto y : G[x]) if (vis[y] && to[y] == -1) {
        assert(id.has(y));
        assert(las == y);
        add_cand(y, x);
      }
      has.erase(x);
      while (has.size()) {
        int y = has.first();
        if (id.has(y) || valid(y, x)) {
          int got = chk_cand(y);
          if (got != -1) return got;
          int dis = tr.dist(x, y);
          if (dis >= 3) {
            int u = tr.findChild(x, y), v = tr.findChild(u, y);
            if (!id.has(v)) {
              has.erase(y);
              continue;
            }
            if (las != -1 && u != las) {
              add_pre(x, las);
              las = -1;
            }
            dir(u, v);
            add_pre(to[x], x);
          } else if (dis == 2) {
            int u = tr.findChild(x, y);
            if (!id.has(u)) {
              has.erase(y);
              continue;
            }
            if (las != -1 && u != las) {
              add_pre(x, las);
            }
            dir(x, u);
            add_pre(to[x], x);
          } else {
            if (las != -1 && y != las) {
              add_pre(x, las);
            }
            for (auto v : G[x]) if (v != y && to[v] != x) {
              dir(v, x);
            }
            las = x;
          }
          break;
        } else {
          has.erase(y);
        }
      }
      return -1;
    };
    int x = has.first();
    vis[x] = 1;
    mark_used(x);
    for (auto y : G[x]) if (vis[y] && (to[y] == x || to[x] == y)) {
      dsu.merge(x, y);
    }
    if (id.has(x)) {
      int got = wk(x);
      if (got != -1) return sol(got);
    } else {
      if (!valid(x)) {
        has.erase(x);
        continue;
      }
      add_pre(to[x], x);
      has.erase(x);
      if (id.has(to[x])) {
        while (has.size()) {
          int y = has.first();
          if (id.has(y) || valid(y, x)) {
            int got = chk_cand(y);
            if (got != -1) return sol(got);
            if (tr.dist(x, y) >= 3) {
              int u = tr.findChild(x, y), v = tr.findChild(u, y);
              if (u != to[x]) {
                has.erase(y);
                continue;
              }
              dir(u, v);
            }
            break;
          } else {
            has.erase(y);
          }
        }
        continue;
      }
    }
  }
  vector<int> ans(n, INF);
  for (int r = id.first(); r < n; r = id.find(r + 1)) {
    auto now = sol(r);
    if (now < ans) ans = now;
  }
  if (alive && cand != -1) {
    auto now = sol(cand);
    if (now < ans) ans = now;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  tr = Tree(n);
  dsu = DSU(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v, u--, v--;
    G[u].push_back(v);
    G[v].push_back(u);
    tr.addEdge(u, v);
  }
  tr.init();
  for (int i = 0; i < n; i++) sort(G[i].begin(), G[i].end());
  auto ans = fnd();
  for (int i = 0; i < n; i++) {
    cout << ans[i] + 1 << " \n"[i == n - 1];
  }
  return 0;
}
