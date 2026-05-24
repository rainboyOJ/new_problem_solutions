#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// cur[u] 记录状态 u 下一次应该尝试按哪个键 (0-9)
// 比如 cur[u] = 3，说明 0,1,2 已经试过了，下次该试 3 了
// 这代替了原来的 bool visited 数组，更节省空间且不用循环查找
int cur[100005]; 

// 用 vector 模拟栈，避免递归导致的 Runtime Error
vector<int> path_stack; 

// 存储最终的密码数字
vector<int> ans;

int N, k_mod;

// 简单的整数幂运算
int power(int base, int exp) {
    int res = 1;
    while (exp--) res *= base;
    return res;
}

int main() {
    // 优化 I/O 速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> N && N != 0) {
        // 特殊情况处理
        if (N == 1) {
            cout << "0123456789" << endl;
            continue;
        }

        // 初始化
        k_mod = power(10, N - 2); 
        // 只需要初始化用到的状态即可，最大状态是 10^(N-1)
        int max_state = power(10, N - 1);
        for(int i = 0; i < max_state; ++i) cur[i] = 0;
        
        path_stack.clear();
        ans.clear();

        // --- 核心算法：迭代版 Hierholzer (欧拉回路) ---
        
        // 1. 从全 0 状态开始
        path_stack.push_back(0);

        // 2. 只要栈不为空，就继续处理
        while (!path_stack.empty()) {
            int u = path_stack.back(); // 获取当前所在的状态

            // 如果当前状态 u 还有路没走完 (0-9 还没试完)
            if (cur[u] < 10) {
                int i = cur[u]; // 取出当前要走的数字
                cur[u]++;       // 标记这个数字下次不能再走了(索引+1)
                
                // 计算下一个状态：去掉最高位，末尾补 i
                int v = (u % k_mod) * 10 + i;
                
                // 将新状态压入栈，相当于“递归”进去了
                path_stack.push_back(v);
            } 
            else {
                // 如果当前状态 u 无路可走了 (0-9 都试过了)
                // 这说明我们完成了一个“圈”，开始回退
                path_stack.pop_back();
                
                // 注意：path_stack 里的存是“节点”，我们需要把导致这个节点的“边”（数字）存下来
                // 如果栈不为空，说明是从 path_stack.back() 走到 u 的
                // u 的最后一位数字就是我们刚才按下的键
                if (!path_stack.empty()) {
                    ans.push_back(u % 10);
                }
            }
        }

        // --- 输出结果 ---

        // 1. 先输出 N-1 个 0，让保险箱初始化到全 0 状态
        for (int i = 0; i < N - 1; ++i) {
            cout << "0";
        }

        // 2. 倒序输出记录的数字
        // 因为我们是在“回退”的时候记录的，所以顺序是反的
        for (int i = ans.size() - 1; i >= 0; --i) {
            cout << ans[i];
        }
        
        cout << endl;
    }

    return 0;
}
