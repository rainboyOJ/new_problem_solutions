//暴力求 与点u 距离为2的点
//单独求是很简单的
//如何在一次dfs里所有的点的距离呢

//代码模板, 来自 rbook.roj.ac.cn
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//====== log 调试用
// 使用: int a,b,c; log(a,b,c)
#ifndef DEBUG
#define log(...)
#define fenc(...) ;
#else
#define fenc cout << "\n=================\n";
#define log(args...) { cout << "LINE:" << __LINE__ << " : ";string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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
int w[maxn];
int max_ans = 0;
ll mod = 10007;
ll sum = 0;

ll ch_sum[maxn]; // sum of children
ll ch_sq_sum[maxn]; // sum of square of children 

int max_f[maxn][2]; // max_f[i][0] max_f[i][1]


// helper
void update_max_f(int i,int val) {
  if( val > max_f[i][0]) {
    max_f[i][1] = max_f[i][0];
    max_f[i][0] = val;
  }
  else if( val > max_f[i][1]) {
    max_f[i][1] = val;
  }
}

const int maxe = 1e6+5;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    //下标访问
    edge& operator[](int i){ return e[i]; }
    //返回head[u]
    int operator()(int u){ return h[u]; }
} e;


void init() {
  cin >> n;
  for(int i =1;i<n;i++){
    int u,v;
    cin >> u >> v;
    e.add2(u,v);
  }
  for(int i =1;i<=n;i++){
    cin >> w[i];
  }
}

void dfs_1(int u,int fa) {

  for(int i = e(u); ~i ;i = e[i].next)
  {
    int  v = e[i].v;
    if( v == fa) continue;
    update_max_f(u,w[v]);
    dfs_1(v,u);
  }

  // get all children info
  int t = max_f[u][1] * max_f[u][0];
  if( t > max_ans) max_ans = t;

}

void dfs_2(int u,int fa) {
  int max_chch = 0;
  for(int i = e(u); ~i ;i = e[i].next)
  {
    int  v = e[i].v;
    if( v == fa) continue;
    // cout << u << " " << v << endl; 
    if(max_chch < max_f[v][0])
      max_chch = max_f[v][0];
    dfs_2(v,u);
  }

  // get all children info
  int t = max_chch * w[u];
  // cout << u << " " << t << endl;

  // cout << max_chch;

  // cout << endl;
  // cout << endl;
  // cout << endl;

  if( t > max_ans) max_ans = t;
}


void dfs_sum_2(int u,int fa) {
  int max_chch = 0;
  ll all_chch_sum = 0;
  for(int i = e(u); ~i ;i = e[i].next)
  {
    int  v = e[i].v;
    if( v == fa) continue;
    ch_sum[u] += w[v];
    ch_sum[u] %= mod;

    ch_sq_sum[u] += w[v] * w[v];
    ch_sq_sum[u] %= mod;

    dfs_sum_2(v,u);

    all_chch_sum += ch_sum[v];
  }

  ll t = ch_sum[u] * ch_sum[u] - ch_sq_sum[u];
  sum += t;
  sum %= mod;

  sum += ( all_chch_sum * w[u]) *2;
  sum %= mod;
}

int main () {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); // 关闭io同步
    init();
    dfs_1(1,1);
    dfs_2(1,1);
    dfs_sum_2(1,1);
    cout << max_ans << " ";
    cout << sum << endl;

    
    return 0;
} 
