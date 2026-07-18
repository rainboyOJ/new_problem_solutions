x,n=map(int,input().split())
# 周一=1 ... 周日=7；周六日不走
ans=sum(1 for i in range(n) if (x-1+i)%7 < 5)*250
print(ans)
