
#include "common_fcgi.h"

int main(int argc, char* argv[])
{
    _FCGI_START_
    
    // implement here.
	ext_string content = query_map["content"];
	ext_string ajax = query_map["ajax"];
	
	cm_printf("{ result: ");
	
	cm_printf(" }");
    
    _FCGI_END_
    
    return 0;
}

