#include "RoboCatPCH.h"

std::unique_ptr<ConnectionDetails> ConnectionDetails::sInstance;

void ConnectionDetails::StaticInit()
{
	ConnectionDetails* cd = new ConnectionDetails();
	cd->Load();
	sInstance.reset(cd);
}

ConnectionDetails::ConnectionDetails()
{
}

void ConnectionDetails::Load()
{
	uint16_t port = 50001;
	m_clientPort = port;
	m_serverPort = port;

	string line;
	std::ifstream nameFile("name.txt");
	if (nameFile.good())
	{
		getline(nameFile, line);
		m_clientName = line;
	}
	nameFile.close();

	std::ifstream ipFile("ip.txt");
	if (ipFile.good())
	{
		getline(ipFile, line);
		m_clientIP = line;
	}
	ipFile.close();
}

string ConnectionDetails::GetClientName()
{
	return m_clientName;
}

string ConnectionDetails::GetClientDestination()
{
	return m_clientIP + ":" + std::to_string(m_clientPort);
}

uint16_t ConnectionDetails::GetServerPort()
{
	return m_serverPort;
}
