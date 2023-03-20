#include "PhoneObject.h"

PhoneObject::PhoneObject(string license, string dataPath)
{
	// Set license string and set path to datafiles (.dat, etc)
	mdPhoneObj->SetLicenseString(license.c_str());
	dataFilePath = dataPath;

	// If you see a different date than expected, check your license string and either download the new data files or use the Melissa Updater program to update your data files.  
	mdPhone::ProgramStatus pStatus = mdPhoneObj->Initialize(dataFilePath.c_str());

	if (pStatus != mdPhone::ProgramStatus::ErrorNone)
	{
		cout << "Failed to Initialize Object." << endl;
		cout << pStatus << endl;
		return;
	}

	cout << "                DataBase Date: " + string(mdPhoneObj->GetDatabaseDate()) << endl;
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
	mdPhoneObj->Lookup(data.Phone, data.ZipCode);

	//mdPhoneObj->CorrectAreaCode(data.Phone, data.ZipCode);
	//mdPhoneObj->ComputeDistance(0.0, 0.0, 0.0, 0.0);
	//mdPhoneObj->ComputeBearing(0.0, 0.0, 0.0, 0.0);

	data.ResultCodes = mdPhoneObj->GetResults();

	// ResultsCodes explain any issues Phone Object has with the object.
	// List of result codes for Phone Object
	// https://wiki.melissadata.com/?title=Result_Code_Details#Phone_Object
}
