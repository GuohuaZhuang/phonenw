
#ifndef _COMMON_FCGI_H_
#define _COMMON_FCGI_H_

// include files.
#include "../src/common/ext_string.h"
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <fcgiapp.h>

using std::string;
using std::ext_string;
using std::vector;
using std::map;
using std::iterator;
using std::pair;


/**
 * @brief decode url to utf-8 character.
 * @param url [input] the url to be decode.
 * @return returns a pointer to cn code url. 
 	The caller should deallocate this code url using free(3)..
 */
extern char* UrlDecode(const char* url);


#define printff(...) FCGX_FPrintF(request->out, __VA_ARGS__) 
#define get_param(KEY) FCGX_GetParam(KEY, request->envp)
#define cm_printf(...) FCGX_FPrintF(request.out, __VA_ARGS__) 


void handle_request(FCGX_Request* request, ext_string& query_str)
{
	char *value;
	printff("Content-Type: text/plain\r\n\r\n");
	if ((value = get_param("CONTENT_LENGTH")) != NULL) {
		long int n_content_length = strtol(value, &value, 10);
		char* content = new char[n_content_length];
		int i = 0;
		int ch;
		while((ch = FCGX_GetChar(request->in)) != -1)
		{
			content[i++] = (char)ch;
		}
		content[n_content_length] = '\0';
		query_str = content;
		delete[] content;
	}
	if ((value = get_param("QUERY_STRING")) != NULL)
	{
		char* cncode = UrlDecode(value);
		if(!cncode) return;
		query_str = cncode;
		free(cncode);
	}
}


#define _FCGI_START_	FCGX_Request request;									\
						FCGX_Init();											\
						FCGX_InitRequest(&request, 0, 0);						\
						while (FCGX_Accept_r(&request) >= 0)					\
						{														\
							ext_string query_str = "";							\
							handle_request(&request, query_str);				\
							map< ext_string, ext_string > query_map;			\
							vector<ext_string> querys = query_str.split('&');	\
							vector<ext_string>::iterator it;					\
							for(it = querys.begin(); it != querys.end(); it++)	\
							{													\
								vector<ext_string> element = it->split('=');	\
								if(element.size() > 1)							\
								{												\
									ext_string value = element[1];				\
									int i = 2;									\
									int n_size = element.size();				\
									while(i < n_size)							\
									{											\
										value += "=";							\
										value += element[i];					\
										i++;									\
									}											\
									query_map.insert(pair<ext_string,			\
										ext_string>(element[0], value));		\
								}												\
							}


#define _FCGI_END_		FCGX_Finish_r(&request);								\
						}


extern char* UrlDecode(const char* url)
{
	int n_len = 0;
	if(NULL == url || (n_len = strlen(url)) <= 0) return NULL;
	
	char* ret = new char[n_len + 1];
	memset(ret, '\0', n_len + 1);
	
	char tmp[3] = {0};
	char* prt = ret;
	const char* pus = url;
	const char* pue = url + n_len;
	
	while(pus <= pue)
	{
		if('%' == pus[0] && (memcpy(tmp, pus + 1, 2), 
			*prt = strtol(tmp, NULL, 16), 0 != *prt))
		{
			pus += 3;
		}
		else { *prt = *pus; pus++; }
		prt++;
	}
	
	return ret;
}

