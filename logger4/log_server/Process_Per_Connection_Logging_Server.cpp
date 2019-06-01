
#include "stdafx.h" 
#include "Process_Per_Connection_Logging_Server.h" 
#include "Logging_Process.h" 
#include "Logging_Handler.h" 

int Process_Per_Connection_Logging_Server::run(int argc, char *argv[])
{
    strncpy(prog_name_, argv[0], MAXPATHLEN); 
    prog_name_[MAXPATHLEN] = 0; 
    if(argc == 3)
        return run_worker(argc, argv); 
    else 
        return run_master(argc, argv); 
}

int Process_Per_Connection_Logging_Server::run_master(int argc, char *argv[])
{
    u_short logger_port = 0; 
    
    if(argc == 2)
        logger_port = atoi(argv[1]); 
    
    if(open(logger_port) == -1)
        return -1; 
    
    for(;;)
        if(handle_connections() == -1)
            return -1; 
        
    return 0;
}

int Process_Per_Connection_Logging_Server::run_worker(int argc, char *argv[])
{
    ACE_HANDLE socket_handle = 
        ACE_reinterpret_cast(ACE_HANDLE, atoi(argv[2])); 

    ACE_SOCK_Stream logging_peer(socket_handle); 
    handle_data(&logging_peer); 
    logging_peer.close(); 
    return 0; 
}


int Process_Per_Connection_Logging_Server::handle_connections()
{
    ACE_SOCK_Stream logging_peer; 
    if(acceptor().accept(logging_peer) == -1)
        return -1; 

    ACE_Process_Options options; 
    Logging_Process *logger = new Logging_Process(prog_name_, logging_peer); 
    pid_t pid = ACE_Process_Manager::instance()->spawn(logger, options); 
    if(pid == 0)
    {
        acceptor().close(); 
        handle_data(&logging_peer); 
        delete logger; 
        ACE_OS::exit(0); 
    }

    logging_peer.close(); 
    if(pid == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "spawn()"), -1); 

    return ACE_Process_Manager::instance()->wait(0, ACE_Time_Value::zero); 
}


int Process_Per_Connection_Logging_Server::handle_data(ACE_SOCK_Stream *logging_peer) 
{
    logging_peer->disable(ACE_NONBLOCK); 

    ACE_FILE_IO log_file; 
    make_log_file(log_file, logging_peer); 

    Logging_Handler logging_handler(log_file, *logging_peer); 
    while(logging_handler.log_record() != -1)
        continue; 

    log_file.close(); 
    return 0; 
}


