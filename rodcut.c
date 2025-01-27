#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int length;
    int value;
} Piece;


void rod_cutting(int rod_length, Piece* pieces, int num_pieces) {
    // allocate memory
    int* dp = (int*)calloc(rod_length + 1, sizeof(int));
    int* cuts = (int*)calloc(rod_length + 1, sizeof(int));

    // calculate the maximum value
    for (int i = 0; i < num_pieces; i++) {
        for (int j = pieces[i].length; j <= rod_length; j++) {
            if (dp[j - pieces[i].length] + pieces[i].value > dp[j]) {
                dp[j] = dp[j - pieces[i].length] + pieces[i].value;
                cuts[j] = pieces[i].length;
            }
        }
    }

    // find the cutting list
    int remaining_length = rod_length;
    int* cut_count = (int*)calloc(rod_length + 1, sizeof(int));

    // Count the number of cuts for each piece length
    while (remaining_length > 0) {
        int cut_length = cuts[remaining_length];
        if (cut_length == 0) break;
        cut_count[cut_length]++;
        remaining_length -= cut_length;
    }

    // Output the cutting list
    for (int i = 0; i <= rod_length; i++) {
        if (cut_count[i] > 0) {
            printf("%d @ %d = %d\n", cut_count[i], i, cut_count[i] * i);
        }
    }

    // Output remainder
    printf("Remainder: %d\n", remaining_length);

    // Output total value
    printf("Total value: %d\n", dp[rod_length]);

    // Free allocated memory
    free(dp);
    free(cuts);
    free(cut_count);
}

int main(int argc, char* argv[]) {
    // check for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <rod length>\n", argv[0]);
        return 1;
    }

    int rod_length = atoi(argv[1]);

    // check for valid rod length
    Piece* pieces = (Piece*)malloc(sizeof(Piece) * 100);  // Assuming at most 100 pieces
    int num_pieces = 0;
    char line[100];

    printf("Enter the piece lengths and values (e.g., 2, 5). Enter 'done' when finished:\n");

    // Read input from user
    while (1) {
        printf("Piece %d: ", num_pieces + 1);
        if (fgets(line, sizeof(line), stdin) == NULL || strcmp(line, "done\n") == 0) {
            break;
        }
        
        int length, value;
        // Parse input
        if (sscanf(line, "%d, %d", &length, &value) == 2) {
            pieces[num_pieces].length = length;
            pieces[num_pieces].value = value;
            num_pieces++;
        } else {
            printf("Invalid input, please enter in the format 'length, value'.\n");
        }
    }

    if (num_pieces == 0) {
        printf("No valid pieces were entered.\n");
        free(pieces);
        return 1;
    }

    rod_cutting(rod_length, pieces, num_pieces);

    free(pieces);
    return 0;
}