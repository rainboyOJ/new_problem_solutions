/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * Problem: HDU 3639 Hawk-and-Chicken
 * Method: Tarjan SCC + Reverse Graph + DFS
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;

const int maxn = 5005;   // 题目 N <= 5000
const int maxm = 30005;  // 题目 M <= 30000

// ---------------- 你的模板开始 ----------------

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxm * 2]; // 稍微开大一点防止越界
    int h[maxn],edge_cnt=0;
    linkList(){ reset(); }

    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }

    // 迭代器部分为了简洁省略，本题直接用原生循环更高效
} e, edag; // e: 原图, edag: 反向DAG

struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; 

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(in_stack, 0, sizeof(in_stack));
        while(!st.empty()) st.pop();
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e.h[u]; ~i ; i = e.e[i].next) {
            int v = e.e[i].v;
            if (!dfn[v]) { 
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (in_stack[v]) { 
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            scc_cnt++;
            while (1) {
                int v = st.top(); st.pop();
                in_stack[v] = 0;
                scc_id[v] = scc_cnt; 
                if (v == u) break; 
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }
    }
} tarjan;

// ---------------- 你的模板结束 ----------------

// 全局变量
int scc_sz[maxn];    // 每个 SCC 的大小（点权）
int dag_indeg[maxn]; // 反向 DAG 的入度
int vis[maxn];       // DFS 访问标记
int visit_token = 0; // 时间戳，避免 memset vis
int current_sum = 0; // 当前 DFS 统计的总数

// 简单的 DFS 统计: 统计从 u 出发能到达的所有点的点权和
void dfs_calc(int u) {
    vis[u] = visit_token;
    current_sum += scc_sz[u];
    
    // 遍历反向图 edag
    for(int i = edag.h[u]; ~i; i = edag.e[i].next) {
        int v = edag.e[i].v;
        if(vis[v] != visit_token) {
            dfs_calc(v);
        }
    }
}

void solve(int n, int m, int case_id) {
    // 1. Tarjan 缩点
    tarjan.solve();

    // 2. 初始化统计数组
    for(int i = 0; i <= tarjan.scc_cnt; i++) {
        scc_sz[i] = 0;
        dag_indeg[i] = 0;
    }
    edag.reset(); // 清空反向图

    // 3. 计算每个 SCC 的大小 (原图点权)
    for(int i = 1; i <= n; i++) {
        scc_sz[tarjan.scc_id[i]]++;
    }

    // 4. 构建反向 DAG
    // 遍历原图的所有边 u -> v
    for(int u = 1; u <= n; u++) {
        for(int i = e.h[u]; ~i; i = e.e[i].next) {
            int v = e.e[i].v;
            int su = tarjan.scc_id[u];
            int sv = tarjan.scc_id[v];
            
            // 如果不在同一个 SCC，建立反向边: SCC[v] -> SCC[u]
            if(su != sv) {
                edag.add(sv, su); // 反向！
                dag_indeg[su]++;  // 统计入度
            }
        }
    }

    // 5. 寻找最大支持数
    int max_val = -1;
    // 存储每个 SCC 能获得的总支持数，-1表示未计算或非起点
    vector<int> final_score(tarjan.scc_cnt + 1, -1);
    
    visit_token = 0;
    memset(vis, 0, sizeof(vis));

    for(int i = 1; i <= tarjan.scc_cnt; i++) {
        // 剪枝：只从反向图入度为 0 的点（原图汇点）开始搜
        if(dag_indeg[i] == 0) {
            visit_token++;
            current_sum = 0;
            dfs_calc(i);
            
            // 题目要求不包含自己，所以结果是 current_sum - 1
            // 但为了比较方便，我们先存总数
            final_score[i] = current_sum;
            max_val = max(max_val, current_sum);
        }
    }

    // 6. 输出结果
    printf("Case %d: %d\n", case_id, max_val - 1);
    
    vector<int> ans_nodes;
    for(int i = 1; i <= n; i++) {
        // 如果节点 i 所属的 SCC 获得的支持数等于最大值
        if(final_score[tarjan.scc_id[i]] == max_val) {
            ans_nodes.push_back(i - 1); // 变回 0-based 输出
        }
    }
    
    // 排序并输出
    sort(ans_nodes.begin(), ans_nodes.end());
    for(int i = 0; i < ans_nodes.size(); i++) {
        if(i > 0) printf(" ");
        printf("%d", ans_nodes[i]);
    }
    printf("\n");
}

int main() {
    int t;
    if(scanf("%d", &t) == 1) {
        for(int i = 1; i <= t; i++) {
            int n, m;
            scanf("%d %d", &n, &m);
            
            // 初始化
            e.reset();
            tarjan.set(n);
            
            for(int j = 0; j < m; j++) {
                int u, v;
                scanf("%d %d", &u, &v);
                // 题目输入 0~n-1，转为 1~n 适配模板
                e.add(u + 1, v + 1);
            }
            
            solve(n, m, i);
        }
    }
    return 0;
}
