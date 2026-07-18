def rot(p):
    n=len(p)
    return [''.join(p[n-1-r][c] for r in range(n)) for c in range(n)]
def ref(p):
    return [row[::-1] for row in p]
n=int(input())
b=[input().strip() for _ in range(n)]
a=[input().strip() for _ in range(n)]
r1,r2,r3=rot(b),rot(rot(b)),rot(rot(rot(b)))
rf=ref(b)
if r1==a: print(1)
elif r2==a: print(2)
elif r3==a: print(3)
elif rf==a: print(4)
elif any(x==a for x in (rot(rf),rot(rot(rf)),rot(rot(rot(rf))))): print(5)
elif b==a: print(6)
else: print(7)
