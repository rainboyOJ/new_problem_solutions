count = int(input())
numbers = map(int, input().split())
seen = set()
answer = []
for number in numbers:
    if number not in seen:
        seen.add(number)
        answer.append(number)
print(*answer)
