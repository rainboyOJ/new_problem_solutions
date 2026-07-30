round_count = int(input())
wins_against = {"Rock": "Scissors", "Scissors": "Paper", "Paper": "Rock"}

for _ in range(round_count):
    first, second = input().split()
    if first == second:
        print("Tie")
    elif wins_against[first] == second:
        print("Player1")
    else:
        print("Player2")
