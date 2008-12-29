#ifndef TELLDUSSETTINGS_H
#define TELLDUSSETTINGS_H

#include "../Device.h"
//#include <vector>

class privateVars;

class TelldusSettings
{
public:
	TelldusSettings(void);
	char * getSetting(const char *strName);
	int getNumberOfDevices(void);
	Device* getDevice(int intDeviceId);
	char* getName(int intDeviceId);
	bool setName(int intDeviceId, const char* strNewName);
	char* getProtocol(int intDeviceId);
	bool setProtocol(int intDeviceId, const char* strVendor);
	int getModel(int intDeviceId);
	bool setModel(int intDeviceId, int intModel);
	char* getArgument(int intDeviceId, const char *strName);
	bool setArgument(int intDeviceId, const char *strName, const char *strValue);
	int addDevice();
	int getDeviceId(int intDeviceIndex);
	bool removeDevice(int intDeviceId);

	~TelldusSettings(void);
	
protected:
	char *getStringSetting(int intDeviceId, const char* name, bool parameter);
	bool setStringSetting(int intDeviceId, const char* name, const char *value, bool parameter);
	int getIntSetting(int intDeviceId, const char* name, bool parameter);
	bool setIntSetting(int intDeviceId, const char* name, int value, bool parameter);

private:
	int getNextDeviceId();
	
	privateVars *d;
};

#endif