/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * date: 2026-09-17 16:56:20
 * oj: luogu
 * title: P3285
 * description: lazy 区间映射
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// #define NO_DEBUG // switch debug
#if defined(onlinejudge) || defined(ONLINE_JUDGE) || defined(NO_DEBUG)
#define log(...)
#define fenc
#else
#define log(args...) { cout << "LINE:" << __LINE__ << " : ";string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define fenc cout<<"================================";
void err(istream_iterator<string> it) {}

template<typename T>
void err(istream_iterator<string> it, T a) {
cerr << *it << " = " << a << "\n";
}

template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
cerr << *it << " = " << a << ", ";
err(++it, args...);
}
#endif
const int maxn = 1e6+5;
int n,m;
int last_answer;
int a[maxn];
int front_pos,back_pos,max_pos;

map<int,int> id_map; // id -> start postion

//pos_map  is the reflection of id_map 
map<int ,int > pos_map;
// ----- [pos                 ] -----
//       |
//       +---> id
//
// 为什么不用记录 pos_map 这一侧的右端点？
// 
//


// ==============================================================================
// 动态开点线段树：维护绝对坐标轴上每个坐标是否有人
// 排名 = 坐标上前缀被占用个数；第 k 名 = 第 k 个被占用坐标
// ==============================================================================
// 单点修改次数上限：op2/op3 各做 2 次 update，共 2m 次；
// V=n+2m<=3e8，树深 <= 29，故最多 2e5*29 ≈ 5.8e6 个点。
// 取 6e6 留余量（6e6*3*4B ≈ 72MB）。
const int MAX_NODES = 6e6+5;
int ls[MAX_NODES],rs[MAX_NODES],sum[MAX_NODES];
int root,tot;

// 未开点区间的默认人数：初始所有人都在 [m+1, m+n] 内，取交集
int default_sum(int l,int r) {
    int L = max(l, m+1);
    int R = min(r, m+n);
    return L <= R ? (R-L+1) : 0;
}

void push_up(int p,int l,int r) {
    int mid = (l+r)>>1;
    int lv = ls[p] ? sum[ls[p]] : default_sum(l,mid);
    int rv = rs[p] ? sum[rs[p]] : default_sum(mid+1,r);
    sum[p] = lv + rv;
}

// 单点赋值：坐标 pos 处有人(1) / 没人(0)
void update(int &p,int l,int r,int pos,int val) {
    if( !p) {
        p = ++tot;
        sum[p] = default_sum(l,r);
    }
    if( l == r) {
        sum[p] = val;
        return;
    }
    int mid = (l+r)>>1;
    if( pos <= mid) update(ls[p],l,mid,pos,val);
    else            update(rs[p],mid+1,r,pos,val);
    push_up(p,l,r);
}

// 前缀人数：坐标 [1,pos] 内共有多少人，也就是坐标 pos 上用户的名次
int query_rank(int p,int l,int r,int pos) {
    if( !p) return default_sum(max(l,1), min(r,pos));
    if( l == r) return sum[p];
    int mid = (l+r)>>1;
    if( pos <= mid) return query_rank(ls[p],l,mid,pos);
    int lv = ls[p] ? sum[ls[p]] : default_sum(l,mid);
    return lv + query_rank(rs[p],mid+1,r,pos);
}

// 线段树上二分：第 k 个被占用的坐标
int query_kth(int p,int l,int r,int k) {
    if( l == r) return l;
    int mid = (l+r)>>1;
    int lv = ls[p] ? sum[ls[p]] : default_sum(l,mid);
    if( k <= lv) return query_kth(ls[p],l,mid,k);
    return query_kth(rs[p],mid+1,r,k-lv);
}

// ==============================================================================
// 区间块撕裂：把含 id 的块切成 [L,id-1] [id,id] [id+1,R]，返回 id 的绝对坐标
// ==============================================================================
int split_and_get_pos(int id) {
    map<int,Interval>::iterator it = id_map.upper_bound(id);
    --it;
    int L = it->second.id_l;
    int R = it->second.id_r;
    int start = it->second.start_pos;

    int target_pos = start + (id - L);

    if( L != R) { // 不是单点块，需要撕裂
        id_map.erase(it);
        pos_map.erase(start);

        // 左半段 [L, id-1]
        if( L <= id-1) {
            id_map[L] = {L, id-1, start};
            pos_map[start] = L;
        }
        // 右半段 [id+1, R]
        if( id+1 <= R) {
            id_map[id+1] = {id+1, R, target_pos+1};
            pos_map[target_pos+1] = id+1;
        }
        // 独立单点 [id, id]
        id_map[id] = {id, id, target_pos};
        pos_map[target_pos] = id;
    }
    return target_pos;
}

// 已知坐标 pos 处有人，反查用户编号
int get_id_by_pos(int pos) {
    map<int,int>::iterator it = pos_map.upper_bound(pos);
    --it;
    return it->second + (pos - it->first);
}

// 把已撕裂成单点的用户从 old_pos 挪到 new_pos
void move_user(int id,int old_pos,int new_pos) {
    update(root,1,max_pos,old_pos,0);
    update(root,1,max_pos,new_pos,1);

    id_map[id] = {id, id, new_pos};
    pos_map.erase(old_pos);
    pos_map[new_pos] = id;
}

void init() {
    // read(n);
    std::cin >> n >> m;
    front_pos = m+1;
    back_pos = n+m;
    max_pos = n + 2*m;

    // init first range
    id_map[1] = {1,n,m+1};
    pos_map[m+1] = 1;

}

signed main () {
#ifdef FREOPEN
    freopen("in", "r",stdin);
#endif
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); // 关闭io同步

    init();

    last_answer = 0;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int op,x,y;
        std::cin >> op >> x;
        x -= last_answer;

        if( op == 1) {
            std::cin >> y;
            y -= last_answer;

            int pos = split_and_get_pos(x);
            last_answer = query_rank(root,1,max_pos,pos);

            // x 已被撕裂成单点，把该点的编号改成 y
            id_map.erase(x);
            id_map[y] = {y, y, pos};
            pos_map[pos] = y;
        }
        else if( op == 2) {
            int pos = split_and_get_pos(x);
            last_answer = query_rank(root,1,max_pos,pos);

            --front_pos; // 占用一个左边预留坐标
            move_user(x,pos,front_pos);
        }
        else if( op == 3) {
            int pos = split_and_get_pos(x);
            last_answer = query_rank(root,1,max_pos,pos);

            ++back_pos; // 占用一个右边预留坐标
            move_user(x,pos,back_pos);
        }
        else { // op == 4
            int pos = query_kth(root,1,max_pos,x);
            last_answer = get_id_by_pos(pos);
        }

        std::cout << last_answer << '\n';
    }

    return 0;
}
