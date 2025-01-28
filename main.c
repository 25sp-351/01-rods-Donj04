#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please input a rod length.\n");
        return 1;
    }

    int rod_length = atoi(argv[1]);
    char input[50];
    int entered_inputs = 0;
    printf("The length of the rod is %d\n", rod_length);

    while (1) {
        int length;
        int value;

        printf(
            "Enter a length followed by its value, seperated by a comma "
            "(EOF to finish): ");
        fgets(input, sizeof(input), stdin);
        
        // Check if input is end-of-file
        if (feof(stdin)) { 
            printf("\n"); // Makes sure the next print statement is on next line
            break;
        } else {
            int num_count = sscanf(input, "%d, %d", &length, &value);
            if (num_count != 2) {
                printf(
                    "Invalid input format. Input should be <length>, "
                    "<value>\n");
            } else {
                printf("Entered length %d with value %d\n", length, value);
                entered_inputs++;
            }
        }
    }
    printf("finished reading input\n");

    if (entered_inputs < 1) {
        printf("Please enter at lease one length and value\n");
        return 1;
    }

    return 0;
}
