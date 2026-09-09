/**
 * @file Main.cpp
 * @brief Phone Object allows websites and custom applications to verify phone numbers down
 * to 7 and 10 digits, update area codes, and append data about the phone number.
 *
 * High-level flow of this sample:
 *   1. SETUP     - create an mdPhone instance, hand it the license string and the
 *                  path to the data files, then Initialize() (one time).
 *   2. INPUT     - feed a phone number in.
 *   3. PROCESS   - Lookup() validates the number and appends its data.
 *   4. READ      - pull the results back out with the Get* getters
 *                  (GetAreaCode, GetCity, GetState, GetTimeZone, ...).
 *   5. INTERPRET - GetResults() returns comma-separated result codes describing
 *                  what the object did/found; each code has a human description.
 *
 * The pieces of this sample map onto that flow:
 *   - main / ParseArguments / RunAsConsole : console harness (argument parsing + the interactive loop).
 *   - PhoneObject     : thin wrapper around mdPhone that owns setup + the call sequence.
 *   - DataContainer   : plain holder for one record's input and output.
 *
 * Where mdPhone comes from:
 *   There is no generated wrapper source for C++. mdPhone.h and
 *   mdEnums.h declare the API, mdPhone.lib is the import library the linker resolves
 *   against, and mdPhone.dll carries the implementation. The accompanying
 *   MelissaPhoneObjectWindowsCpp.ps1 script downloads all four on every run.
 *
 * Reference:
 *   Quickstart    : https://docs.melissa.com/on-premise-api/phone-object/phone-object-quickstart.html
 *   Release notes : https://releasenotes.melissa.com/on-premise-api/phone-object/
 *   Result codes  : https://docs.melissa.com/on-premise-api/phone-object/result-codes.html
 */

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

/**
 * Entry point. Reads the optional command-line arguments, then hands control to
 * RunAsConsole, which performs the actual Phone Object setup and processing.
 *
 * @param argc The count of command-line arguments.
 * @param argv The raw command-line arguments.
 */
int main(int argc, char* argv[])
{
	// Populated by ParseArguments below.
	string license = "";
	string testPhone = "";
	string dataPath = "";

	ParseArguments(license, testPhone, dataPath, argc, argv);
	RunAsConsole(license, testPhone, dataPath);

	return 0;
}

/**
 * Reads the supported command-line options into the reference parameters.
 *
 * Recognized flags (each followed by its value, e.g. "--phone 8002356766"):
 *   --license / -l   : the Melissa license string
 *   --phone / -p     : a phone number to test in one-shot mode
 *   --dataPath / -d  : path to the Phone Object data files
 *
 * @param license   Receives the Melissa license string.
 * @param testPhone Receives the phone number to test in one-shot mode.
 * @param dataPath  Receives the path to the Phone Object data files.
 * @param argc      The count of command-line arguments to parse.
 * @param argv      The raw command-line arguments to parse.
 */
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

/**
 * Sets up the Phone Object once, then drives the input -> process -> output cycle.
 *
 * In interactive mode (no --phone) it loops, asking for a new phone number each pass
 * until the user answers "N". In one-shot mode (--phone supplied) it runs a single
 * pass on testPhone and exits.
 *
 * @param license   The Melissa license string used to initialize the object.
 * @param testPhone A phone number to process in one-shot mode; if empty, the program prompts interactively.
 * @param dataPath  Path to the Phone Object data files.
 */
void RunAsConsole(string license, string testPhone, string dataPath)
{
	cout << "\n============ WELCOME TO MELISSA PHONE OBJECT WINDOWS C++ ===========\n" << endl;

	// Construct the wrapper. This is where the object is licensed, pointed at the
	// data files, and initialized (see the PhoneObject constructor below).
	PhoneObject* phoneObject = new PhoneObject(license, dataPath);

	bool shouldContinueRunning = true;

	while (shouldContinueRunning)
	{
		// Holder for this pass's input and result codes.
		DataContainer dataContainer = DataContainer();

		if (testPhone.empty())
		{
			// Interactive mode: prompt the user for a phone number.
			cout << "\nFill in each value to see the Phone Object results" << endl;
			cout << "Phone: ";

			string input;
			getline(cin, input);

			strcpy_s(dataContainer.Phone, input.c_str());
		}
		else
		{
			// One-shot mode: use the phone number passed on the command line.
			strcpy_s(dataContainer.Phone, testPhone.c_str());
		}

		// Print user input
		cout << "\n============================== INPUTS ==============================\n" << endl;
		cout << "\t                Phone: " + string(dataContainer.Phone)                  << endl;

		// Execute Phone Object
		// Runs the Lookup and stores the result codes on dataContainer.
		phoneObject->ExecuteObjectAndResultCodes(dataContainer);

		// Print output
		// Each Get* getter below returns one component the object produced for the most
		// recently processed phone number. These read directly from the mdPhone instance,
		// which still holds the results from the Execute call above.
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

		// Other data the Phone Object can return - uncomment any you need:
		//cout << "\t New Area Code: " + string(phoneObject.mdPhoneObj->GetNewAreaCode())		<< endl;
		//cout << "\t     Extension: " + string(phoneObject.mdPhoneObj->GetExtension())			<< endl;
		//cout << "\t    CountyFips: " + string(phoneObject.mdPhoneObj->GetCountyFips())		<< endl;
		//cout << "\t    CountyName: " + string(phoneObject.mdPhoneObj->GetCountyName())		<< endl;
		//cout << "\t           Msa: " + string(phoneObject.mdPhoneObj->GetMsa())						<< endl;
		//cout << "\t          Pmsa: " + string(phoneObject.mdPhoneObj->GetPmsa())					<< endl;
		//cout << "\tTime Zone Code: " + string(phoneObject.mdPhoneObj->GetTimeZoneCode())	<< endl;
		//cout << "\t  Country Code: " + string(phoneObject.mdPhoneObj->GetCountryCode())		<< endl;
		//cout << "\t      Distance: " + string(phoneObject.mdPhoneObj->GetDistance())			<< endl;

		// Result codes come back as a single comma-separated string (e.g. "PS01,PS08").
		// Split it and ask the object for a readable description of each code.
		// ResultCodeDescriptionLong requests the long-form text; a short form is also
		// available via ResultCodeDescriptionShort
		list<string> rs = SplitResultCodes(dataContainer.ResultCodes, ",");
		list<string>::iterator it;

		for (it = rs.begin(); it != rs.end(); it++)
		{
			printf("        %s: %s", it->c_str(), phoneObject->mdPhoneObj->GetResultCodeDescription(it->c_str(), phoneObject->mdPhoneObj->ResultCodeDescriptionLong));
			cout << endl;
		}

		bool isValid = false;

		// In one-shot mode there is nothing more to do after a single pass: mark the
		// input handled and stop the outer loop.
		if (!testPhone.empty()) 
		{
			isValid = true;
			shouldContinueRunning = false;
		}

		// Interactive mode: ask whether to process another phone number. Keep prompting
		// until we get a valid Y/N. "N" ends the program; "Y" falls through to another pass.
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

/**
 * Splits the comma-separated result-code string into individual codes.
 *
 * @param s         The result-code string (e.g. "PS01,PS08").
 * @param delimiter The delimiter string to split on.
 * @return A list holding each individual result code.
 */
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
