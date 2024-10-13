import java.util.Scanner;
import java.io.File;  
import java.io.FileNotFoundException;

/*
 * Author: Mya Dang
 */

class JavaBingoVerifier {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(System.in);
        
        while (sc.hasNext()) {
           // Save the pattern
           int[][] pattern = new int[5][5];        
           for (int i = 0; i < 5; i++) {
               String[] pattern_line = sc.nextLine().split(" ");
               for (int j = 0; j < 5; j++) {
                   pattern[j][i] = Integer.parseInt(pattern_line[j]);
               }
           }
           
           sc.nextLine();
           
           // Save the called bingo numbers
           String[] bingo_line = sc.nextLine().split(" ");
           int[]  bingo_numbers = new int[bingo_line.length];
           for (int i = 0; i < bingo_line.length; i++) {
               bingo_numbers[i] = Integer.parseInt(bingo_line[i]);
           }
           
           sc.nextLine();
           
           // Save the bingo card
           int[][] card = new int[5][5];
           for (int i = 0; i < 5; i++) {
               String[] card_line = sc.nextLine().split(" ");
               for (int j = 0; j < 5; j++) {
                   card[j][i] = Integer.parseInt(card_line[j]);
               }
           }
           
           if (isCrazy(pattern)) {
               if (isValidCrazyLastNumber(pattern, bingo_numbers, card)) {
                     if (isCrazyBingo(pattern, bingo_numbers, card)) {
                           System.out.println("VALID BINGO");
                     } else {
                           System.out.println("NO BINGO");
                     }
               } else {
                     System.out.println("NO BINGO");
               }
           } else {
               if (isValidLastNumber(pattern, bingo_numbers, card)) {
                     if (isBingo(pattern, bingo_numbers, card)) {
                           System.out.println("VALID BINGO");
                     } else {
                           System.out.println("NO BINGO");
                     }
               } else {
                     System.out.println("NO BINGO");
               }
           }
        }
        sc.close();   
    }
       
    // Check valid bingo
    public static boolean isBingo(int[][] pattern, int[] bingo_numbers, int[][] card) {
         for (int i = 0; i < 5; i++) {
               for (int j = 0; j < 5; j++) {
            	     if (i == 2 && j == 2) continue;
                    if (pattern[j][i] == 1 || pattern[j][i] == 4) {
                           if (!contains(bingo_numbers, card[j][i])) {
                                 return false;
                           }
                     }
               }
         }
         return true;
    }
    
    // Check if the card contains called bingo number
    public static boolean contains(int[] bingo_numbers, int num) {
         for (int n: bingo_numbers) {
               if (n == num) {
                     return true;
               }
         }
         return false;
    }
    
    // Check if the last number called is part of the winning pattern
    public static boolean isValidLastNumber(int[][] pattern, int[] bingo_numbers, int[][] card) {
         int last_num = bingo_numbers[bingo_numbers.length - 1];
         for (int i = 0; i < 5; i++) {
               for (int j = 0; j < 5; j++) {
                     if ((pattern[j][i] == 1 || pattern[j][i] == 4) && (card[j][i] == last_num)) {
                           return true;
                     }
               }
         }
         return false;
    }
    
    // Check if the card has crazy pattern
    public static boolean isCrazy(int[][] pattern) {
         for (int i = 0; i < 5; i++) {
               for (int j = 0; j < 5; j++) {
                     if (pattern[i][j] == 4) {
                           return true;
                     }
               }
         }
         return false;
    }

    
    // Rotate the pattern
    // Source: https://stackoverflow.com/questions/2799755/rotate-array-clockwise
    public static int[][] rotate(int[][] pattern) {
          int[][] result = new int[5][5];
          for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                      result[j][5-i-1] = pattern[i][j];
                }
          }
          return result;
    }
    
    // Check valid bingo for crazy pattern
    public static boolean isCrazyBingo(int[][] pattern, int[] bingo_numbers, int[][] card){
         for (int i = 0; i < 4; i++) {
               if (isBingo(pattern, bingo_numbers, card)) {
                     return true;
               }
               pattern = rotate(pattern);
         }
         return false;
    }
    
    // Check isValidLastNumber for crazy pattern
    public static boolean isValidCrazyLastNumber(int[][] pattern, int[] bingo_numbers, int[][] card) {
         for (int i = 0; i < 4; i++) {
               if (isValidLastNumber(pattern, bingo_numbers, card)) {
                     return true;
               }
               pattern = rotate(pattern);
         }
         return false;
    }
}