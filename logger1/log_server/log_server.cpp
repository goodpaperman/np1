// log_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ace/Log_Msg.h" 
#include "Iterative_Logging_Server.h" 

int main(int argc, char* argv[])
{
    Iterative_Logging_Server server; 
    if(server.run(argc, argv) == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "server.run()"), 1); 

	return 0;
}
