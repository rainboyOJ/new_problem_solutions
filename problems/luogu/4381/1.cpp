/* author: Rainboy email: rainboylvx@qq.com  time: 2023年 06月 17日 星期六 09:04:05 CST */
#include <bits/stdc++.h>
//#include "graph/linkList.hpp"
using namespace std;
typedef long long ll;
const ll maxn = 1e6+5,maxe = 2e6+5; //点与边的数量

ll n,m;
/* 定义全局变量 */

ll fa[maxn]; //记录每个点的父子边
ll dfn[maxn];
ll timestamp; 
bool in_loop[maxn];


//quick read
void read() {}
 template<typename T,typename ...Args>
#ifdef __cpp_concepts
    requires 
    std::conjunction_v<std::is_integral<T>,std::is_integral<Args>...>
    // std::integral<T> && std::integral<args>...
#endif
    void read(T & n,Args&... args) {
        n = 0;
        bool neg_flag = 0;
        char ch = getchar();

        // no digit , 一真读,直数字
        while('0' < ch && ch > '9') {
            if( ch == '-') neg_flag = 1;
            ch = getchar();
        }
        while( '0' <= ch && ch <='9') {
            n = n*10 + ch -'0';
            ch= getchar();
        }
        n = neg_flag ? -n : n;
        read(args...);
    }


struct linkList {
    struct edge {ll u,v,w,next;
        friend std::ostream & operator<<(std::ostream & o ,const edge & e ) {
            o << "u="  << e.u << ",v= "<<e.v << ",w=" << e.w;
            return o;
        }
    } ;
    edge e[maxe];
    


