ticket_count = int(input())
winning = set(map(int, input().split()))

answer = [0] * 7

for _ in range(ticket_count):
    ticket = set(map(int, input().split()))
    match_count = len(winning & ticket)
    if match_count > 0:
        answer[7 - match_count] += 1

print(*answer)
