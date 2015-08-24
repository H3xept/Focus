#include "bstrlib.h"
#include "focus.h"
#include "dbg.h"
#include "db.h"
#include <stdlib.h>

char* craft_string(const char** valid_urls, int loops)
{
	char* str = malloc((sizeof(char*)*loops)+1);
	for(int milk = 0; milk < loops; milk++){
		strcat(str,"\n0.0.0.0       ");
		strcat(str,*(valid_urls+milk));
	}

	return str;
}

int del_blacklist(const char* path, const char** args, int loops)
{
	int rt = -1;
	char* temp_str = NULL;
	size_t len;
	size_t t_len = 0;
	int ext_c;
	bstring strings[loops];
	char* new_file_contents = NULL;

	for(int milk = 0; milk < loops; milk++)
	{
		strings[milk] = bfromcstr(*(args + milk));
	}

	FILE* config_file = NULL;
	config_file = CF_open(path,"r");
	check(config_file,"Could not open config file.");


	while(getline(&temp_str,&len,config_file) != -1)
	{
		t_len += len+1;
	}
	new_file_contents = malloc(t_len);

	for(int milk = 0; milk < loops; milk++)
	{	
		rewind(config_file);

		ext_c = 0;
		while(getline(&temp_str,&len,config_file) != -1)
		{

			bstring temp_bstr = bfromcstr(temp_str);
			if(binstr(temp_bstr,0,strings[milk]) == BSTR_ERR)
			{
				strcat(new_file_contents,temp_str);
				rt = 0;
			}
			else
			{
				rt = 1;
			}

		}
	}

	config_file = CF_override(config_file, new_file_contents);
	if(config_file == NULL) goto error;

	if(rt == 0) {_info("No occurrencies removed!"); rt = 1;}
	else{
		if(errno == 0) _info("All done! :) Restart your browser to confirm changes. (Be sure to exit completely from the app)");
	}
	return rt;

error:
	if(config_file) free(config_file);
	return rt;
}

int add_blacklist(const char* path, const char** args, int loops)
{
	int rt = -1;
	const char* temp_valid_urls[loops];
	const char** valid_urls = NULL;
	int t_index = 0;
	int t_counter = 0;

	FILE* config_file = NULL;
	config_file = CF_open(path,"r");
	check(config_file,"Could not open config file.");

	for(int milk = 0; milk < loops; milk++)
	{
		if(!CF_match(config_file, *(args+milk)))
		{	
			_info("URL '%s' queued for insertion.",*(args+milk));
			*(temp_valid_urls + milk) = *(args + milk);
			if(rt == -1) rt = 1;
		}
		else _warn("URL '%s' already included.",*(args+milk));
	}

	for(int milk = 0; milk < loops; milk++) { if(*(temp_valid_urls+milk)) t_counter++; }

	valid_urls = malloc(sizeof(char*)*t_counter);
	for(int milk = 0; milk < loops; milk++) { if(*(temp_valid_urls+milk)) *(valid_urls + t_index++) = *(temp_valid_urls+milk);}

	CF_close(config_file);

	config_file = CF_open(FILE_PATH,"a+");
	check(config_file, "Could not open config file. Root required to insert new entries.");

	char* comp_string = craft_string(valid_urls,t_counter);

	fprintf(config_file,"%s",comp_string);
	fclose(config_file);

	if(errno == 0) _info("All done! :) Restart your browser to confirm changes. (Be sure to exit completely from the app)");

	return rt;

error:
	if(config_file) free(config_file);
	if(valid_urls) free(valid_urls);
	return rt;
}

int main(int argc, const char *argv[])
{
	if(argc < 2) _err("No command specified! Aborting...");
	if(argc >= 2)
	{
		if(strcmp(argv[1],"-a") == 0 || strcmp(argv[1],"add") == 0){
			if(argv[2] == NULL){
				_err("Too few arguments! Usage: -a <url1> <url2> ...");
			}
			else{
				if(!add_blacklist(FILE_PATH,&argv[2],argc-2)) _err("Something went wrong... Contact @H3xept");
			}
		}
		else if(strcmp(argv[1],"-d") == 0 || strcmp(argv[1],"del") == 0)
		{
			if(argv[2] == NULL) _err("Too few arguments! Usage: -d <url1> <url2> ...");
			if(!del_blacklist(FILE_PATH,&argv[2],argc-2)) _err("Something went wrong... Contact @H3xept");
		}
		else{
			_err("Command '%s' not recognized.",argv[1]);
		}
	}

	return 0;

error:
	return -1;
}