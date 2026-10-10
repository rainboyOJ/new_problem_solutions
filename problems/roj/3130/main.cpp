/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// Mokia：三维偏序（时间, x, y），CDQ 分治时间维，x 排序后树状数组维护 y。
#include <cstdio>
#include <vector>

typedef long long ll;

struct Ev {
    ll x, y;
    ll w;   // 修改的权值
    ll qid; // 询问编号；-1 表示这是修改
    ll sgn; // 询问角点的符号
};

std::vector<Ev> ev;
std::vector<Ev> tmp;
ll W;
std::vector<ll> tree;
std::vector<int> stamp;
ll cur_stamp = 0;
std::vector<ll> ans;
ll qcnt = 0;

void cdq(ll l, ll r) {
    if (r - l <= 1) return;
    ll mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid, r);
    // 递归保证两半各自按 x 有序；左半修改（时间早）贡献给右半询问
    cur_stamp++;
    ll i = l;
    for (ll j = mid; j < r; j++) {
        if (ev[j].qid == -1) continue;
        ll qx = ev[j].x, qy = ev[j].y;
        while (i < mid && ev[i].x <= qx) {
            if (ev[i].qid == -1) {
                ll k = ev[i].y, ew = ev[i].w;
                while (k <= W) {
                    if (stamp[k] != cur_stamp) {
                        stamp[k] = (int)cur_stamp;
                        tree[k] = 0;
                    }
                    tree[k] += ew;
                    k += k & -k;
                }
            }
            i++;
        }
        if (ev[j].sgn) {
            ll s = 0, k = qy;
            while (k) {
                if (stamp[k] == cur_stamp) s += tree[k];
                k -= k & -k;
            }
            ans[ev[j].qid] += ev[j].sgn * s;
        }
    }
    // 归并两半按 x 有序，维持不变式
    ll a = l, b = mid, t = l;
    while (a < mid && b < r) {
        if (ev[a].x <= ev[b].x) tmp[t++] = ev[a++];
        else tmp[t++] = ev[b++];
    }
    while (a < mid) tmp[t++] = ev[a++];
    while (b < r) tmp[t++] = ev[b++];
    for (ll k = l; k < r; k++) ev[k] = tmp[k];
}

int main() {
    ll S;
    if (scanf("%lld %lld", &S, &W) != 2) return 0; // 空输入安全返回

    tree.assign(W + 1, 0);
    stamp.assign(W + 1, 0);

    while (true) {
        ll op;
        if (scanf("%lld", &op) != 1) break;
        if (op == 1) {
            ll x, y, a;
            scanf("%lld %lld %lld", &x, &y, &a);
            Ev e;
            e.x = x; e.y = y; e.w = a; e.qid = -1; e.sgn = 0;
            ev.push_back(e);
        } else if (op == 2) {
            ll x1, y1, x2, y2;
            scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
            // 每个询问拆成 4 个前缀角点询问
            Ev e;
            e.x = x1 - 1; e.y = y1 - 1; e.w = 0; e.qid = qcnt; e.sgn = 1;  ev.push_back(e);
            e.x = x2;     e.y = y2;     e.w = 0; e.qid = qcnt; e.sgn = 1;  ev.push_back(e);
            e.x = x1 - 1; e.y = y2;     e.w = 0; e.qid = qcnt; e.sgn = -1; ev.push_back(e);
            e.x = x2;     e.y = y1 - 1; e.w = 0; e.qid = qcnt; e.sgn = -1; ev.push_back(e);
            qcnt++;
        } else {
            break;
        }
    }

    ans.assign(qcnt, 0);
    tmp.resize(ev.size());
    if (!ev.empty()) cdq(0, (ll)ev.size());

    for (ll i = 0; i < qcnt; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
