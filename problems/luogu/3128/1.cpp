/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-03 21:14:03
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n,m;
int a[maxn];


//oisnip_begin code/graph/linklist.cpp 内容开始

// const int maxn = 1e6+5;
// const int maxe = 1e6+5;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        reset();
    }

    void reset() {
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

    // 参考 语法糖
    // https://en.cppreference.com/w/cpp/language/range-for.html
#ifdef __cpp_range_based_for
    // C++ 模板 和 策略模式（Policy） 来消除重复代码。
    // 我们可以定义一个通用的迭代器模板，通过传入不同的“提取器（Getter）”来决定 operator* 返回什么。
    // === 1. 定义数据提取策略 (核心区别) ===
    
    // 策略A: 获取整条边 (对应原本的 Iterator)
    struct UseEdge {
        using ReturnType = edge&; // 定义返回类型
        static ReturnType get(linkList* p, int i) { return p->e[i]; }
    };

    // 策略B: 只获取邻接点v (对应原本的 AdjIterator)
    struct UseAdj {
        using ReturnType = int;   // 定义返回类型
        static ReturnType get(linkList* p, int i) { return p->e[i].v; }
    };

    // === 2. 通用迭代器模板 (复用逻辑) ===
    template<typename Getter>
    struct BaseIterator {
        int i;          // 边的编号
        linkList* p;    // linkList指针
        
        BaseIterator(linkList* p, int i) : p(p), i(i) {}

        // 通用的遍历逻辑
        BaseIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const BaseIterator& oth) { return i != oth.i; }
        
        // 差异化逻辑：委托给 Getter 处理
        typename Getter::ReturnType operator*() { return Getter::get(p, i); }
    };

    // 定义具体的迭代器别名
    using Iterator    = BaseIterator<UseEdge>;
    using AdjIterator = BaseIterator<UseAdj>;

    // === 3. 通用范围类模板 ===
    template<typename IterT>
    struct BaseRange {
        int start;
        linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        IterT begin() { return IterT(p, p->h[start]); }
        IterT end()   { return IterT(p, -1); }
    };

    // === 4. 接口语法糖 ===
    
    // usage: for(auto& e : list(u))
    BaseRange<Iterator> operator()(int u) { return BaseRange<Iterator>(this, u); }

    // usage: for(int v : list.adj(u))
    BaseRange<AdjIterator> adj(int u) { return BaseRange<AdjIterator>(this, u); }
    
#endif
} e;

//oisnip_end code/graph/linklist.cpp 内容结束

//oisnip_begin最小生成树mst_kruskal.cpp
// 定义边的结构体
struct Edge {
    int u, v;
    long long w;
    // 重载 < 运算符，方便 std::sort 直接排序
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

// Kruskal 算法封装结构体
struct KruskalAlgorithm {
    struct DSU {
        std::vector<int> fa;
        // 初始化并查集
        void init(int n) {
            fa.resize(n + 1);
            std::iota(fa.begin(), fa.end(), 0); // 赋值 0, 1, 2... n
        }
        int find(int x) {
            return x == fa[x] ? x : fa[x] = find(fa[x]); // 路径压缩
        }
        bool merge(int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx == fy) return false; // 已经在同一个集合
            fa[fx] = fy;
            return true;
        }
    } dsu;

    int n; // 点的数量
    std::vector<Edge> edges; // 存储所有边

    // 初始化：清空边，设定点数
    void init(int _n) {
        n = _n;
        edges.clear();
        dsu.init(n);
    }

    // 加边函数：心智负担低，不用操心数组下标
    void add_edge(int u, int v, long long w) {
        edges.push_back({u, v, w});
    }

    // 执行算法
    // 返回值：最小生成树的权值和。如果无法连通，返回 -1
    long long solve() {
        // 1. 排序：贪心的基础
        std::sort(edges.begin(), edges.end());
        
        // 2. 重新初始化并查集状态（防止多次调用 solve 出错）
        dsu.init(n);

        long long ans = 0; // 权值和，注意开 long long
        int cnt = 0;       // 记录选了多少条边

        for (const auto& e : edges) {
            if (dsu.merge(e.u, e.v)) { // 如果不在同一集合，合并
                ans += e.w;
                cnt++;
                // 如果需要输出选中的边，可以在这里打印
                // cout << e.u << " " << e.v << " " << e.w << endl;
            }
            if (cnt == n - 1) break; // 优化：选够了边就退出
        }

        // 3. 连通性检查：如果选的边数少于 n-1，说明图不连通
        if (cnt < n - 1) return -1;
        
        return ans;
    }
} kruskal;
//oisnip_end


void init(){

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    return 0;
}
