#include<iostream>

using namespace std;

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

/**
 * Data holder for a single record: carries the input phone number in and the result
 * codes out.
 */
class DataContainer
{
public:
	// Input: the phone number to process.
	char Phone[20] = "";

	// Input: optional ZIP code passed to Lookup to help disambiguate the number.
	// This sample never populates it, so Lookup receives an empty string.
	char ZipCode[15] = "";

	// Output: comma-separated result codes from GetResults().
	string ResultCodes;

	DataContainer() {};
};

#endif