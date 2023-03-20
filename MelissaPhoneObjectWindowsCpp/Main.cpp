#include <iostream>
#include <string>
#include <cstdlib>
#include <list>

#include "mdPhone.h"
#include "PhoneObject.h"
#include "DataContainer.h"

using namespace std;

// function declarations
void ParseArguments(string& license, string& testPhone, string& dataPath, int argc, char** argv);
void RunAsConsole(string license, string testPhone, string dataPath);
list<string> SplitResultCodes(string s, string delimiter);

int main(int argc, char* argv[])
{
	// Variables
	string license = "";
	string testPhone = "";
	string dataPath = "";

	ParseArguments(license, testPhone, dataPath, argc, argv);
	RunAsConsole(license, testPhone, dataPath);

	return 0;
}

void ParseArguments(string& license, string& testPhone, string& dataPath, int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (string(argv[i]) == "--license" || string(argv[i]) == "-l")
		{
			if (argv[i + 1] != NULL)
			{
				license = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--phone" || string(argv[i]) == "-p")
		{
			if (argv[i + 1] != NULL)
			{
				testPhone = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--dataPath" || string(argv[i]) == "-d")
		{
			if (argv[i + 1] != NULL)
			{
				dataPath = argv[i + 1];
			}
		}
	}
}

void RunAsConsole(string license, string testPhone, string dataPath)
{
	cout << "\n============ WELCOME TO MELISSA PHONE OBJECT WINDOWS C++ ===========\n" << endl;

	PhoneObject* phoneObject = new PhoneObject(license, dataPath);

	bool shouldContinueRunning = true;

	while (shouldContinueRunning)
	{
		DataContainer dataContainer = DataContainer();

		if (testPhone.empty())
		{
			cout << "\nFill in each value to see the Phone Object results" << endl;
			cout << "Phone: ";

			string input;
			getline(cin, input);

			strcpy_s(dataContainer.Phone, input.c_str());
		}
		else
		{
			strcpy_s(dataContainer.Phone, testPhone.c_str());
		}

		// Print user input
		cout << "\n============================== INPUTS ==============================\n" << endl;
		cout << "\t                Phone: " + string(dataContainer.Phone)                  << endl;

		// Execute Phone Object
		phoneObject->ExecuteObjectAndResultCodes(dataContainer);

		// Print output
		cout << "\n============================== OUTPUT ==============================\n"      << endl;
		cout << "\n\tPhone Object Information:"                                                 << endl;
		cout << "\t            Area Code: " + string(phoneObject->mdPhoneObj->GetAreaCode())		<< endl;
		cout << "\t               Prefix: " + string(phoneObject->mdPhoneObj->GetPrefix())			<< endl;
		cout << "\t               Suffix: " + string(phoneObject->mdPhoneObj->GetSuffix())			<< endl;
		cout << "\t                 City: " + string(phoneObject->mdPhoneObj->GetCity())				<< endl;
		cout << "\t                State: " + string(phoneObject->mdPhoneObj->GetState())			  << endl;
		cout << "\t             Latitude: " + string(phoneObject->mdPhoneObj->GetLatitude())		<< endl;
		cout << "\t            Longitude: " + string(phoneObject->mdPhoneObj->GetLongitude())	  << endl;
		cout << "\t            Time Zone: " + string(phoneObject->mdPhoneObj->GetTimeZone())		<< endl;
		cout << "\t         Result Codes: " + dataContainer.ResultCodes												  << endl;

		//cout << "\t New Area Code: " + string(phoneObject.mdPhoneObj->GetNewAreaCode())		<< endl;
		//cout << "\t     Extension: " + string(phoneObject.mdPhoneObj->GetExtension())			<< endl;
		//cout << "\t    CountyFips: " + string(phoneObject.mdPhoneObj->GetCountyFips())		<< endl;
		//cout << "\t    CountyName: " + string(phoneObject.mdPhoneObj->GetCountyName())		<< endl;
		//cout << "\t           Msa: " + string(phoneObject.mdPhoneObj->GetMsa())						<< endl;
		//cout << "\t          Pmsa: " + string(phoneObject.mdPhoneObj->GetPmsa())					<< endl;
		//cout << "\tTime Zone Code: " + string(phoneObject.mdPhoneObj->GetTimeZoneCode())	<< endl;
		//cout << "\t  Country Code: " + string(phoneObject.mdPhoneObj->GetCountryCode())		<< endl;
		//cout << "\t      Distance: " + string(phoneObject.mdPhoneObj->GetDistance())			<< endl;

		list<string> rs = SplitResultCodes(dataContainer.ResultCodes, ",");
		list<string>::iterator it;

		for (it = rs.begin(); it != rs.end(); it++)
		{
			printf("        %s: %s", it->c_str(), phoneObject->mdPhoneObj->GetResultCodeDescription(it->c_str(), phoneObject->mdPhoneObj->ResultCodeDescriptionLong));
			cout << endl;
		}

		bool isValid = false;
		if (!testPhone.empty()) 
		{
			isValid = true;
			shouldContinueRunning = false;
		}
		while (!isValid)
		{
			string testAnotherResponse;

			cout << "\nTest another phone? (Y/N)" << endl;
			getline(cin, testAnotherResponse);

			if (!testAnotherResponse.empty())
			{
				if (testAnotherResponse == "y" || testAnotherResponse == "Y")
				{
					isValid = true;
				}
				else if (testAnotherResponse == "n" || testAnotherResponse == "N")
				{
					isValid = true;
					shouldContinueRunning = false;
				}
				else
				{
					cout << "Invalid Response, please respond 'Y' or 'N'" << endl;
				}
			}
		}
	}
	cout << "\n=============== THANK YOU FOR USING MELISSA C++ OBJECT =============\n" << endl;
}

/// <summary>
/// This function splits the resultCodes based on a delimiter
/// </summary>
/// <param name="s">the resultCode string</param>
/// <param name="delimiter"the delimiter string></param>
/// <returns></returns>
list<string> SplitResultCodes(string s, string delimiter) {
	list<string> resultCodes;

	size_t pos = 0;
	string token;

	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		resultCodes.push_back(token);
		s.erase(0, pos + delimiter.length());
	}

	// push back the last resultCode
	resultCodes.push_back(s);

	return resultCodes;
}

	/*
	cout << bar;

	char phone[20], zip[15];
	const char* results;

	double      lat1;             // latitude of first point
	double      lon1;             // longitude of first point
	float distance, bearing;

	mdPhone* ph = new mdPhone;

	if (!ph->SetLicenseString(dLICENSE)) {
		cout << "Error setting License to : " << dLICENSE << endl;
		cout << "Please contact a sales representative at 1-800-800-6245 x3 for a valid license string" << endl;
		return 1;
	}

	if (ph->Initialize(dFILELOC) != mdPhone::ErrorNone) {
		cout << "Error Initializing mdName: " << ph->GetInitializeErrorString() << endl;
		return 1;
	}
	cout << "     MELISSA DATA PHONE OBJECT C++ EXAMPLE  " << endl;
	cout << "        Object Initialized: " << ph->GetInitializeErrorString() << endl;
	cout << "              Build Number: " << ph->GetBuildNumber() << endl;
	cout << "             Database Date: " << ph->GetDatabaseDate() << endl;
	cout << "   License Expiration Date: " << ph->GetLicenseExpirationDate() << endl;
	cout << bar;

	/***************************************************************
*  Remember, without a valid license, you can only process    *
*  Nevada numbers - for example:                              *
		*      PhoneNumber: 702-896-5154                              *
*	   ZipCode: = 89119                                        *
		***************************************************************/

		/*
		cout << " Input Phone (ex: 702-896-5154): ";        cin.getline(phone, sizeof phone);
		cout << "     Input Zip Code (ex: 89119): ";        cin.getline(zip, sizeof zip);

		ph->Lookup(phone, zip);

		cout << endl << "Results..." << endl;
		results = ph->GetResults();
		if ((strstr(results, "PS01") != 0) || (strstr(results, "PS02") != 0))
		{
			if (strstr(results, "PS01") != 0)
				cout << "Phone validated to 10 digits" << endl;
			else if (strstr(results, "PS02") != 0)
				cout << "Phone validated to 7 digits" << endl;

			if (strstr(results, "PS07") != 0)
				cout << "Exchange Type: Cellular" << endl;
			if (strstr(results, "PS08") != 0)
				cout << "Exchange Type: Land Line" << endl;
			else if (strstr(results, "PS09") != 0)
				cout << "Exchange Type: Voip" << endl;

			if (strstr(results, "PS10") != 0)
				cout << "Phone Type: Residential" << endl;
			if (strstr(results, "PS11") != 0)
				cout << "Phone Type: Business" << endl;
			if (strstr(results, "PS12") != 0)
				cout << "Phone Type: Small/Home Office" << endl;

			if (strstr(results, "PS06") != 0)
				cout << "New Area Code Furnished" << endl;

			cout << endl;
			cout << "AreaCode    : " << ph->GetAreaCode() << endl;
			cout << "NewAreaCode : " << ph->GetNewAreaCode() << endl;
			cout << "Prefix      : " << ph->GetPrefix() << endl;
			cout << "Suffix      : " << ph->GetSuffix() << endl;
			cout << "Extension   : " << ph->GetExtension() << endl;
			cout << endl;

			cout << "City        : " << ph->GetCity() << endl;
			cout << "State       : " << ph->GetState() << endl;
			cout << "CountyFips  : " << ph->GetCountyFips() << endl;
			cout << "CountyName  : " << ph->GetCountyName() << endl;
			cout << "Msa         : " << ph->GetMsa() << endl;
			cout << "Pmsa        : " << ph->GetPmsa() << endl;
			cout << "TimeZone    : " << ph->GetTimeZone() << endl;
			cout << "TimeZoneCode: " << ph->GetTimeZoneCode() << endl;
			cout << "CountryCode : " << ph->GetCountryCode() << endl;
			cout << "Latitude    : " << ph->GetLatitude() << endl;
			cout << "Longitude   : " << ph->GetLongitude() << endl;
			cout << "Distance    : " << ph->GetDistance() << endl;
			cout << endl;

			cout << "==============================================" << endl;
			cout << "        Distance and Bearing Example" << endl;
			cout << " Lat / Long of US Capital: 38.889722  -77.0075 " << endl;
			cout << "==============================================" << endl;
			lat1 = atof(ph->GetLatitude());
			lon1 = atof(ph->GetLongitude());
			distance = ph->ComputeDistance(lat1, lon1, 38.889722, -77.0075);
			bearing = ph->ComputeBearing(lat1, lon1, 38.889722, -77.0075);
			cout << " Distance: " << distance << "miles" << endl;
			cout << "  Bearing: " << bearing << "degrees" << endl;
			cout << endl;

			ph->CorrectAreaCode(phone, zip);
			results = ph->GetResults();
			if (strstr(results, "PS03") != 0)
			{
				cout << "===============================" << endl;
				cout << "  Corrected Area Code Results" << endl;
				cout << "===============================" << endl;
				cout << "    Area Code: " << ph->GetAreaCode() << endl;
				cout << "New Area Code: " << ph->GetNewAreaCode() << endl;
				cout << "       Prefix: " << ph->GetPrefix() << endl;
				cout << "       Suffix: " << ph->GetSuffix() << endl;
				cout << "    Extension: " << ph->GetExtension() << endl;
			}

		}
		else if ((strstr(results, "PS04") != 0) || (strstr(results, "PS05") != 0)) {
			// program could not process the number
			if (strstr(results, "PS04") != 0)
				cout << "PS04: Phone number is outside the Demo range (Nevada)" << endl;
			if (strstr(results, "PS05") != 0)
				cout << "PS05: Expired Database The database has expired. Contact Melissa Data" << endl;

		}
		else if (strstr(results, "PE") != 0) {
			//there was an error validating the number
			if (strstr(results, "PE01") != 0)
				cout << "PE01: Bad Area Code" << endl;
			if (strstr(results, "PE02") != 0)
				cout << "PE02: Blank Phone Number" << endl;
			if (strstr(results, "PE03") != 0)
				cout << "PE03: Too few or too many digits" << endl;
			if (strstr(results, "PE04") != 0)
				cout << "PE04: Multiple Match" << endl;
			if (strstr(results, "PE05") != 0)
				cout << "PE05: Bad prefix" << endl;
			if (strstr(results, "PE06") != 0)
				cout << "PE06: Bad Zip Code" << endl;
		}

		// clean up after ourselves
		delete ph;
		ph = NULL;
		*/
