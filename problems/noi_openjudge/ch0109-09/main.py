from collections import Counter

count = int(input())
numbers = map(int, input().split())
frequencies = Counter(numbers)

for number in range(max(frequencies) + 1):
    print(frequencies[number])
