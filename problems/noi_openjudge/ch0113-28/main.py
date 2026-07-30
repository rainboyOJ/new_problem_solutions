from collections import Counter

count = int(input())
numbers = list(map(int, input().split()))
number, frequency = Counter(numbers).most_common(1)[0]

print(number if frequency > count // 2 else "no")
