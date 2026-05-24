/**
 * Author by Rainboy
 * Problem: HDU 3394 Railway
 * Method: Tarjan v-BCC (Point-Biconnected Component)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

const int maxn = 10010; 
const int maxe = 200020; 

int n, m;

struct Edge {
    int u, v, next, id;
} e[maxe];

int head[maxn], e_cnt;
int dfn[maxn], low[maxn], timer;
int bridge_ans, clash_ans;

// 栈存储边的 ID
int st[maxe], top; 

// 标记数组，用于统计每个块内的点数 (避免重复计数)
int vis_tag[maxn], tag_id;

void init() {
    e_cnt = 0;
    timer = 0;
    top = 0;
    bridge_ans = 0;
    clash_ans = 0;
    tag_id = 0;
    
    // 初始化 head, dfn, vis_tag
    // 只需要初始化 0 到 n 的范围
    for(int i = 0; i <= n; i++) {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        vis_tag[i] = 0;
    }
}

void add_edge(int u, int v, int id) {
    e[e_cnt].u = u;
    e[e_cnt].v = v;
    e[e_cnt].id = id; // 记录原始边的编号如果不必要可以省略，但这里用索引作为ID
    e[e_cnt].next = head[u];
    head[u] = e_cnt++;
}

// 处理找到的连通分量（块）
void process_bcc(int u, int v) {
    int edge_count = 0;
    int vertex_count = 0;
    tag_id++; // 使用新的标记轮次，代替 memset

    while (true) {
        int idx = st[--top]; // 弹出栈顶边
        edge_count++;
        
        int curr_u = e[idx].u;
        int curr_v = e[idx].v;

        // 统计点数
        if (vis_tag[curr_u] != tag_id) {
            vis_tag[curr_u] = tag_id;
            vertex_count++;
        }
        if (vis_tag[curr_v] != tag_id) {
            vis_tag[curr_v] = tag_id;
            vertex_count++;
        }

        // 直到弹出的边是当前边 (u, v) 为止
        // 注意：因为是无向图存双边，边的ID判断要小心，这里简化逻辑：
        // 只要弹出的不是我们刚才入栈的那个逻辑边就继续
        // 实际上 tarjan 逻辑中，当 process_bcc 被调用时，栈顶一系列边就是该分量的
        // 我们利用 idx 和当前边的关系来停止可能比较麻烦，不如直接利用 Tarjan 性质：
        // 在 low[v] >= dfn[u] 时，栈中所有在 (u,v) 之上的边都属于这个分量
        // 为了准确停止，我们通常比较 e[idx] 是否就是 e[i] (当前遍历的边)
        // 但这里无法直接传 i，所以通常做法是：在入栈前记录栈顶位置，或者手动判断
        
        // 修正：更简单的做法是，只要弹出的边不是当前递归触发的边，就一直弹
        // 但这里为了方便，我们只判断值
        if (curr_u == u && curr_v == v) break;
        // 同时也可能是反向存的 v, u，但我们在 tarjan 里 push 的是当前的 directed edge
    }

    // 判定冲突
    if (edge_count > vertex_count) {
        clash_ans += edge_count;
    }
}

void tarjan(int u, int fa_edge_idx) {
    dfn[u] = low[u] = ++timer;
    
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].v;
        // 如果是反向边（父亲来的边），跳过
        // 使用异或技巧：0^1=1, 1^1=0; 2^1=3, 3^1=2
        if ((i ^ 1) == fa_edge_idx) continue;

        if (!dfn[v]) {
            st[top++] = i; // 将当前边入栈
            
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            
            // 核心逻辑：Point-BCC 判断条件
            if (low[v] >= dfn[u]) {
                // 1. 判断是否为桥
                if (low[v] > dfn[u]) {
                    bridge_ans++;
                }
                
                // 2. 弹出并处理该分量内的所有边
                // 这里的处理逻辑：弹出直到栈顶是当前边 i
                int edge_count = 0;
                int vertex_count = 0;
                tag_id++; 
                
                while (true) {
                    int idx = st[--top];
                    edge_count++;
                    
                    int u_node = e[idx].u;
                    int v_node = e[idx].v;
                    
                    if (vis_tag[u_node] != tag_id) {
                        vis_tag[u_node] = tag_id;
                        vertex_count++;
                    }
                    if (vis_tag[v_node] != tag_id) {
                        vis_tag[v_node] = tag_id;
                        vertex_count++;
                    }
                    
                    if (idx == i) break; // 弹到了当前边，结束
                }
                
                if (edge_count > vertex_count) {
                    clash_ans += edge_count;
                }
            }
        } else if (dfn[v] < dfn[u]) {
            // 回边：更新 low，并入栈
            st[top++] = i;
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    // 加上扩栈代码，防止爆栈 (HDU 特色)
    // #pragma comment(linker, "/STACK:102400000,102400000")
    
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;
        
        init();
        
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            // 0-based 转 1-based，防止冲突
            u++; v++; 
            add_edge(u, v, i);
            add_edge(v, u, i);
        }
        
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i, -1);
            }
        }
        
        printf("%d %d\n", bridge_ans, clash_ans);
    }
    return 0;
}

