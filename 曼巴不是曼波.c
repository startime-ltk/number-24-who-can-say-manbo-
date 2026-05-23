#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

const char *words[] = {"曼波", "哈基米", "我", "南北绿豆", "曼巴"};
int word_lens[] = {2, 3, 1, 4, 2}; 
const int WORD_COUNT = 5;

int count_chinese_chars(const char *str) {
    int count = 0;
    int i = 0;
    int len;
    unsigned char c;
    
    if (str == NULL) return 0;
    len = strlen(str);
    
    while (i < len) {
        c = (unsigned char)str[i];

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            i++;
            continue;
        }
        

        if (c >= 0x81 && c <= 0xFE) {
            count++;
            i += 2;
        } else if (c < 128) {
            i++;
        } else {
            i++;
        }
    }
    return count;
}

int is_all_chinese(const char *str) {
    int i = 0;
    int len;
    unsigned char c;
    
    if (str == NULL) return 0;
    len = strlen(str);
    
    while (i < len) {
        c = (unsigned char)str[i];
        if (c == ' ' || c == '\t') {
            i++;
            continue;
        }
        
        if (c == '\n' || c == '\r' || c == '\0') {
            break;
        }
        
        if (c < 128) {
            return 0;
        }
        if (c >= 0x81 && c <= 0xFE) {

            if (i + 1 >= len) {
                return 0;
            }

            unsigned char c2 = (unsigned char)str[i+1];
            if (c2 < 0x40 || c2 > 0xFE || c2 == 0x7F) {
                return 0;
            }
            i += 2;
        } else {

            return 0;
        }
    }
    return 1;
}


int is_bye(const char *str) {
    char *bye = "拜拜";
    int i = 0;
    int j = 0;
    int len;
    
    if (str == NULL) return 0;
    len = strlen(str);
    

    while (i < len && (str[i] == ' ' || str[i] == '\t')) {
        i++;
    }
    

    while (i < len && j < 4) {
        if (str[i] == bye[j]) {
            i++;
            j++;
        } else {
            return 0;
        }
    }
    

    while (i < len) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            return 0;
        }
        i++;
    }
    
    return (j == 4);
}


void generate_replacement(int target_len, char *result) {
    int current_len = 0;
    int remaining;
    int valid_words[WORD_COUNT];
    int valid_count;
    int idx;
    int i;
    
    result[0] = '\0';
    
    while (current_len < target_len) {
        remaining = target_len - current_len;
        valid_count = 0;
        

        for (i = 0; i < WORD_COUNT; i++) {
            if (word_lens[i] <= remaining) {
                valid_words[valid_count] = i;
                valid_count++;
            }
        }
        
        if (valid_count == 0) {
        
            strcat(result, "我");
            current_len += 1;
        } else {
     
            idx = valid_words[rand() % valid_count];
            strcat(result, words[idx]);
            current_len += word_lens[idx];
        }
    }
}

int main() {
    char input[1000];
    char output[2000];
    int char_count;

    SetConsoleOutputCP(936);
    SetConsoleCP(936);
    

    srand((unsigned int)time(NULL));
    
    printf("========================================\n");
    printf("  man！输入中文我将输出曼波语\n");

    printf("========================================\n\n");
    
    while (1) {
        printf("请输入一句中文：\n");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        

        input[strcspn(input, "\n")] = '\0';
        

        if (is_bye(input)) {
            printf("\n曼巴 out\n");
            break;
        }
        

        if (!is_all_chinese(input)) {
            printf("错误：输入只能包含中文汉字！\n\n");
            continue;
        }
        
        char_count = count_chinese_chars(input);
        
        if (char_count == 0) {
            printf("错误：请输入至少一个汉字！\n\n");
            continue;
        }
        
        printf("输入字数：%d\n", char_count);
        generate_replacement(char_count, output);
        printf("替换结果：%s\n\n", output);
    }
    
    return 0;
}

