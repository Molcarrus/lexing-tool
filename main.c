#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "src/lexer.h"

char* read_file(char* filename) {
    struct stat status;

    if (stat(filename, &status) < 0) {
        perror("opening file");
        return NULL;
    }

    long long file_size = status.st_size;

    char *buff = (char*)malloc(file_size + 1);
    if (!buff) {
        perror("malloc");
        return NULL;
    }

    FILE* f = fopen(filename, "rb");
    if (!f) {
        perror("opening file");
        fclose(f);
        return NULL;
    }

    fread(buff, 1, file_size, f);
    buff[file_size] = '\0';

    fclose(f);
    
    return buff;
}

void lex_file(char* filename) {
    char* buff = open_file(filename);
    
    if (buff == NULL) {
        return;
    }

    lexer* l = init_lexer(buff);

    token t;

    while ((t = next_token(l)).type != t_EOF) {
        if (t.type == ILLEGAL) {
            printf("\nERROR: illegal token: %s", t.literal);
            break;
        }

        printf("\n-> (%s, %s)", t.literal, enum_str[t.type]);
        free(t.literal);
    }

    if (t.type == t_EOF) {
        free(t.literal);
    }

    free(l);
    free(buff);

    if (t.type != ILLEGAL) assert(t.type == t_EOF);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./exefilename <filename.c>\n");
        return 0;
    }

    lex_file(argv[1]);

    return 0;
}