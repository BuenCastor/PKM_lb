#include "single_thread_udp_receiver.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

const std::string currentDateTime();

bool process_receiv_data(SOCKET socket) {
	sockaddr_in incom_addr;
	memset(&incom_addr, 0, sizeof(incom_addr));
	socklen_t len = sizeof(incom_addr);
	char buffer[256] = "";
	int rec_cn = recvfrom(socket, buffer, sizeof(buffer), 0, (sockaddr*)&incom_addr, &len);

    std::cout << "current time " << currentDateTime() << std::endl;
    getchar();  // wait for keyboard input

	if (rec_cn <= 0) {
		error_msg("Can't receive data");		
	}

	printf("[From: %s] Received data [%s]\n", inet_ntoa(incom_addr.sin_addr), buffer);

	return true;
}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
