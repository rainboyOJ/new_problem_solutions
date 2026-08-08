rows = []

try:
    while True:
        rows.append(input().strip())
except EOFError:
    pass

n = len(rows[0])
text = "".join(rows)

answer = [n]
current = "0"
count = 0

for ch in text:
    if ch == current:
        count += 1
    else:
        answer.append(count)
        current = ch
        count = 1

answer.append(count)
print(*answer)
