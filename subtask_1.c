#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>


char* reverse_string(char* string) {
    char* reversed_string = (char*)malloc(sizeof(char) * strlen(string));
    for (size_t i = 0; i < strlen(string); ++i) {
        reversed_string[i] = string[strlen(string) - 1 - i];
    }
    return reversed_string;
}
size_t last_index_of(const char* string, char value) {
    size_t i = strlen(string) - 1;
    while (string[i] != value) {
        i--;
    }
    return i;
}
char* substring_from_index_to_end(const char* string, size_t fromExclusive) {
    char* substring = (char*)malloc(sizeof(char) * (strlen(string) - fromExclusive - 1));
    for (size_t i = fromExclusive + 1; i < strlen(string); ++i) {
        substring[i - fromExclusive - 1] = string[i];
    }
    return substring;
}
char* substring_from_start_to_index(const char* string, size_t toInclusive) {
    char* substring = (char*) malloc(sizeof(char) * (toInclusive + 1));
    for (size_t i = 0; i <= toInclusive; ++i) {
        substring[i] = string[i];
    }
    return substring;
}
bool is_regular_file(const char* path) {
    struct stat file_stat_struct;
    stat(path, &file_stat_struct);
    if (S_ISREG(file_stat_struct.st_mode)) {
        return true;
    }
    return false;
}


char* get_reversed_catalog_path(char* path) {
    char* catalog = substring_from_index_to_end(path, last_index_of(path, '/'));
    char* before_catalog = substring_from_start_to_index(path, last_index_of(path,'/'));
    char* reversed_catalog = reverse_string(catalog);
    char* path_to_create = (char*)malloc(sizeof(char) * strlen(path));
    strcat(path_to_create, before_catalog);
    strcat(path_to_create, reversed_catalog);
    free(catalog);
    free(before_catalog);
    free(reversed_catalog);
    return path_to_create;
}

char* get_reversed_file_name(const char* file_name) {
    char* reversed_file_name = malloc(sizeof(char) * strlen(file_name));
    char* name_without_ext = substring_from_start_to_index(file_name, last_index_of(file_name, '.') - 1);
    char* reversed_name_without_ext = reverse_string(name_without_ext);
    char* ext = substring_from_index_to_end(file_name, last_index_of(file_name, '.'));
    sprintf(reversed_file_name, "%s.%s", reversed_name_without_ext, ext);
    free(ext);
    free(reversed_name_without_ext);
    free(name_without_ext);
    return reversed_file_name;
}

void reverse_content(const char* source, const char* dest) {
    FILE* source_file, *dest_file;
    source_file = fopen(source, "r");
    dest_file = fopen(dest, "w");
    fseek(source_file, 0, SEEK_END);
    long pos = ftell(source_file);
    char symbol;
    while (pos != 0) {
        pos--;
        fseek(source_file, pos, SEEK_SET);
        symbol = (char) fgetc(source_file);
        fputc(symbol, dest_file);
    }
    fclose(source_file);
    fclose(dest_file);
}

void create_reversed_regular_files(const char* source_path, const char* dest_path) {
    DIR* dir;
    dir = opendir(source_path);
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        char* source_file_path = malloc(sizeof(char*) * strlen(source_path));
        char* dest_file_path = malloc(sizeof(char*) * strlen(source_path));
        sprintf(source_file_path, "%s%s", source_path, entry->d_name);
        if (is_regular_file(source_file_path)) {
            char* reversed_file_name = get_reversed_file_name(entry->d_name);
            sprintf(dest_file_path, "%s%s%s", dest_path, "/", reversed_file_name);
            reverse_content(source_file_path, dest_file_path);
            free(reversed_file_name);
        }
        free(source_file_path);
        free(dest_file_path);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return -1;
    }
    char* path = argv[1];
    char* path_to_create = get_reversed_catalog_path(path);
    mkdir(path_to_create, 0777);
    strcat(path,"/");
    create_reversed_regular_files(path, path_to_create);
    free(path_to_create);
    return 0;
}
