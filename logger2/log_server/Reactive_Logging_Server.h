#ifndef __REACTIVE_LOGGING_SERVER_H__
#define __REACTIVE_LOGGING_SERVER_H__

#include "ace/Handle_Set.h" 
#include "Iterative_Logging_Server.h" 


class Reactive_Logging_Server : public Iteractive_Logging_Server
{
public:
    virtual int open(u_short logger_port = 0); 
    virtual int wait_for_multiple_events(); 
    virtual int handle_connections(); 
    virtual int handle_data(ACE_SOCK_Stream* = 0); 

private:
    ACE_Handle_Set active_handles_; 
    ACE_Handle_Set master_handle_set_; 
}; 

#endif 