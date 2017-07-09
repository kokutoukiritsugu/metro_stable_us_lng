#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define UTF16LEBOM "\xFF\xFE"

char *read_str(FILE *, char *);

void utf16_out(char *, FILE *);

long get_file_size(FILE *);

int main() {
    char *s_temp = malloc(sizeof(char) * 65535);

    FILE *fp_string = fopen("string", "rb");
    FILE *fp_table = fopen("table", "rb");
    FILE *fp_out = fopen("out.ini", "wb+");
    fputs(UTF16LEBOM, fp_out);
    utf16_out("[lng]\r\n", fp_out);

    long table_size = get_file_size(fp_table);
    long string_size = get_file_size(fp_string);

    char *table = malloc(sizeof(char) * (table_size));
    for (int i = 0; i < table_size; ++i) {
        table[i] = fgetc(fp_table);
    }

    while (ftell(fp_string) != string_size) {
        char *str = read_str(fp_string, s_temp);
        utf16_out("\"", fp_out);
        utf16_out(str, fp_out);
        utf16_out("\"", fp_out);

        char *s = read_str(fp_string, s_temp);
        utf16_out("=", fp_out);
        utf16_out("\"", fp_out);
        for (int j = 0; j < strlen(s); ++j) {
            fputc(table[((unsigned char) s[j]) * 2], fp_out);
            fputc(table[((unsigned char) s[j]) * 2 + 1], fp_out);
        }
        utf16_out("\"", fp_out);

        utf16_out("\r\n", fp_out);
    }

    fclose(fp_string);
    fclose(fp_table);
    fclose(fp_out);
    return 0;
}

long get_file_size(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return file_size;
};

void utf16_out(char *str, FILE *fp) {
    size_t str_len = strlen(str);
    for (size_t j = 0; j < str_len; ++j) {
        fputc(str[j], fp);
        fputc('\x00', fp);
    }
}

char *read_str(FILE *fp, char *s_temp) {
    s_temp[0] = '\0';
    for (int i = 0, c = 0; (c = fgetc(fp)) != '\0'; i++) {
        s_temp[i] = (char) c;
        s_temp[i + 1] = '\0';
    }

    char *s2 = malloc(sizeof(char) * (strlen(s_temp) + 1));
    strcpy(s2, s_temp);
    return s2;
}
