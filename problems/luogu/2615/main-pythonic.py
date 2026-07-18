n=int(input())
g=[[0]*n for _ in range(n)]
r,c=0,n//2
for v in range(1,n*n+1):
    g[r][c]=v
    nr,nc=(r-1)%n,(c+1)%n
    r,c=(nr,nc) if g[nr][nc]==0 else (r+1,c)
for row in g: print(*row)
