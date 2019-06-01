// log_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ace/Log_Msg.h" 
#include "Process_Per_Connection_Logging_Server.h" 

static void sigterm_handler(int signum) { }

int main(int argc, char* argv[])
{
    ACE_Sig_Action sa(sigterm_handler, SIGTERM); 

    Process_Per_Connection_Logging_Server server; 
    if(server.run(argc, argv) == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "server.run()"), 1); 

    return ACE_Process_Manager::instance()->wait();
}
