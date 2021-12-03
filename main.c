#include <stdio.h>
#include <stdlib.h>
#define uc unsigned char
#define ul unsigned long

//typedef union UNPACKING_BITS{
//    char input_byte;
//    struct bits {
//        uc b0;
//        uc b1;
//        uc b2;
//        uc b3;
//        uc b4;
//        uc b5;
//        uc b6;
//        uc b7;
//    };
//} UNPACK;


void byte_to_bits (FILE *fin, char *result_array) {
    char byte = '\0';
    byte = fgetc(fin);
    for (int i = 0; i < 8; i++) {
        if (((byte >> i) & 1) == 1) result_array[i] = 1;
        else result_array[i] = 0;
    }
}
unsigned long bitwise_shift_4 (unsigned char basic_size[4]) {
    unsigned long total_num = 0;
    total_num = total_num | basic_size[0];
    total_num = total_num | basic_size[1] << 8;
    total_num = total_num | basic_size[2] << 16;
    total_num = total_num | basic_size[3] << 24;
    return total_num;
}
unsigned long bitwise_shift_2 (unsigned char basic_size[2]) {
    unsigned long total_num = 0;
    total_num = total_num | basic_size[0];
    total_num = total_num | basic_size[1] << 8;
    return total_num;
}
void foo(int x) {
    printf("%d", x);
    
}
typedef struct tag_BM_file_header {
    uc bf_type[2];
    uc bf_size[4];
    uc bf_reserved_1[2];
    uc bf_reserved_2[2];
    uc bf_off_bits[4]; // оффсет, с которого начинаются данные
} tag_BM_file_header;



void game_of_life (int height, int width, char *previous_situation[]) {
    
    int real_height = height + 2;
    int real_width = width + 2;
    int counter_death_cells = 0;
    int counter_living_cells = 0;
    char current_situation[real_height][real_width];
//    char previous_situation[real_height][real_width];
    for (int i = 1; i < height; i++) {
        for (int j = 1; j < width; j++) {
            if (previous_situation[i - 1][j - 1] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if (previous_situation[i - 1][j] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if (previous_situation[i - 1][j + 1] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if (previous_situation[i][j - 1] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if (previous_situation[i][j + 1] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if (previous_situation[i + 1][j - 1] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if (previous_situation[i + 1][j] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if (previous_situation[i + 1][j + 1] == 1) counter_death_cells++;
            else counter_living_cells++;
            
            if ((previous_situation[i][j] == 0) && ((counter_living_cells == 2) || (counter_living_cells == 3))) {
                current_situation[i][j] = 0;

            }
            else if ((previous_situation[i][j] == 1) &&(counter_living_cells == 3)) {
                current_situation[i][j] = 0;
            }
            else {
                current_situation[i][j] = 1;
            }
        }
    }
    printf("\n");
    for (int t = 0; t < 6; t++) {
        printf("\n");
        for (int n = 0; n < 12; n++) {
            printf("%d ", current_situation[t][n]);
        }
    }
}


int main(int argc, const char * argv[]) {
//    int game_box[10][10];
    FILE *fin, *fout;
    uc buffer_array[4];
//    if (argc != 5) {
//        fprintf(stderr, "Проверьте количество параметров\n");
//        return EXIT_FAILURE;
//    }
//    if (argv[0] == "--input") {
//        input_file =
//    }
    
    fin = fopen ("/Users/artemparfenov/Downloads/12_on_6_px.bmp", "rb");
//    fout = fopen ("/Users/artemparfenov/Downloads/new_bmp.bmp", "rb");
//    char head[2];
    tag_BM_file_header current_header;
    fread(current_header.bf_type, sizeof(char), 2, fin);
    fread(current_header.bf_size, sizeof(char), 4, fin);
    fread(current_header.bf_reserved_1, sizeof(char), 2, fin);
    fread(current_header.bf_reserved_2, sizeof(char), 2, fin);
    fread(current_header.bf_off_bits, sizeof(char), 4, fin);
    ul size_of_file = bitwise_shift_4(current_header.bf_size);
    
    ul data_offSet = bitwise_shift_4(current_header.bf_off_bits);
    char array_of_service_information[62];
//    for (int i = 0; i < data_offSet; i++) {
//
//    }
    
    
//    printf("%lu уваолцрцаи \n\n", data_offSet);
//    printf ("%lu", size_of_file);
//    printf ("\n");
    fread(buffer_array, sizeof(char), 4, fin);
    fread(buffer_array, sizeof(char), 4, fin);
    ul image_width = bitwise_shift_4(buffer_array);
    int insignificant_bytes;
    
    
    int num_of_bytes_per_string = (image_width / 8) + 1;
    int size_of_block = (num_of_bytes_per_string / 4 + 1) * 4;
    fread(buffer_array, sizeof(char), 4, fin);
    ul image_height = bitwise_shift_4(buffer_array);
    fread(buffer_array, sizeof(char), 2, fin);
    fread(buffer_array, sizeof(char), 2, fin);
    ul j = bitwise_shift_2(buffer_array);
//    printf("%lu уваолцрцаи \n\n", j);
//    char temp_arrr[20];
    fseek(fin, data_offSet, SEEK_SET);
    char array_of_bits[8];
    int important_bits_in_last_byte = image_width % 8;
    int counter_elements = 0;
    int real_height = image_height + 2;
    int real_width = image_width + 2;
    char tmp_result_array[real_height][real_width];
    int current_ptr = ftell(fin);
    for (int k = image_height - 1; k >= 0; k--) {
        counter_elements = 0;
        current_ptr = ftell(fin);
        for (int i = 0; i < num_of_bytes_per_string; i++) {
            if (i == num_of_bytes_per_string - 1) {
                
                byte_to_bits(fin, array_of_bits);
                for (int i = 1; i < important_bits_in_last_byte; i++) {
                    tmp_result_array[k][counter_elements] = array_of_bits[7 - i];
                    counter_elements++;
                }
            }
            else {
                byte_to_bits(fin, array_of_bits);
//                for (int o = 0; o < 8; o++) {
//                    printf("%d ", array_of_bits[o]);
//                }
//                printf("\n");
                for (int d = 0; d < 8; d++) {
                    tmp_result_array[k][counter_elements] = array_of_bits[7 - d];
                    counter_elements++;
                }
            }
            
        }
        fseek(fin, current_ptr + size_of_block, SEEK_SET);
        

    }
    printf("\n");
    for (int t = 0; t < 6; t++) {
        printf("\n");
        for (int n = 0; n < 12; n++) {
            printf("%d ", tmp_result_array[t][n]);
        }
    }
    
    game_of_life(image_height, image_width, tmp_result_array);
    
    
    
    
    
    

    
    
    


    
    return 0;
}
