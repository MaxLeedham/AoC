rotations = []

with open("input.txt", "r") as f:
    rotations = [line.strip() for line in f.readlines()]

# rotations = ["L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"]
# rotations = ["R1000"]
# rotations = ["L685"]
# rotations = ["L5"]

dial = 50
code = 0

# dial = 0

def parse(rotation: str) -> int:
    amount = int(rotation[1::])
    return amount if rotation[0] == 'R' else -amount

# No idea why the maths way was overcounting for the real input but working for all the examples and edge cases I could think of
# I eventually just resorted to manually "turning" the dial 1 by 1
for rotation in rotations:
    turns = parse(rotation)
    # print(f"It turns {turns} times from {dial}")
    # print(f"dial + turns = {dial+turns} so (dial + turns) >= 100 = {(dial + turns) >= 100}")
    # if ((dial + turns) >= 100 or (dial + turns) <= 0) and not (dial == 0 and abs(turns) < 100):
    #     to_zero = 100 - dial if rotation[0] == "R" else (dial % 100)
    #     # print(f"dial={dial}, turns={turns} takes {to_zero} turns to get to 0")
    #     after_zero = abs(turns) - to_zero
    #     # print(f"It passes 0 after {to_zero} turns")
    #     # print(f"Which leaves {after_zero} turns after 0")
    
    #     print(f"abs(turns): {abs(turns)}")
    #     print(f"to_zero: {to_zero}")
    #     print(f"After zero: {after_zero}")
    #     code += 1
    #     code += after_zero // 100
    #     # print(f"It then passes 0 {after_zero // 100} more times")

    direction = 1 if turns > 0 else -1

    while turns:
        dial += direction
        dial = dial % 100
        if dial == 0:
            code += 1
        turns += -direction

    # For detecting if it lands on exactly 0
    # dial = (dial + turns) % 100
    # print(f"Dial is now at {dial}\n\n\n\n\n\n\n")
    # if dial == 0:
    #     code += 1

print(f"Final code: {code}")