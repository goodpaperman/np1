// Logging_Process.h: interface for the Logging_Process class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGGING_PROCESS_H__07B5955F_A8BA_4AF5_AABE_965819E0FE83__INCLUDED_)
#define AFX_LOGGING_PROCESS_H__07B5955F_A8BA_4AF5_AABE_965819E0FE83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ace/Process.h" 
#include "ace/SOCK_Stream.h" 

class Logging_Process : public ACE_Process  
{
public:
    Logging_Process(const char *prog_name, 
        const ACE_SOCK_Stream &logging_peer); 

    virtual int prepare(ACE_Process_Options &options); 
    virtual void unmanage() { delete this; } 

private:
	Logging_Process();

    char prog_name_[MAXPATHLEN+1]; 
    ACE_SOCK_Stream logging_peer_; 
};

#endif // !defined(AFX_LOGGING_PROCESS_H__07B5955F_A8BA_4AF5_AABE_965819E0FE83__INCLUDED_)
