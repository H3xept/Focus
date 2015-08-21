#include <stdio.h>

FILE* CF_open(const char* path, const char* mode);
//int CF_backup(FILE* config_file, const char* path);
//int CF_restore(FILE* curr_file, const char* bk_path, const char* default_path);
int CF_match(FILE* config_file, const char* url);
void CF_close(FILE* config_file);
int get_line_for_string(const char* string); // TODO IMPLEMENT :O
void move_stream_to_line(FILE* stream, int line); // TODO IMPLEMENT :O