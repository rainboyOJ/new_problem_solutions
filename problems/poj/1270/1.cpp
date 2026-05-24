/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-18 10:14:48
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 300;
int n,m;
int sz;
char a[maxn]; //所有字符

bool del[maxn];
int indg[maxn]; //每个点的入度

int g[maxn][maxn]; //邻居矩阵
char topsort[maxn];

std::string s;


void dfs(char u,int dep) {

    topsort[dep] = u;
    del[u] = 1;
    // std::cout << "dfs > " << u << "  >dep = " << dep << "\n";

    if( dep == sz) { //删除的点已经结束了
        // std::cout << "-------------------------" << "\n";
        for(int i = 1;i <= sz ;++i ) // i: 1->n
            cout << topsort[i];
        std::cout << "\n";
        // std::cout << "-------------------------" << "\n";
        del[u] = 0;
        return ;
    }

    // 删除u周围的点
    for(int i = 1;i <= sz ;++i ) // i: 1->sz
    {
        char c = a[i];
        if( del[c] == 0 && indg[c] > 0 && g[u][c])
            indg[c]--;
    }

    // 开始遍历 
    for(int i = 1;i <= sz ;++i ) // i: 1->sz
    {
        char c = a[i];
        if( del[c] == 0 && indg[c] == 0)
            dfs(c,dep+1);
    }

    // 恢复u周围的点
    for(int i = 1;i <= sz ;++i ) // i: 1->sz
    {
        char c = a[i];
        // u周围的点的值都有添加+1,因为相当于把u恢复了
        if( del[c] == 0 && g[u][c])
            indg[c]++;
    }

    del[u] = 0;

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);

    while( getline(cin,s) ) {

        memset(g,0,sizeof(g));
        memset(indg,0,sizeof(indg));
        memset(del,0,sizeof(del));

        sz = 0;
        for(int i = 0 ;i < s.length() ;i++) 
        {
            if( s[i] < 'a' || s[i] > 'z') continue;
            a[++sz]  = s[i];
        }
        std::sort(a+1,a+1+sz); // 排序

        getline(cin,s);

        //依次处理每个元素字符
        int first = 1;
        char st,ed;
        for(int i = 0 ;i < s.length() ;i++) {
            char c = s[i];
            if( c <'a' || c > 'z') continue;// 不是合法的字符,可能是空格
            if( first )  {
                st = c;
            }
            else {
                ed = c;
                g[st][ed] = 1; //存图
                indg[ed]++;
                // std::cout << st << " " << ed << endl;
            }
            first ^=1;
        }

        for(int i = 1 ;i<=sz;i++) {
            char c = a[i];
            if( indg[c] == 0) {
                dfs(c,1);
            }
        }
        std::cout << "\n";

    }
    
    return 0;
}
