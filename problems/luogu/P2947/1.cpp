/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-31 11:21:52
 */
#include <algorithm>
#include <bits/stdc++.h>
#include <stack>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn]; // 存储牛的高度


// 从后往前遍历，所以答案需要倒序存储
std::vector<int> ans;

// 单调栈，存储牛的下标
std::stack<int> stk;

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }

    // 从后往前遍历，寻找每个元素右边第一个比它大的元素
    for(int i = n;i >= 1;i--) {
        // std::cout << "deal " << a[i] <<   "\n";


        // 维护单调栈：当栈不为空，且栈顶牛的高度小于等于当前牛的高度时，
        // 说明栈顶的牛不可能成为在当前牛左边任何一头牛的答案（因为它更近且更矮，被当前牛挡住了），
        // 所以将其弹出。
        while( stk.empty() == false && a[stk.top()] <= a[i] )
            stk.pop();

        // 经过上面的循环，栈顶的元素（如果存在）就是i右边第一个比a[i]大的牛的下标
        if( stk.empty() ) 
            ans.push_back(0); // 如果栈为空，说明右边没有比它高的牛
        else
            ans.push_back(stk.top()); // 否则，栈顶就是答案

        // 将当前牛的下标压入栈中，作为后续（左边）牛的候选答案
        stk.push(i);
    }


    // 因为是倒序遍历得到的答案，所以需要反转
    std::reverse(ans.begin(),ans.end());
    for( auto u: ans) std::cout << u << "\n";
    
    return 0;
}
