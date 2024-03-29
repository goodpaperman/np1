// Logging_Process.cpp: implementation of the Logging_Process class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Logging_Process.h"
#include "ace/ACE.h" 
#include "ace/Log_Msg.h" 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Logging_Process::Logging_Process(const char *prog_name, 
                                 const ACE_SOCK_Stream &logging_peer)
                                 : logging_peer_(logging_peer.get_handle())
{
    strcpy(prog_name_, prog_name); 
}


int Logging_Process::prepare(ACE_Process_Options &options)
{
    if(options.pass_handle(logging_peer_.get_handle()) == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "pass_handle()"), -1); 

    options.command_line("%s", prog_name_); 
    options.avoid_zombies(1); 
    options.creation_flags(ACE_Process_Options::NO_EXEC); 
    return 0; 
}