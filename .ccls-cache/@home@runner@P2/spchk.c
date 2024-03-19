#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h> // for tolower

#define MAX_WORD_LEN 100
#define MAX_LINE_LEN 1000

void process_file(const char *filename);
void process_directory(const char *dirname);
int binary_search(const char *word, const char **dictionary, int dictionary_size);
void checkWord(const char **dictionary, int dictionary_size, const char *word, int line, int column, const char *filename);
void toLowerCase(char *str);
int isCapitalizedCorrectly(const char *word);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_or_directory> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        DIR *dir = opendir(arg);
        if (dir) {
            process_directory(arg);
            closedir(dir);
        } else {
            process_file(arg);
        }
    }

    return 0;
}

void process_file(const char *filename) { 
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LEN];
    int line_number = 1;
    while (fgets(line, MAX_LINE_LEN, file)) {
        char *word = strtok(line, " \t\n");
        int column_number = 1;
        while (word) {
            printf("%s (%d,%d)\n", word, line_number, column_number);
            word = strtok(NULL, " \t\n");
            column_number += strlen(word) + 1;
        }
        line_number++;
    }

    fclose(file);
}

void process_directory(const char *dirname) {
    DIR *dir = opendir(dirname);
    struct dirent *entry;

    if (!dir) {
        fprintf(stderr, "Error opening directory: %s\n", dirname);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        char path[MAX_LINE_LEN];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        FILE *file = fopen(path, "r");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", path);
            continue;
        }

        printf("Processing file: %s\n", path);

        char line[MAX_LINE_LEN];
        int line_number = 1;
        while (fgets(line, MAX_LINE_LEN, file)) {
            char *word = strtok(line, " \t\n");
            int column_number = 1;
            while (word) {
                printf("%s (%d,%d)\n", word, line_number, column_number);
                word = strtok(NULL, " \t\n");
                column_number += strlen(word) + 1;
            }
            line_number++;
        }

        fclose(file);
    }

    closedir(dir);
}

int binary_search(const char *word, const char **dictionary, int dictionary_size) {
    int low = 0, high = dictionary_size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int res = strcmp(dictionary[mid], word);

        if (res == 0)
            return 1; // Word found
        else if (res > 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0; // Word not found
}

void checkWord(const char **dictionary, int dictionary_size, const char *word, int line, int column, const char *filename) {
    char *lowerCaseWord = strdup(word);
    if (!lowerCaseWord) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    toLowerCase(lowerCaseWord);

    if (!binary_search(lowerCaseWord, dictionary, dictionary_size)) {
        printf("%s:%d:%d: %s is not in the dictionary\n", filename, line, column, word);
    } else if (!isCapitalizedCorrectly(word)) {
        printf("%s:%d:%d: %s is not capitalized correctly\n", filename, line, column, word);
    }

    free(lowerCaseWord);
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int isCapitalizedCorrectly(const char *word) {
    if (!isupper(word[0])) {
        return 0; // First letter is not capitalized
    }
    for (int i = 1; word[i]; i++) {
        if (isupper(word[i])) {
            return 0; // Subsequent letters are capitalized
        }
    }
    return 1; // Capitalized correctly
}
