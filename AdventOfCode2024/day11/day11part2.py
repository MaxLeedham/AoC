from functools import cache

@cache
def blink(stone, iterations):
    if iterations <= 0:
        return 1

    if stone == 0:
        return blink(1, iterations - 1)

    num_digits = len(str(stone))
    if num_digits % 2 == 0:
        left_half = stone // (10 ** (num_digits // 2))
        right_half = stone - (left_half * (10 ** (num_digits // 2)))
    
        return blink(left_half, iterations-1) + blink(right_half, iterations-1)

    return blink(stone * 2024, iterations-1)

with open("input.txt", "r") as f:
    stones = [int(x) for x in f.readline().split(" ")]

total = 0

for stone in stones:
    total += blink(stone, 75)

print(f"Total: {total}")