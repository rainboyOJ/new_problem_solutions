/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-02 08:36:41
 * oj: luogu-1972
 * title: [SDOI2009] HH 的项链
 * description: 区间不同值的数量
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;


// 快读模板示例
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int maxn = 2e6+5;
int n,m;
int a[maxn];
int cnt[maxn];// cnt[i] 数字i出现的次数
int cnt_diff; // 不同数字的数量
int ans[maxn]; // ans 序列

// 扩大区间到x
void add(int x) {
    int num = a[x];
    cnt[num]++;
    if( cnt[num] == 1) cnt_diff++;
}

void del(int x) {
    int num = a[x];
    cnt[num]--;
    if(cnt[num]==0) cnt_diff--;
}


// block
int pos[maxn]; // pos[i]表示 i所在的块
int block_size;

struct Quer{int l,r,idx;};
Quer qur[maxn];

bool cmp(Quer & a,Quer &b) {
    if( pos[a.l] != pos[b.l])
        return pos[a.l] < pos[b.l];
    // todo 奇偶性优化
    if(pos[a.l] & 1) return a.r > b.r;
    return a.r < b.r;
}

void init(){
    // scanf("%d",&n);
    n = read();
    block_size = sqrt(n);
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        a[i] = read();
    }
    // scanf("%d",&m);
    m = read();
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        // scanf("%d%d",&qur[i].l,&qur[i].r);
        qur[i].l = read();
        qur[i].r = read();
        qur[i].idx = i;
    }

    // init block
    for(int i =1;i<=n;i++) {
        pos[i] = (i-1)/block_size + 1;
    }

    sort(qur+1,qur+1+m,cmp);

}

signed main (int argc, char *argv[]) {
    init();

    int L = 1,R=0; // why ? 这样初始化
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        while(L < qur[i].l ) del(L++);
        while(R > qur[i].r ) del(R--);
        while(L > qur[i].l ) add(--L);
        while(R < qur[i].r ) add(++R);
        ans[qur[i].idx] = cnt_diff;
    }
    for(int i = 1;i <= m ;++i ) // i: 1->n
    {
        printf("%d\n",ans[i]);
    }

    return 0;
}
