round_count, a_length, b_length = map(int, input().split())
a_pattern = list(map(int, input().split()))
b_pattern = list(map(int, input().split()))

# 每种拳能战胜的拳：石头 0 胜剪刀 2，剪刀 2 胜布 5，布 5 胜石头 0。
wins_against = {0: 2, 2: 5, 5: 0}
a_wins = sum(wins_against[a_pattern[i % a_length]] == b_pattern[i % b_length] for i in range(round_count))
b_wins = sum(wins_against[b_pattern[i % b_length]] == a_pattern[i % a_length] for i in range(round_count))

if a_wins > b_wins:
    print("A")
elif a_wins < b_wins:
    print("B")
else:
    print("draw")
