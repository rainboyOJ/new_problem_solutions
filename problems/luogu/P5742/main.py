def is_excellent(academic, quality):
    return academic + quality > 140 and academic * 7 + quality * 3 >= 800


n = int(input())

for _ in range(n):
    student_id, academic, quality = map(int, input().split())
    if is_excellent(academic, quality):
        print("Excellent")
    else:
        print("Not excellent")
