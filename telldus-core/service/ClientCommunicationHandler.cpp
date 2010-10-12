#include "ClientCommunicationHandler.h"
#include "Message.h"

class ClientCommunicationHandler::PrivateData {
public:
	TelldusCore::Socket *clientSocket;
	Event *event;
	bool done;
};

ClientCommunicationHandler::ClientCommunicationHandler(){

}

ClientCommunicationHandler::ClientCommunicationHandler(TelldusCore::Socket *clientSocket, Event *event)
	:Thread()
{
	d = new PrivateData;
	d->clientSocket = clientSocket;
	d->event = event;
	d->done = false;
	
}

ClientCommunicationHandler::~ClientCommunicationHandler(void)
{
	wait();
	delete(d->event);
	delete(d->clientSocket);
	delete d;
}

void ClientCommunicationHandler::run(){
	//run thread
	
	std::wstring clientMessage = d->clientSocket->read();

	int intReturn;
	std::wstring strReturn;
	strReturn = L"";
	parseMessage(clientMessage, intReturn, strReturn);
	
	TelldusCore::Message msg;
	
	if(strReturn == L""){
		msg.addArgument(intReturn);
	}
	else{
		msg.addArgument(strReturn);
	}
	msg.append(L"\n");
	d->clientSocket->write(msg);

	//We are done, signal for removal
	d->done = true;
	d->event->signal();
}

bool ClientCommunicationHandler::isDone(){
	return d->done;
}


void ClientCommunicationHandler::parseMessage(const std::wstring &clientMessage, int &intReturn, std::wstring &wstringReturn){

	intReturn = 0;
	wstringReturn = L"";
	std::wstring msg(clientMessage);	//Copy
	std::wstring function(TelldusCore::Message::takeString(&msg));
	
	if (function == L"tdTurnOn") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	//tdTurnOn(intDeviceId);

	} else if (function == L"tdTurnOff") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		intReturn = 0; //tdTurnOff(intDeviceId);

	} else if (function == L"tdBell") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	// tdBell(intDeviceId);

	} else if (function == L"tdDim") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		int level = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	// tdDim(intDeviceId, level);

	} else if (function == L"tdLearn") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	//tdLearn(intDeviceId);

	} else if (function == L"tdLastSentCommand") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		int methodsSupported = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	// tdLastSentCommand(intDeviceId, methodsSupported);

	} else if (function == L"tdLastSentValue") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		char *value = "";	//tdLastSentValue(intDeviceId);
		wstringReturn =  TelldusCore::Message::charToWstring(value);

	} else if(function == L"tdGetNumberOfDevices"){
		intReturn = 12;	//tdGetNumberOfDevices();

	} else if (function == L"tdGetDeviceId") {
		int intDeviceIndex = TelldusCore::Message::takeInt(&msg);
		intReturn = 1;	//tdGetDeviceId(intDeviceIndex);

	} else if (function == L"tdGetDeviceType") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		intReturn = 11;	// tdGetDeviceType(intDeviceId);

	} else if (function == L"tdGetName") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		char *name = "Default name";	//tdGetName(intDeviceId);
		wstringReturn = TelldusCore::Message::charToWstring(name);

	} else if (function == L"tdSetName") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		std::wstring name = TelldusCore::Message::takeString(&msg);
		intReturn = 0; //tdSetName(intDeviceId, name.c_str());

	} else if (function == L"tdGetProtocol") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		char *protocol = "Default protocol";	//tdGetProtocol(intDeviceId);

	} else if (function == L"tdSetProtocol") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		std::wstring protocol = TelldusCore::Message::takeString(&msg);
		intReturn = 0;	// tdSetProtocol(intDeviceId, protocol.c_str());

	} else if (function == L"tdGetModel") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		char *model = "Default model";	//tdGetModel(intDeviceId);

	} else if (function == L"tdSetModel") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		std::wstring model = TelldusCore::Message::takeString(&msg);
		intReturn = 0;	// tdSetModel(intDeviceId, model.c_str());

	} else if (function == L"tdSetDeviceParameter") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		std::wstring name = TelldusCore::Message::takeString(&msg);
		std::wstring value = TelldusCore::Message::takeString(&msg);
		intReturn = 0;	//tdSetDeviceParameter(intDeviceId, name.c_str(), value.c_str());

	} else if (function == L"tdGetDeviceParameter") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		std::wstring name = TelldusCore::Message::takeString(&msg);
		std::wstring defaultValue = TelldusCore::Message::takeString(&msg);
		char *value = "Device parameter default";	//tdGetDeviceParameter(intDeviceId, name.c_str(), defaultValue.c_str());
		wstringReturn = TelldusCore::Message::charToWstring(value);

	} else if (function == L"tdAddDevice") {
		intReturn = 0;	// tdAddDevice();

	} else if (function == L"tdRemoveDevice") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	// tdRemoveDevice(intDeviceId);

	} else if (function == L"tdMethods") {
		int intDeviceId = TelldusCore::Message::takeInt(&msg);
		int intMethodsSupported = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	// tdMethods(intDeviceId, intMethodsSupported);

	} else if (function == L"tdGetErrorString") {
		int intErrorNo = TelldusCore::Message::takeInt(&msg);
		char *response = "Default error string";	//tdGetErrorString(intErrorNo);
		wstringReturn = TelldusCore::Message::charToWstring(response);

	} else if (function == L"tdSendRawCommand") {
		std::wstring command = TelldusCore::Message::takeString(&msg);
		int reserved = TelldusCore::Message::takeInt(&msg);
		intReturn = 0;	//tdSendRawCommand(command.c_str(), reserved);
		
	} else if (function == L"tdConnectTellStickController") {
		int vid = TelldusCore::Message::takeInt(&msg);
		int pid = TelldusCore::Message::takeInt(&msg);
		std::wstring serial = TelldusCore::Message::takeString(&msg);
		//tdConnectTellStickController(vid, pid, serial.c_str());
		wstringReturn = L"";

	} else if (function == L"tdDisconnectTellStickController") {
		int vid = TelldusCore::Message::takeInt(&msg);
		int pid = TelldusCore::Message::takeInt(&msg);
		std::wstring serial = TelldusCore::Message::takeString(&msg);
		//tdDisconnectTellStickController(vid, pid, serial.c_str());
		wstringReturn = L"";

	}
	else{
		intReturn = 6;
	}
}
