/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int  main(){
	long long n;
	scanf("%lld",&n);
	while( n != 1) {
		long long  ans;
		if( n % 2 == 1){
			ans = n*3+1;
			printf("%lld*3+1=%lld\n",n,ans);
		}
		else {
			ans =n /2;
			printf("%lld/2=%lld\n",n,ans);
		}
		n = ans;
	}
	printf("End");
	return 0;
}
