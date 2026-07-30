/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
#include <algorithm>
using namespace std;

int n,t;
int a[1000];
int cnt = 0;

int main(){
	scanf("%d",&n);
	int i;
	for(i=1;i<=n;i++){
		scanf("%d",&t);
		if( t % 2 == 1){
			cnt++;
			a[cnt] = t;
		}
	}
	sort(a+1,a+cnt+1);
	printf("%d",a[1]);
	for(i=2;i<=cnt;i++)
		printf(",%d",a[i]);
	

	return 0;
}
