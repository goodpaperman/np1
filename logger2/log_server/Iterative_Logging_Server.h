
#ifndef __ITERATIVE_LOGGING_SERVER_H__
#define __ITERATIVE_LOGGING_SERVER_H__

#include "ace/FILE_IO.h" 
#include "ace/INET_Addr.h" 
#include "ace/Log_Msg.h" 

#include "Logging_Server.h" 
#include "Logging_Handler.h" 

class Iteractive_Logging_Server : public Logging_Server
{
public:
    Iteractive_Logging_Server() : logging_handler_(log_file_) {}
    virtual ~Iteractive_Logging_Server() { log_file_.close(); } 
    Logging_Handler& logging_handler() { return logging_handler_; } 

protected:
    virtual int open(u_short logger_port = 0); 
    virtual int handle_connections(); 
    virtual int handle_data(ACE_SOCK_Stream* = 0); 

private:
    ACE_FILE_IO log_file_; 
    Logging_Handler logging_handler_; 
}; 

#endif 