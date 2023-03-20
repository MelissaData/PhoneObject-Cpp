#include<iostream>

using namespace std;

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

class DataContainer
{
public:
	char Phone[20] = "";
	char ZipCode[15] = "";
	string ResultCodes;

	DataContainer() {};
};

#endif