    ll h[maxn],edge_cnt=0;
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(ll u,U func){
        for(ll i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }

    bool same_edge(ll i,ll j) {
        return i == j  || i == (j^1);
    }

    void add(ll u,ll v,ll w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(ll u,ll v,ll w=0){
        add(u,v,w);
        add(v,u,w);
    }
    //下标访问
    edge& operator[](ll i){ return e[i]; }
    //返回head[u]
    ll operator()(ll u){ return h[u]; }
} e;


void init()
{
    // cin >> n;
    read(n);
    //存图
    for(ll i=1;i<=n;++i){
        ll v,w;
        // std::cin >> v >> w;
        read(v,w);
        e.add2(i, v,w);
    }
}

struct node {
    ll u,s; //u表示当前点的编号,
             //s表示前缀和
};

template<typename T>
void max_upd(T &a ,const T & b ) {
    if( a < b ) a = b;
}

// dp求树的直径

ll dp[maxn];
ll ans = 0;
void dfs_dp(ll u,ll fa) {

    for(ll i = e.h[u]; ~i; i =e[i].next) {
        ll v = e[i].v;
        if( in_loop[v] ) continue; //环上的边
        if( v == fa) continue;
        dfs_dp(v, u);
        // ans = max(ans,dp[u] + dp[v]+ e[i].w);
        max_upd(ans, dp[u]+dp[v]+e[i].w);
        dp[u] = max(dp[u],dp[v]+e[i].w);
    }
}
// 单调队列的实现

template<typename T>
struct _que {
    T a[maxn];
    ll head,tail;
    void init() {tail = head = 0;}
    ll size() { return head -tail;}
    void push(T t) {
        a[tail++] = t;
    }
    bool empty() {return tail == head;}
    T & front() {return a[head];}
    T & back() {return a[tail-1];}
    void pop_back(){ tail--;}
    void pop_front() { ++head;}
};

//单调队列
struct monotonic_que {
    struct node_with_p : public node{
        ll p;
    };
    _que<node_with_p> a;

    //初始化
    void init() { a.init();}

    //删除头部
    void del(ll p) {
        if( a.front().p < p)
            a.pop_front();
    }
    void push(ll p,ll u,ll s) {
        while(!a.empty() && a.back().s < s )
            a.pop_back();
        a.push({u,s,p});
    }

    auto & front() {
        return a.front();
    }

} mque;

//前缀和,编号从1开始
struct pre_sum {
    ll a[maxn];
    ll idx=0;
    void init() { idx = 0;}

    void push(ll v) {
        ++idx;
        a[idx] = v + a[idx-1];
    }

    //[i,j] 的区间和
    ll range(ll i,ll j) {
        return a[j] - a[i-1];
    }

    ll size() {
        return idx;
    }
    ll operator[](std::size_t i) const {
        return a[i];
    }

} pre;

// 拆环成链
// 存数据有要求
// 除了第一个数据边外，每一条数据都能和上一条连接
// i.e 
// first save : 1->2
// second save : 2->x
// 也就是上一条边的延续,起点是上一条边的终点
struct ring2chain {
    using edge = linkList::edge;
    linkList::edge a[maxe];
    ll idx = 0;

    void init() { idx = 0;}
    
    //第一条边存两次,方便每一次都取v点
    void push(const edge & e) {
        if(idx != 0  && e.u != last_edge().v )
            throw "invalid argument";
        if(idx == 0) {
            a[0].v = e.u;
            a[0].w = 0;
        }
        a[++idx] = e;
    }

    edge& last_edge() {
        return a[idx];
    }

    //得到第i个点的编号
    ll get(ll i) {
        return a[resp(i)].v;
    }

    //得到第i个点对应的长度值
    //第i个点和前面的点的边长
    ll getw(ll i) {
        return a[resp(i)].w;
    }
    ll resp(ll i) const {
        if( i > idx+1)
            i-=idx;
        return i-1;
    }
    ll size() const {
        return idx*2;
    }
} chain;



// i前面的第m个位置,包括i
ll Predecessor(ll i,ll m) {
    return  i-m+1;
}

// 输入形成环的边集
// 拆环成链

// 存入的数据
// 1 2 w
// 2 3 w
// 3 1 w

void get_cycle(ll u,ll v,ll edge)
{
    in_loop[u] = 1;
    in_loop[v] = 1;

    //拆环成链
    // cout << e[edge^1] << endl;
    chain.init();
    chain.push( e[edge^1]);
    while( u!=v) {
        // cout << e[fa[u]^1] << endl;
        chain.push(e[fa[u]^1]);
        // dfs_dp(u, -1);
        u = e[fa[u]].u;
        in_loop[u] = 1;
    }
    
    // cout << "\n";
}

void get_ans() {
    // for(ll i =1;i<=chain.size();i++) {
    //     cout << chain.get(i) << " ";
    // }
    // cout << "\n";
    for(ll i = 1;i <= chain.size() /2 ;i ++) {
        dfs_dp(chain.get(i), -1);
    }
    pre.init();
    for(ll i =1;i<=chain.size();i++) {

        // cout << chain.getw(i) << " ";
        pre.push(chain.getw(i)); //前缀和
    }
    //进行单调队列
    mque.init();
    mque.push(0, 0, 0);
    ll m = chain.size()/2;
    for(ll i =1;i<=chain.size();i++) {
        ll p = Predecessor(i, m);
        mque.del(p);
        ll u = chain.get(i);
        ll pre_s = mque.front().s;
        ll res = dp[u] + pre[i] + pre_s;
        max_upd(ans, res);
        // cout << "i " << chain.get(i) << " " << ans << '\n';
        mque.push(i, u, dp[u] - pre[i]);
    }
}

void dfs_find_circle(ll u,ll father_edge) {
    dfn[u] = ++timestamp;
    fa[u] = father_edge;

    for(ll i = e.h[u];~i;i = e[i].next) {
        ll v = e[i].v;
        if( e.same_edge(i,father_edge) )
            continue;
        if( !dfn[v]) {
            dfs_find_circle(v,i);
        }
        else if( dfn[v] < dfn[u] ) {
            get_cycle(u,v,i);
        }
    }
}



int main(){
    // cin.sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
    init();
    //找到环
    ll _ans = 0;

    /*
    for(ll i=0;i<e.edge_cnt;++i){
        ll u = e[i].u;
        ll v = e[i].v;
        ll w = e[i].w;
        cout << u << "," <<  v << "," << w<<'\n';
    }
    */
    // return 0;
    for(ll i =1 ;i<= n;i++) {
        ans = 0;
        chain.init();
        if( !dfn[i]) {
            dfs_find_circle(i, -1);
            get_ans();
            // std::cout << "ans "<<ans << "\n";
            _ans += ans;
        }
    }
    std::cout << _ans << "\n";
    // 求环上的两点的路径
    return 0;
}
