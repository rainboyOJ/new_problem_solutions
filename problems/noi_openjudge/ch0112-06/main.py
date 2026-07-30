from bisect import bisect_left

floor_count, room_count = map(int, input().split())
floors = []

for _ in range(floor_count):
    rooms = [tuple(map(int, input().split())) for _ in range(room_count)]
    stairs = [room for room, (has_stairs, _) in enumerate(rooms) if has_stairs]
    floors.append((rooms, stairs))

room = int(input())
password = 0
for rooms, stairs in floors:
    has_stairs, number = rooms[room]
    password = (password + number) % 20123
    first_stair = bisect_left(stairs, room) % len(stairs)
    room = stairs[(first_stair + number - 1) % len(stairs)]

print(password)
