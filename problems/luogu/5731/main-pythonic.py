n=int(input())
g=[[0]*n for _ in range(n)]
dirs=[(0,1),(1,0),(0,-1),(-1,0)]
r=c=d=0
for v in range(1,n*n+1):
    g[r][c]=v
    nr,nc=r+dirs[d][0],c+dirs[d][1]
    if not (0<=nr<n and 0<=nc<n) or g[nr][nc]:
        d=(d+1)%4
        nr,nc=r+dirs[d][0],c+dirs[d][1]
    r,c=nr,nc
for row in g:
    print(''.join(f'{x:3d}' for x in row))
