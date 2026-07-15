import sys


def parse_records():
    records = []
    for ch in sys.stdin.read():
        if ch == "E":
            break
        if ch == "W" or ch == "L":
            records.append(ch)
    return records


def build_scores(records, target):
    scores = []
    win = 0
    lose = 0

    for ch in records:
        if ch == "W":
            win += 1
        else:
            lose += 1

        if max(win, lose) >= target and abs(win - lose) >= 2:
            scores.append((win, lose))
            win = 0
            lose = 0

    scores.append((win, lose))
    return scores


records = parse_records()

for win, lose in build_scores(records, 11):
    print(f"{win}:{lose}")

print()

for win, lose in build_scores(records, 21):
    print(f"{win}:{lose}")
