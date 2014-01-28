// MQTT Client Test C++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mosquitto.h"
#include "mosquittopp.h"
#include "myMosq.h"
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <iostream>
#include <string>

#define SIGNAL_LEN 34

struct mosquitto *m;

void test1();
void test2();

int _tmain(int argc, _TCHAR* argv[])
{
	
	test1();
	//test2();

	return 0;
}

void test1()
{
	char const* id = "1234";
	char const* topic = "hello/world";
	char const* host = "192.168.222.235";
	int port = 1883;
	char const* message = "HR: 137";
	myMosq MQTT(id, topic, host, port);

	//new crap
	std::string input = "y";

	while (input != "q")
	{
		std::cout << "Enter message:\n";
		std::getline(std::cin, input);
		char* message = new char[input.length() + 1];
		memcpy(message, input.c_str(), input.size() + 1);
		MQTT.send_message(message);
		delete message;
	}

	/*
	char buffer[10];
	int count = 1;

	while (true)
	{
		char* testMessage;
		_itoa_s(count, buffer, 10, 10);
		MQTT.send_message(buffer);
		count++;
		Sleep(5000);
	}
	*/

	//message 1
	//MQTT.send_message(message);
}

void test2()
{
	mosquitto_lib_init();

	m = mosquitto_new("1234", false, NULL);
	assert(m != 0);

	//Setup connection
	//if (mosquitto_username_pw_set(m, 0, 0) == MOSQ_ERR_SUCCESS)
	//{
	//	printf("check 1\n");
	//}

	//if (mosquitto_will_set(m, 0, 0, 0, 0, 0) == MOSQ_ERR_SUCCESS)
	//{
	//	printf("check 2\n");
	//}

	if (mosquitto_connect(m, "192.168.222.235", 1883, 15) == MOSQ_ERR_SUCCESS)
	{
		printf("check 3\n");
	}

	printf("connected\n");

	char strbuf[256];

	int count = 1;
	while (true)
	{
		sprintf_s(strbuf, "%04d", count);
		count++;
		printf("sending %s  ", strbuf);
		if (mosquitto_publish(m, 0, "hello/world", strlen(strbuf) + 1, strbuf, 2, true) == MOSQ_ERR_SUCCESS) {
			printf("OK\n");
		}
		else {
			printf("fail\n");
		}
		Sleep(5000);
	}

	mosquitto_lib_cleanup();
}

