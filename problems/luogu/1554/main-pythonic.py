L,R=map(int,input().split())
cnt=[0]*10
for x in range(L,R+1):
    while True:
        cnt[x%10]+=1
        x//=10
        if x==0: break
print(*cnt)
