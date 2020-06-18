/******************************************************
*       Copyright Keysight Technologies 2015
******************************************************/

using namespace std;

///////////////////////////////
// Helper methods and variables used internally by the driver.  Add as needed.
///////////////////////////////

// Member Variables

//double _simMyVar = 0; // TODO: Example member variable declaration.  Delete if not used.


// Helper Methods

void ResetVars()
{
	// Resets any driver member variables to initial settings.
	// Called by driver Reset and ResetWithDefaults functions.

	//_simMyVar = 0; // TODO: Example reset of member variable.  Delete if not used.

}

void GetSimArray(int points, ViReal64 data[])
{
	// Return simulatied array data.  
	// Replicate for other data types as needed.
	for (int i = 0; i < points; i++)
		data[i] = 0;
}

string StrToUpper(string strToConvert)
{
	// Change a std::string to upper case
	for (unsigned int i = 0; i<strToConvert.length(); i++)
		strToConvert[i] = toupper(strToConvert[i]);

	return strToConvert;  // Return the converted string
}

void StrReplace(string &s, const string &search, const string &replace)
{
	/*
	Replace all occurrances of a substring in a std::string.
	Operates directly on string, does not return a copy.
	Syntax:  StrReplace(myString, "Find Text", "Replace Text");
	Typical use to delete quotes after SCPI query of attribute that returns quoted text:

	// Remove any quotes
	string strValue(AttributeValue);
	StrReplace(strValue, "\"", "");
	strncpy_s(AttributeValue, AttributeValueBufferSize, strValue.c_str(), _TRUNCATE);
	*/

	for (size_t pos = 0;; pos += replace.length())
	{
		pos = s.find(search, pos);
		if (pos == string::npos) break;
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}


