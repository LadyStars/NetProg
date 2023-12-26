#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define port 7
#define address "172.16.40.1"
#define bufsize 512

int main(int argc, char **argv)
{
    sockaddr_in *caddr = new sockaddr_in;
    caddr->sin_family = AF_INET;
    caddr->sin_port = 0;
    caddr->sin_addr.s_addr = 0;

    sockaddr_in *saddr = new sockaddr_in;
    saddr->sin_family = AF_INET;
    saddr->sin_port = htons(port);
    saddr->sin_addr.s_addr = inet_addr(address);

    char *buf = new char[bufsize];
    string str = "Муха села на варенье";
    int msglen = str.length();
    size_t length = str.copy(buf, msglen);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "ERRRROORR open socket";
    }

    int rc = bind(sockfd, (const sockaddr *) caddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(sockfd);
        cerr << "ERRRROORR bind socket with local address";
    }

    rc = connect(sockfd, (const sockaddr *) saddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(sockfd);
        cerr << "ERRRROORR connect socket with remote server";
    }

    rc = send(sockfd, buf, msglen, 0);
    if (rc == -1) {
        close(sockfd);
        cerr << "ERRRROORR send message";
    }
    cout << "Send: " << buf << endl;

    rc = recv(sockfd, buf, bufsize, 0);
    if (rc == -1) {
        close(sockfd);
        cerr << "ERRRROORR receive answer";
    }
    buf[rc] = '\0';
    cout << "Receive: " << buf << endl;

    close(sockfd);

    delete caddr;
    delete saddr;
    delete[] buf;
    return 0;
}