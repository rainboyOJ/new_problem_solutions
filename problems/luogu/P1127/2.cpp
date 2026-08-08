#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXN = 30;
// adj[u] 存储从字符 u 出发的所有单词
vector<string> adj[MAXN];
int in[MAXN], out[MAXN];
int p[MAXN]; // 并查集父节点
bool exist[MAXN]; // 记录字母是否出现过
stack<string> ans; // 存储结果路径

// 并查集查找
int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void dfs(int u) {
    // 必须倒序取，或者用 vector 配合 pop_back 减少开销
    // 这里因为已经排序过(大到小)，尾部就是字典序最小的
    while (!adj[u].empty()) {
        string w = adj[u].back();
        adj[u].pop_back();
        int v = w.back() - 'a';
        dfs(v);
        ans.push(w); // 回溯时入栈（逆序）
    }
}

int main() {
    // 1. 初始化
    for (int i = 0; i < 26; i++) p[i] = i;
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int u = s.front() - 'a';
        int v = s.back() - 'a';
        
        // 为了方便从尾部 pop (O(1))，我们稍后将按字典序“从大到小”排序
        // 这样 vector 的尾部就是字典序最小的单词
        adj[u].push_back(s); 
        
        out[u]++;
        in[v]++;
        exist[u] = exist[v] = true;
        
        // 并查集
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) p[rootU] = rootV;
    }

    // 2. 预处理：排序邻接表
    for (int i = 0; i < 26; i++) {
        // 排序：从大到小，这样 back() 取出的是最小的
        sort(adj[i].begin(), adj[i].end(), greater<string>());
    }

    // 3. 判定欧拉路/回路并寻找起点
    int start_node = -1;
    int cnt_start = 0, cnt_end = 0;
    
    // 找起点逻辑
    for (int i = 0; i < 26; i++) {
        if (!exist[i]) continue;
        if (out[i] == in[i]) continue;
        if (out[i] == in[i] + 1) {
            start_node = i;
            cnt_start++;
        } else if (in[i] == out[i] + 1) {
            cnt_end++;
        } else {
            cout << "***"; return 0; // 度数不平衡，无解
        }
    }

    // 必须 1起1终 (路径) 或者 0起0终 (回路)
    if (!((cnt_start == 1 && cnt_end == 1) || (cnt_start == 0 && cnt_end == 0))) {
        cout << "***"; return 0;
    }

    // 如果是回路，起点设为字典序最小的有出度的点
    if (start_node == -1) {
        for (int i = 0; i < 26; i++) {
            if (exist[i] && out[i] > 0) {
                start_node = i;
                break;
            }
        }
    }

    // 4. 连通性检查 (必须只有一个连通分量)
    int root = find(start_node);
    for (int i = 0; i < 26; i++) {
        if (exist[i] && find(i) != root) {
            cout << "***"; return 0;
        }
    }

    // 5. DFS 求解
    dfs(start_node);

    // 6. 检查是否走完了所有边
    if (ans.size() != n) {
        cout << "***"; return 0;
    }

    // 7. 输出
    bool first = true;
    while (!ans.empty()) {
        if (!first) cout << ".";
        cout << ans.top();
        ans.pop();
        first = false;
    }
    
    return 0;
}

