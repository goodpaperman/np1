// mblk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ace/OS.h" 
#include "ace/ACE.h" 
#include "ace/Message_Block.h" 

#define BUFSIZE 1
int main(int argc, char* argv[])
{
    ACE_Message_Block *head = new ACE_Message_Block(BUFSIZE); 
    ACE_Message_Block *mblk = head; 
    for(;;) { 
        ssize_t nbytes = ACE::read_n(ACE_STDIN, 
            mblk->wr_ptr(), 
            mblk->size()); 

        if(nbytes <= 0)
            break; 

        mblk->wr_ptr(nbytes); 
        mblk->cont(new ACE_Message_Block(BUFSIZE)); 
        mblk = mblk->cont(); 
    }

    //for(mblk = head; mblk != 0; mblk = mblk->cont())
    //  ACE::write_n(ACE_STDOUT, mblk->rd_ptr(), mblk->length()); 

    ACE::write_n(ACE_STDOUT, head); 
    head->release(); 
	return 0;
}
