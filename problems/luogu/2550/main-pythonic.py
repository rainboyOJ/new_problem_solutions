n=int(input())
win=set(map(int,input().split()))
ans=[0]*7
for _ in range(n):
    m=len(win & set(map(int,input().split())))
    if m: ans[7-m]+=1
print(*ans)
