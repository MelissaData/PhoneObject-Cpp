#include<iostream>
#include <string>

#include "mdPhone.h"
#include "DataContainer.h"

using namespace std;

#ifndef PHONEOBJECT_H
#define PHONEOBJECT_H

/**
 * Wrapper that owns a single Melissa Phone Object instance and encapsulates the two
 * things every Melissa object needs: one-time setup (license + data files) and the
 * per-record processing sequence. Reuse one instance across many numbers; do NOT
 * re-initialize per number.
 */
class PhoneObject
{
public:
	// Path to the Phone Object data files.
	string dataFilePath;

	// The underlying Melissa Phone Object instance.
	mdPhone* mdPhoneObj = new mdPhone;

	/**
	 * Performs the mandatory one-time setup, in this required order:
	 *   1. SetLicenseString - authorize the object.
	 *   2. Initialize       - point the object at the data files and load them.
	 *
	 * @param license  The Melissa license string used to authorize the object.
	 * @param dataPath Path to the folder containing the Phone Object data files.
	 */
	PhoneObject(string license, string dataPath);

	/**
	 * Runs the full Phone Object processing sequence for one phone number and captures
	 * its result codes. This is the canonical per-record call pattern to copy into your
	 * own application:
	 *   Lookup -> GetResults
	 *
	 * @param data The record to process. Its Phone is read as input, and ResultCodes is
	 *             populated with this run's result codes.
	 */
	void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
