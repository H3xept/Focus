#include "bstrlib.h"
#include "focus.h"
#include "dbg.h"
#include "db.h"
#include <stdlib.h>

FILE* CF_open(const char* path,const char* mode)
{
	FILE* config_file = NULL;
	config_file = fopen(path,mode);
	check(config_file,"Could not open file {%s}.",path);
	return config_file;

error:
	if(config_file) free(config_file);
	return NULL;
}

void CF_close(FILE* config_file)
{
	fclose(config_file);
}

int CF_match(FILE* config_file, const char* url)
{
	bstring data = NULL;
	bstring line = bfromcstr(url);
	int rt = -1;

	data = bread((bNread)fread,config_file);
	check(data,"Could not retrieve data from config file.");

	if(binstr(data,0,line) != BSTR_ERR) rt = 1;
	else rt = 0;

	rewind(config_file);

	return rt;

error:
	if(data) free(data);
	return rt;

}

FILE* CF_override(FILE* config_file, const char* content)
{
	fclose(config_file);

	FILE* new_file = fopen(FILE_PATH,"w");
	check(new_file,"Root privileges needed in order to edit entries.");

	fprintf(config_file,"%s",content);
	
	return new_file;
error:
	if(new_file) free(new_file);
	return NULL;
}






