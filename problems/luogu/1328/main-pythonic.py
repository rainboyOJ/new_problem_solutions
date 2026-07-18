win = [
    [0, 0, 1, 1, 0],
    [1, 0, 0, 1, 0],
    [0, 1, 0, 0, 1],
    [0, 0, 1, 0, 1],
    [1, 1, 0, 0, 0],
]

n, length_a, length_b = map(int, input().split())
pattern_a = list(map(int, input().split()))
pattern_b = list(map(int, input().split()))

score_a = 0
score_b = 0

for round_index in range(n):
    gesture_a = pattern_a[round_index % length_a]
    gesture_b = pattern_b[round_index % length_b]
    if win[gesture_a][gesture_b]:
        score_a += 1
    elif win[gesture_b][gesture_a]:
        score_b += 1

print(score_a, score_b)
