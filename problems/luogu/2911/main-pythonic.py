from collections import Counter
from itertools import product

s1, s2, s3 = map(int, input().split())
count = Counter(a + b + c for a, b, c in product(range(1, s1 + 1), range(1, s2 + 1), range(1, s3 + 1)))
print(min(total for total, times in count.items() if times == max(count.values())))
