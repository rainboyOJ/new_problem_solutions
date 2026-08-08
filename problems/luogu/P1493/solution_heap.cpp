#include <bits/stdc++.h>
using namespace std;

struct Pear {
    int A, B;
    long long V;  // V = C1*A + C2*B
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    int C1, C2, C3;
    cin >> C1 >> C2 >> C3;
    
    vector<Pear> pears(N);
    for (int i = 0; i < N; i++) {
        cin >> pears[i].A >> pears[i].B;
        pears[i].V = 1LL * C1 * pears[i].A + 1LL * C2 * pears[i].B;
        pears[i].id = i;
    }
    
    int maxCount = 0;
    
    // 按A排序
    sort(pears.begin(), pears.end(), [](const Pear& a, const Pear& b) {
        return a.A < b.A;
    });
    
    // 外层循环：枚举A0
    for (int i = 0; i < N; i++) {
        int A0 = pears[i].A;
        
        // 收集候选梨子（A >= A0）
        vector<Pear> candidates;
        for (int j = i; j < N; j++) {
            candidates.push_back(pears[j]);
        }
        
        // 按B排序
        sort(candidates.begin(), candidates.end(), [](const Pear& a, const Pear& b) {
            return a.B < b.B;
        });
        
        // 小根堆：存储V值超过当前threshold的梨子
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> heap;
        
        // 懒惰删除标记数组
        vector<bool> deleted(N, false);
        
        // 达标梨子的数量
        int count = 0;
        
        // 初始化：计算初始threshold，将梨子分为达标和待定两类
        long long threshold = C3 + 1LL * C1 * A0 + 1LL * C2 * candidates[0].B;
        
        for (const auto& pear : candidates) {
            if (pear.V <= threshold) {
                count++;
            } else {
                heap.push({pear.V, pear.id});
            }
        }
        
        maxCount = max(maxCount, count);
        
        // 内层循环：枚举B0
        for (int k = 0; k < candidates.size(); k++) {
            // 移除当前作为B0的梨子
            if (candidates[k].V <= threshold) {
                // 如果在达标集合中，直接减少计数
                count--;
            } else {
                // 如果在待定集合（堆中），标记为删除
                deleted[candidates[k].id] = true;
            }
            
            // 如果不是最后一个，更新threshold并处理堆
            if (k + 1 < candidates.size()) {
                int nextB0 = candidates[k + 1].B;
                threshold = C3 + 1LL * C1 * A0 + 1LL * C2 * nextB0;
                
                // 检查堆顶，将新达标的梨子移到达标集合
                while (!heap.empty()) {
                    auto top = heap.top();
                    long long v = top.first;
                    int id = top.second;
                    
                    // 如果已被删除，直接弹出
                    if (deleted[id]) {
                        heap.pop();
                        continue;
                    }
                    
                    // 如果达到新标准，移到达标集合
                    if (v <= threshold) {
                        heap.pop();
                        count++;
                    } else {
                        break;  // 堆顶都不达标，后面的更不达标
                    }
                }
                
                maxCount = max(maxCount, count);
            }
        }
    }
    
    cout << maxCount << endl;
    return 0;
}