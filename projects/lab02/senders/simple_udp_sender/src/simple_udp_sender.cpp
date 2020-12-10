#include "simple_udp_sender.h"

void exit_handler();

SOCKET client_socket;
int main(int argc, char* argv[])
{
	atexit(common_exit_handler);
	atexit(exit_handler);

	short port;
	char host[128] = "";
	bool parse_cmd_result = parse_cmd(argc, argv, host, &port);

	if (!parse_cmd_result || !host || !strlen(host))
	{
		printf("Invalid host or port. Usage %s -h host -p port\n", argv[0]);
		return -1;
	}

    common_init_handler();

	client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (client_socket <= 0) {
		error_msg("Can't create socket");
		return -1;
	}

	struct sockaddr_in server_addr;
	init_inet_address(&server_addr, host, port);

	
	char msg[256] = "";
	int sc = sendto(client_socket, msg, sizeof(msg), 0, (sockaddr*)&server_addr, sizeof(server_addr));
	if (sc <= 0) {
		char err_msg[128] = "";
		sprintf(err_msg, "Can't send data to the %s:%d", host, port);
		error_msg(err_msg);
		return -1;
	}

	return 0;
}

void exit_handler()
{
	close_socket(client_socket);
}
