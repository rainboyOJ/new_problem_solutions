/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int main(){
	int m,n,a,i,cnt = 0;
	scanf("%d%d",&m,&n);
	for(i = 1;i<=n;i++){
		scanf("%d",&a);
		if( a > m )
			cnt++;
		else
			m = m - a;
	}
	printf("%d",cnt);
	return 0;
}
