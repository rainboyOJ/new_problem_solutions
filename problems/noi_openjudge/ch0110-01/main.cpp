/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

char str[105][105];
int xh[105];
double fs[105];
int n,k;
int main(){
	int i,j;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++){
		scanf("%s",str[i]);
		xh[i] = i;
		scanf("%lf",&fs[i]);
	}
	for(i=1;i<=n-1;i++)
		for(j=1;j<=n-i;j++){
			if( fs[j] > fs[j+1]){
				double t = fs[j];
				fs[j] = fs[j+1];
				fs[j+1] = t;
				
				int x = xh[j];
				xh[j] = xh[j+1];
				xh[j+1] = x; 
			} 
		}
	int p = n-k+1;
	printf("%s %g",str[xh[p]],fs[p]); 
	
	return 0;
}
