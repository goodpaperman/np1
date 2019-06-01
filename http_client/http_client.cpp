// http_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ace/INET_Addr.h" 
#include "ace/SOCK_Connector.h" 
#include "ace/SOCK_Stream.h" 


int main(int argc, char* argv[])
{
    const char *pathname = 
        argc > 1 ? argv[1] : "index.html"; 
    const char *server_hostname = 
        argc > 2 ? argv[2] : "localhost"; 

    ACE_SOCK_Connector connector; 
    ACE_SOCK_Stream peer; 
    ACE_INET_Addr peer_addr;
    ACE_Time_Value timeout(10); 

    if(peer_addr.set(80, server_hostname) == -1)
        return 1; 
    else if(connector.connect(peer, peer_addr, &timeout) == -1)
    {
        ACE::write_n(ACE_STDOUT, "connect failed\n", 16); 
        return 1; 
    }

    char buf[1024] = { 0 }; 
    iovec iov[3] = { 0 }; 
    iov[0].iov_base = "GET "; 
    iov[0].iov_len = 4; 
    iov[1].iov_base = (char*)pathname; 
    iov[1].iov_len = strlen(pathname); 
    iov[2].iov_base = " HTTP/1.0\r\n\r\n"; 
    iov[2].iov_len = 13; 

    //if(peer.sendv_n(iov, 3) == -1)
    //    return 1; 

    for(ssize_t n; (n = peer.recv(buf, sizeof buf)) > 0; )
        ACE::write_n(ACE_STDOUT, buf, n);

    return peer.close() == -1 ? 1 : 0;
}
