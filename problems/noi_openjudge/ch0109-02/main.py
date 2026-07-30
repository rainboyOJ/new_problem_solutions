student_count = int(input())
best_score = -1
best_name = ""

for _ in range(student_count):
    score_text, name = input().split()
    score = int(score_text)
    if score > best_score:
        best_score = score
        best_name = name

print(best_name)
