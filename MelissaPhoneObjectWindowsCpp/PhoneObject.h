#include<iostream>
#include <string>

#include "mdPhone.h"
#include "DataContainer.h"

using namespace std;

#ifndef PHONEOBJECT_H
#define PHONEOBJECT_H

class PhoneObject
{
public:
	// Path to Phone Object data files (.dat, etc)
	string dataFilePath;

	// Create instance of Melissa Phone Object
	mdPhone* mdPhoneObj = new mdPhone;

	PhoneObject(string license, string dataPath);

	// This will call the lookup function to process the input phone as well as generate the result codes
	void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
