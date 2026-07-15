n = int(input())
numbers = list(map(int, input().split()))
values = set(numbers)

can_be_sum = set()

for i in range(n):
    for j in range(i + 1, n):
        total = numbers[i] + numbers[j]
        if total in values:
            can_be_sum.add(total)

print(len(can_be_sum))
