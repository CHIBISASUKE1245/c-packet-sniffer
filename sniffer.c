#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/ethernet.h> 
#include <netinet/ip.h>
#include <netinet/tcp.h>  
#include <netinet/udp.h> 

int main() {
    int raw_socket;
    unsigned char buffer[65536]; 

    raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (raw_socket < 0) {
        perror("Socket creation failed.");
        return 1;
    }

    printf("Listening for TCP/UDP packets...\n");

    while (1) {
        int data_size = recvfrom(raw_socket, buffer, sizeof(buffer), 0, NULL, NULL);
        if (data_size < 0) continue;

        struct ether_header *eth = (struct ether_header *)buffer;

        
        if (ntohs(eth->ether_type) == 0x0800) {
            
            struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ether_header));
            
            char src_ip[INET_ADDRSTRLEN];
            char dest_ip[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, &(ip->saddr), src_ip, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &(ip->daddr), dest_ip, INET_ADDRSTRLEN);

            printf("Src IP: %-15s | Dest IP: %-15s | ", src_ip, dest_ip);

            
            int ip_header_len = ip->ihl * 4;

           
            if (ip->protocol == IPPROTO_TCP) {
                struct tcphdr *tcp = (struct tcphdr *)(buffer + sizeof(struct ether_header) + ip_header_len);
                printf("TCP | Src Port: %-5d | Dest Port: %-5d\n", ntohs(tcp->source), ntohs(tcp->dest));
            } 
            else if (ip->protocol == IPPROTO_UDP) {
                struct udphdr *udp = (struct udphdr *)(buffer + sizeof(struct ether_header) + ip_header_len);
                printf("UDP | Src Port: %-5d | Dest Port: %-5d\n", ntohs(udp->source), ntohs(udp->dest));
            } 
            else {
                printf("Other Protocol\n");
            }
        }
    }

    close(raw_socket);
    return 0;
}
