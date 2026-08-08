import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
m = data[1]

people = []
index = 2
for _ in range(n):
    student_id = data[index]
    score = data[index + 1]
    people.append((student_id, score))
    index += 2

people.sort(key=lambda item: (-item[1], item[0]))
line_count = m * 3 // 2
line_score = people[line_count - 1][1]

chosen = [item for item in people if item[1] >= line_score]

print(line_score, len(chosen))
for student_id, score in chosen:
    print(student_id, score)
