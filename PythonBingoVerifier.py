# Author: Mya Dang

import sys

def check(pattern, call, card):
    """Check if there is a valid bingo match and valid last number."""
    temp = [row[:] for row in pattern]
    valid_last_call = False
    
    # Check if the last bingo number called is part of the winning pattern
    for i in range(5):
        for j in range(5):
            if card[i][j] == call[-1]:
                valid_last_call = (temp[i][j] == 1)
    
    # Mark the called bingo numbers as 0 on the card to clear the pattern
    for i in range(5):
        for j in range(5):
            if card[i][j] in call:
                temp[i][j] = 0
                
    # Check if the pattern is cleared (all number 1's on the pattern is called)           
    valid_match = True
    for i in range(5):
        for j in range(5):
            if pattern[i][j] == 1 and temp[i][j] != 0:
                valid_match = False
                break
        if not valid_match:
            break
    
    return valid_last_call and valid_match
    
def rotate(pattern):
    """Rotate the pattern 90 degrees clockwise."""
    temp = [[0] * 5 for _ in range(5)]
    for i in range(5):
        for j in range(5):
            temp[i][j] = pattern[4-j][i]
    return temp

def main():
    input = sys.stdin.read().strip().splitlines() 
    line = 0
    
    while line < len(input):
        # Read the pattern
        pattern = []
        for i in range(5):
            pattern.append(list(map(int, input[line].split())))
            line += 1
        pattern[2][2] = 0 
        
        line += 1
        
        # Read the called bingo numbers
        call = list(map(int, input[line].split()))
        line += 2

        # Read the bingo card
        card = []
        for i in range(5):
            card.append(list(map(int, input[line].split())))
            line += 1
            
        # Check if the pattern is crazy
        crazy_pattern = False
        for row in pattern:
            for num in row:
                if num == 4:
                    crazy_pattern = True
                    break
            if crazy_pattern:
                break
        
        if crazy_pattern:
            # Save 4 rotated patterns and check each if there is valid bingo
            pat1 = [[1 if pattern[i][j] == 4 else 0 for j in range(5)] for i in range(5)]
            pat2 = rotate(pat1)
            pat3 = rotate(pat2)
            pat4 = rotate(pat3)
            
            is_bingo = False
            for pat in [pat1, pat2, pat3, pat4]:
                if check(pat, call, card):
                    is_bingo = True
                    break
            
            if is_bingo:
                print("VALID BINGO")
            else:
                print("NO BINGO")
        else:
            # Check for straight patterns
            if check(pattern, call, card):
                print("VALID BINGO")
            else:
                print("NO BINGO")
            
if __name__ == "__main__":
    main()