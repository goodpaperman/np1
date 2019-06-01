#ifndef __PROCESS_PER_CONNECTION_LOGGING_SERVER_H__
#define __PROCESS_PER_CONNECTION_LOGGING_SERVER_H__

//#include "ace/ACE.h" 
//#include "ace/Handle_Set.h" 
//#include "ace/Hash_Map_Manager.h" 
//#include "ace/Synch.h" 
//#include "Logging_Server.h" 
//#include "Logging_Handler.h" 

//#include "ace/Log_Record.h" 
#include "ace/Process.h" 
#include "ace/Process_Manager.h" 
#include "ace/Signal.h" 
#include "Logging_Server.h" 

class Process_Per_Connection_Logging_Server : public Logging_Server
{
public:
    virtual int run(int argc, char *argv[]); 
    //virtual int open(u_short logger_port = 0); 
    //virtual int wait_for_multiple_events(); 
    virtual int handle_connections(); 
    virtual int handle_data(ACE_SOCK_Stream* = 0); 

private:
    int run_master(int argc, char *argv[]); 
    int run_worker(int argc, char *argv[]); 

private:
    char prog_name_[MAXPATHLEN + 1]; 
}; 

#endif 