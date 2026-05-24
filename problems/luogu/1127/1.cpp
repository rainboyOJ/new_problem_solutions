/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-07 16:59:28
 * Problem: P1127 词链 (欧拉路径/回路)
 */
#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include <string>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 30; // 最多26个字母，开到30足够
int n, m;
int a[maxn];

// out[i]: 字母 i (i+'a') 的出度
int out[maxn];
// in[i]: 字母 i 的入度
int in[maxn];
// exist[i]: 标记字母 i 是否在输入的单词中出现过
bool exist[maxn]; 

// adj[i]: 邻接表，存储从字母 i 开始的所有单词
// 使用 vector 是为了方便排序和删除边
vector<string> adj[maxn]; 
// ans: 结果栈，用于存储 Hierholzer 算法后序遍历的路径
stack<string> ans;


// === 并查集 (用于判断图的弱连通性) ===
int fa[maxn]; // 并查集父节点数组

// 查找元素 x 所在集合的代表元素（根节点），带路径压缩
int find(int x) {
    // 标准的三目运算符写法：如果 fa[x] 是自身，则返回 x；否则递归查找并压缩路径
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

// 合并 u 和 v 所在的两个集合
void dsu_merge(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    if (fu != fv) {
        fa[fu] = fv; // 将 u 的根指向 v 的根
    }
}
// === 并查集结束 ===

// 初始化函数：读取输入、建图、统计度数、维护并查集
void init(){
    // 初始化并查集，每个节点的父节点指向自己
    for(int i = 0; i <= 26; ++i) {
        fa[i] = i;
    }

    std::cin >> n; // 读取单词数量
    for(int i = 1; i <= n; ++i) {
        string s;
        std::cin >> s;
        // u: 单词首字母的索引 (0-25)
        int u = s.front() - 'a';
        // v: 单词尾字母的索引 (0-25)
        int v = s.back() - 'a';

        // 标记首尾字母已存在
        exist[u] = 1;
        exist[v] = 1;
        
        // 更新出度及入度
        out[u]++;
        in[v]++;

        // 将单词加入首字母对应的邻接表中
        adj[u].push_back(s);

        // 在并查集中合并首尾字母所在的集合
        // 这意味着在无向意义下，u 和 v 是连通的
        dsu_merge(u, v);
    }
}

// Hierholzer 算法的核心 DFS 函数
// 作用：寻找欧拉路径，并将路径逆序存入 ans 栈中
void dfs(int u) {
    // 只要当前节点 u 还有出边（单词）未访问
    while (!adj[u].empty()) {
        // 1. 取出当前出边中字典序最小的单词
        // 由于在 main 中对 adj[u] 进行了降序排序，最小的单词在 vector 的尾部 (back)
        string w = adj[u].back();
        
        // 2. 删除该边，标记为已走过。pop_back 是 O(1) 操作
        adj[u].pop_back();

        // 获取单词的尾字母，即下一个节点
        int v = w.back() - 'a';
        
        // 3. 递归走向下一个节点，继续寻找路径
        dfs(v);
        
        // 4. 【核心】回溯时将单词入栈
        // 这保证了路径是后序记录的，即先记录死胡同的边，最后记录起点的边
        ans.push(w);
    }
}

signed main () {
    // 关闭同步流，加速输入输出
    ios::sync_with_stdio(false); cin.tie(0);
    
    init(); // 执行初始化
    
    // 【关键步骤】对每个节点的邻接表进行排序
    // 使用 greater<string>() 进行降序排序。
    // 这样字典序最小的单词会排在 vector 的末尾，方便使用 pop_back() 高效取出。
    for(int i = 0; i <= 26; ++i) {
        std::sort(adj[i].begin(), adj[i].end(), greater<string>());
    }

    int start = -1;      // 欧拉路径/回路的起点
    int cnt_start = 0;   // 统计符合起点度数条件 (out = in + 1) 的节点个数
    int cnt_end = 0;     // 统计符合终点度数条件 (in = out + 1) 的节点个数
    
    // 遍历所有字母，检查度数条件并寻找起点
    for(int i = 0; i < 26; ++i) {
        if (!exist[i]) continue; // 跳过未出现的字母
        
        // 临时设置一个起点，防止全是环的情况 start 保持为 -1
        // 如果后面找到了更确定的欧拉路径起点，会覆盖这个值
        if (start == -1) start = i;
        
        if (out[i] == in[i]) continue; // 度数平衡，是中间节点或回路节点
        
        if (out[i] == in[i] + 1) {
            // 满足欧拉路径起点的条件
            start = i;
            cnt_start++;
        }
        else if (in[i] == out[i] + 1) {
            // 满足欧拉路径终点的条件
            cnt_end++;
        }
        else {
            // 度数差绝对值大于 1，不可能存在欧拉路/回路
            cout << "***\n";
            return 0;
        }
    }

    // 判定度数条件是否满足欧拉路径或欧拉回路的定义
    // 欧拉路径: 1个起点 (out=in+1), 1个终点 (in=out+1), 其余平衡
    // 欧拉回路: 0个起点, 0个终点 (所有点平衡 out=in)
    bool ok  = (cnt_start == 1 && cnt_end == 1 ) || (cnt_start == 0 && cnt_end == 0);
    if (!ok) {
        cout << "***\n";
        return 0;
    }

    // 如果是欧拉回路的情况 (cnt_start == 0)，此时 start 可能不是最优起点。
    // 为了满足字典序最小，需要找到第一个出现的、有出度（可以作为起点）的字母。
    if (cnt_start == 0) {
        start = -1; // 重置 start，重新寻找
        for(int i = 0; i <= 25; ++i) {
            // 找到第一个存在的且有出边的字母
            if(exist[i] && out[i] > 0) {
                start = i;
                break;
            }
        }
    }
    // 注意：如果此时 start 仍为 -1，说明虽然满足度数平衡，但所有点都没有出度（图是空的或只有独立的点），
    // 这种边界情况在本题 N>=1 的约束下不会发生。
    
    // 【连通性检查】使用并查集判断所有出现过的点是否在同一个弱连通分量中
    int root = find(start); // 获取起点的集合代表元素
    for(int i = 0; i <= 25; ++i) {
        // 如果某个存在的点与起点不在同一个集合，说明图不连通
        if (exist[i] && find(i) != root) {
            cout << "***\n";
            return 0;
        }
    }

    // 执行 Hierholzer 算法寻找路径
    dfs(start);

    // 输出结果
    bool first = 1; // 标记是否是第一个输出的单词，用于控制点的输出

    // 栈中存储的是逆序的路径，出栈顺序即为正确顺序
    while (ans.empty() == false) {
        if (!first) cout << "."; // 如果不是第一个单词，先输出点分隔符
        cout << ans.top(); // 输出栈顶单词
        ans.pop();         // 弹出栈顶
        first = 0;         // 更新标记
    }
    
    return 0;
}
