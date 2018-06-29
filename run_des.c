#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * des.h provides the following functions and constants:
 *
 * generate_key, generate_sub_keys, process_message, ENCRYPTION_MODE, DECRYPTION_MODE
 *
 */
#include "des.h"

// Declare file handlers
static FILE *key_file, *input_file, *output_file;

// Declare action parameters
#define ACTION_GENERATE_KEY "-g"
#define ACTION_ENCRYPT "-e"
#define ACTION_DECRYPT "-d"

// DES key is 8 bytes long
#define DES_KEY_SIZE 8

int main(int argc, char* argv[])
{
    clock_t start, finish;
    double time_taken;
    unsigned long file_size;
    unsigned short int padding;
    unsigned int iseed = (unsigned int) (&main);
    srand(iseed);

    unsigned char* des_key = "\0\0\0\0\0\0\0\0\0\0";
    unsigned long block_count = 0, number_of_blocks;
    unsigned char* data_block = (unsigned char*)malloc(8 * sizeof(char));
    unsigned char* processed_block = (unsigned char*)malloc(8 * sizeof(char));
    key_set* key_sets = (key_set*)malloc(17 * sizeof(key_set));

    // Determine process mode
    int process_mode = ENCRYPTION_MODE;

    // Get number of blocks in the file
    int i = 1;
    start = clock();
    generate_sub_keys(des_key, key_sets);
    while (i++) {
        if (i % 1000000 == 0) {
            finish = clock();
            printf("%d %ld\n", i, finish - start);
            start = clock();
        }
        generate_key(data_block);
        int ans = process_message(data_block, processed_block, key_sets, process_mode);
        if (ans || (processed_block[0] == data_block[0] && processed_block[1] == data_block[1] && processed_block[2] == data_block[2] && processed_block[3] == data_block[3] && processed_block[4] == data_block[4] && processed_block[5] == data_block[5] && processed_block[6] == data_block[6] && processed_block[7] == data_block[7])) {
            printf("found\n");
            printf("%02x%02x%02x%02x%02x%02x%02x%02x\n", data_block[0], data_block[1], data_block[2], data_block[3], data_block[4], data_block[5], data_block[6], data_block[7]);
            printf("%02x%02x%02x%02x%02x%02x%02x%02x\n", processed_block[0], processed_block[1], processed_block[2], processed_block[3], processed_block[4], processed_block[5], processed_block[6], processed_block[7]);

            break;
        }
    }

    return 0;
}
