import sys

sys.setrecursionlimit(10_000)

while True:
    piece_count = int(input())
    if piece_count == 0:
        break
    pieces = sorted(map(int, input().split()), reverse=True)
    total_length = sum(pieces)
    longest_piece = pieces[0]

    for original_length in range(longest_piece, total_length + 1):
        if total_length % original_length:
            continue
        used = [False] * piece_count

        def search(completed: int, current_length: int, start: int) -> bool:
            if completed == total_length:
                return True
            if current_length == original_length:
                return search(completed, 0, 0)
            previous_length = -1
            for index in range(start, piece_count):
                piece = pieces[index]
                if used[index] or piece == previous_length or current_length + piece > original_length:
                    continue
                used[index] = True
                if search(completed + piece, current_length + piece, index + 1):
                    return True
                used[index] = False
                previous_length = piece
                if current_length == 0 or current_length + piece == original_length:
                    return False
            return False

        if search(0, 0, 0):
            print(original_length)
            break
