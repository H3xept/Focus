#ifndef _focus_h
#define _focus_h

#define FILE_PATH "//etc//hosts"
#define BK_FILE_PATH "//etc//hosts_bk"
#define MAX_BUFFER_SIZE 254
#define len(X) sizeof(X)/sizeof(X[0])

#include <stdio.h>

int add_blacklist(const char* path, const char** args, int loops);
int del_blacklist(const char* path, const char** args, int loops);
int focus_toggle(const char* path); // TODO IMPLEMENT :O
char* craft_string(const char** valid_urls, int loops);

char* disable_str(const char* str);

#endif