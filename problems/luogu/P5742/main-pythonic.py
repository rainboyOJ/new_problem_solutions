n = int(input())
for _ in range(n):
    _, academic, quality = map(int, input().split())
    ok = academic + quality > 140 and academic * 7 + quality * 3 >= 800
    print('Excellent' if ok else 'Not excellent')
