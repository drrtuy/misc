#include "headers.h"

int SendLEGData(struct SMData *SMDataEntry, SMB_HANDLE smAPI) {
	
	ReturnCode *smRetCode = NULL;
	MappingType smMapType = IP_RANGE;
	char *NetID;
	
	if(SMDataEntry == NULL || smAPI == NULL) {
		
		fprintf(stderr, "Cannot send data to SM\n");
		return 0;
			
	}
	
	if(isEmpty(SMDataEntry->NetID) || isEmpty(SMDataEntry->NameID)){
		
		fprintf(stderr, "Username or Mappings is empty in SendLEGData()\n");
		return 0;
	}
		
	NetID = SMDataEntry->NetID;	
	
	if(SMB_isConnected(smAPI) == true){

// отправить мусор вместо IP; domain is not known
		
		SMB_logoutByMapping(smAPI, SMDataEntry->NetID, smMapType, NULL);	
		//freeReturnCode(smRetCode);
		
	}
	
	if(SMB_isConnected(smAPI) == true){
		
		smRetCode = SMB_login(smAPI ,SMDataEntry->NameID,\
				  &NetID, &smMapType, 0, NULL, NULL, 0, NULL, false, 0);
		
	}
	
    if(smRetCode == NULL || isReturnCodeError(smRetCode)) {
//sprintfReturnCode для вывода		
		fprintf(stderr, "There was an error while trying to login a user into SM\n");
		freeReturnCode(smRetCode);
		return 0;
		
	}	
	
	SMDataEntry->WasSent = true;
	freeReturnCode(smRetCode);
	
	return 1;
	
}


