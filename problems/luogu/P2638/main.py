from math import comb


n, zeros, ones = map(int, input().split())
print(comb(n + zeros, zeros) * comb(n + ones, ones))
