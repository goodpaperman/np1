// http_srv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ace/Auto_Ptr.h" 
#include "ace/INET_Addr.h" 
#include "ace/SOCK_Acceptor.h" 
#include "ace/SOCK_Stream.h" 
#include "ace/Mem_Map.h" 

int main(int argc, char* argv[])
{
    ACE_INET_Addr server_addr; 
    ACE_SOCK_Acceptor acceptor; 
    ACE_SOCK_Stream peer; 

    if(server_addr.set(80) == -1) 
        return 1; 

    if(acceptor.open(server_addr) == -1)
        return 1; 

    for(;;) {
        if(acceptor.accept(peer) == -1)
            return 1; 

        ACE::write_n(ACE_STDOUT, "accept a new connection\n", 25);
        peer.disable(ACE_NONBLOCK); 
        char *pathname = "e:\\codes\\ace_wrappers\\ace\\SOCK_Stream.h"; 
        ACE_Mem_Map mapped_file(pathname); 
        if(peer.send_n(mapped_file.addr(), 
            mapped_file.size()) == -1)
            return 1; 

        ACE::write_n(ACE_STDOUT, "transfer a file\n", 17);
        peer.close(); 
    }

    return acceptor.close() == -1 ? 1 : 0;
}
