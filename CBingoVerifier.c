#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char pattern[5][5]);
 
int main() {
    // control the loop using isPlaying
    int isPlaying = 1;
    while (isPlaying) {
        char pattern[5][5];
        // Read the pattern
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (fscanf(stdin, "%s", &pattern[i][j]) == EOF) { // reach the end of input
                    isPlaying = 0;
                    break;
                }
            }
            if (!isPlaying) break;
        }
        if (!isPlaying) break;
       
        char bingoString[225];
        char* bingoCalls[75];
        char* token;
        int bingoLength = 0;
       
        fgets(bingoString, 225, stdin); 
        fgets(bingoString, 225, stdin);
        fgets(bingoString, 225, stdin);
       
        // Read the called bingo numbers
        bingoString[strlen(bingoString)] = '\0';
        token = strtok(bingoString, " "); 
        while (token != NULL) {
            bingoCalls[bingoLength++] = token;
            token = strtok(NULL, " ");
        }
       
        char card[5][5][3];
        // Read the bingo card
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                fscanf(stdin, "%s", &card[i][j]);
            }
        }
       
       // Count the number of marked numbers in the pattern
        int numPattern = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (pattern[i][j] == '1' || pattern[i][j] == '4') {
                    numPattern++;
                }
            }
        }
 
        int lastRow = -1;
        int lastCol = -1;
        for (int n = 0; n < bingoLength; n++) {
            int call = atoi(bingoCalls[n]);
            int found = 0;
           
            for (int i = 0; i < 5 && !found; i++) {
                for (int j = 0; j < 5 && !found; j++) {
                    if (atoi(card[i][j]) == call) { 
                        strcpy(card[i][j], "X"); // Mark the called number as X on the card
                        if (n == bingoLength - 1) { // Save the row and column of the last number called
                            lastRow = i;
                            lastCol = j;
                        }
                        found = 1;
                    }
                }
            }
        }
       
        if (lastRow == -1) {
            printf("NO BINGO\n");
            continue;
        }
        
       // Mark the free space with "00" as X
        strcpy(card[2][2], "X");
       
       // Array of last calls to store if the last number called is valid (1 = true, 0 = false)
        int lastCalls[4] = {0};
        if (pattern[lastRow][lastCol] == '1' || pattern[lastRow][lastCol] == '4') {
            lastCalls[0] = 1;
        }
        // If the pattern is crazy (contains 4's), rotate the pattern to verify the last number
        for (int i = 1; i <= 3; i++) {
            rotate(pattern);
            if (pattern[lastRow][lastCol] == '4') {
                lastCalls[i] = 1;
            }
        }
        rotate(pattern); 
 
        // Array of counters to store number of matching positions
        int rotateCount[4] = {0};
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                
                if ((pattern[i][j] == '1' || pattern[i][j] == '4') && strcmp(card[i][j], "X") == 0) {
                    rotateCount[0]++;
                }
               
               // If the pattern is crazy (contains 4's), rotate the pattern to count the number of matching positions
                for(int r = 1; r <= 3; r++) {
                    rotate(pattern);
                    if (pattern[i][j] == '4' && strcmp(card[i][j], "X") == 0) {
                        rotateCount[r]++;
                    }
                }
               
                rotate(pattern);
            }
        }
       
       // Return valid bingo if the last called number is valid and
       // the number of matching positions is equal to the number of marked positions on the pattern
        if ((numPattern == rotateCount[0] && lastCalls[0] == 1) ||
        (numPattern == rotateCount[1] && lastCalls[1] == 1) ||
        (numPattern == rotateCount[2] && lastCalls[2] == 1) ||
        (numPattern == rotateCount[3] && lastCalls[3] == 1)) {
            printf("VALID BINGO\n");
        } else {
            printf("NO BINGO\n");
        }
    }
 
    return 0;
}
 
// Rotate the pattern 90 degrees clockwise
void rotate(char pattern[5][5]) {
    char temp[5][5]; 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            temp[i][j] = pattern[i][j]; // temporary copy of the current pattern
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            pattern[i][j] = temp[4 - j][i]; // reassign values to pattern after rotating
        }
    }
}
