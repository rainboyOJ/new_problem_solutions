from math import ceil
s,v=map(int,input().split())
need=ceil(s/v)+10
h,m=divmod((8*60-need)%(24*60),60)
print(f"{h:02d}:{m:02d}", end="")
