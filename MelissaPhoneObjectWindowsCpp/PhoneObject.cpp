#include "PhoneObject.h"

PhoneObject::PhoneObject(string license, string dataPath)
{
	// Set license string and set path to data files
	mdPhoneObj->SetLicenseString(license.c_str());
	dataFilePath = dataPath;

	// Point the object at the data files and load them. The returned ProgramStatus reports whether initialization succeeded.
	// If you see a different date than expected, check your license string and either download the new data files
	// or use the Melissa Updater program to update your data files.
	mdPhone::ProgramStatus pStatus = mdPhoneObj->Initialize(dataFilePath.c_str());

	// If an issue occurred, please investigate the common causes.
	// Common causes: an invalid/expired license, or missing/wrong-path data files.
	if (pStatus != mdPhone::ProgramStatus::ErrorNone)
	{
		cout << "Failed to Initialize Object." << endl;
		cout << pStatus << endl;
		return;
	}

	// Diagnostic information, handy for confirming the object loaded the data you expect:

	// Build date of the data files
	cout << "                DataBase Date: " + string(mdPhoneObj->GetDatabaseDate()) << endl;

	// When the license stops working
	cout << "              Expiration Date: " + string(mdPhoneObj->GetLicenseExpirationDate()) << endl;

	/**
	 * This number should match with the file properties of the Melissa Object binary file.
	 * If TEST appears with the build number, there may be a license key issue.
	 */
	cout << "               Object Version: " + string(mdPhoneObj->GetBuildNumber()) << endl;
}

// This will call the lookup function to process the input phone as well as generate the result codes
void PhoneObject::ExecuteObjectAndResultCodes(DataContainer& data)
{
	// Validate the number and append its data
	mdPhoneObj->Lookup(data.Phone, data.ZipCode);

	// Other Phone Object operations, available if you need them:
	//mdPhoneObj->CorrectAreaCode(data.Phone, data.ZipCode);
	//mdPhoneObj->ComputeDistance(0.0, 0.0, 0.0, 0.0);
	//mdPhoneObj->ComputeBearing(0.0, 0.0, 0.0, 0.0);

	// Collect the result codes for this run
	// ResultsCodes explain any issues Phone Object has with the object.
	// List of result codes for Phone Object
	// https://docs.melissa.com/on-premise-api/phone-object/result-codes.html
	data.ResultCodes = mdPhoneObj->GetResults();
}
