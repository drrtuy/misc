#include "headers.h"

typedef struct LEGStruct{
		char NameID[AWSTRLEN];
		char NetID[AWSTRLEN];
		char Policy[AWSTRLEN];
		char *SMOptions;
};

int isEmpty(char *String){
	
	if(String == NULL || (strlen(String) == 0))
		return 1;
	
	return 0;
	
}

void *ThreadTask(void *Arg);

int main(int argc, char **argv)
{
	int Iter1=0, RetCode=0;
	pthread_t Threads[MAXTHREADS];
	SMB_HANDLE smAPI;
	char *smHostName = "smhost";
	struct ThrArgStruct ThreadArg;	
	static char StartConnInfo[]= "host=pghost user=smdatauser dbname=SMLEG password=botbot";
		
	smAPI = SMB_init(10, 0, 200000, 10, 30);
	
	if(smAPI == NULL){
		
		fprintf(stderr, "SM API init fail\n");
		exit(EXIT_FAILURE);
		
	}
	
	SMB_setReconnectTimeout(smAPI, SMRECONNTO);	
	SMB_connect(smAPI, smHostName, SMPORT);	
		
	ThreadArg.DBConnInfo = StartConnInfo;
	ThreadArg.SMRes = smAPI; 	
	
	//while(1) {
	
		for(Iter1=0; Iter1 < MAXTHREADS; Iter1++) {
			
			fprintf(stderr, "Starting thread №%d\n", Iter1);
			
			RetCode=pthread_create(&Threads[Iter1], NULL, ThreadTask, &ThreadArg);		
			if(RetCode != 0) {			
				
				fprintf(stderr, "pthread_create() error\n");
				
			}
			
		}
		
		for(Iter1=0; Iter1 < MAXTHREADS; Iter1++) {

				RetCode=pthread_join(Threads[Iter1], NULL);
				fprintf(stderr, "Thread №%d is finished\n", Iter1);
						
		}
		
	//}
	
	 SMB_disconnect(smAPI);
     SMB_release(smAPI);
	
	fprintf(stderr, "The End. Program is finished\n");
	
	sleep(10);
	
	exit(EXIT_SUCCESS);
}

void *ThreadTask(void *Arg){
	
	struct ThrArgStruct *ThreadArg = (struct ThrArgStruct *) Arg;
	struct SMData SMDataEntry;
	PGconn	*DBconn;
	void *Nothing;	
	
	DBconn = PQconnectdb((const char*) ThreadArg->DBConnInfo);

/*
	if(!DBConnIsAlive(DBConn)){
		
		exit_nicely(DBConn);
		return Nothing;
		
	}
	
	if(!SMConnIsAlive()) {
		
		exit_nicely(*********);
		return Nothing;
		
	}
*/
	while(DBConnIsAlive(DBconn) && ( SMB_isConnected(ThreadArg->SMRes) == true) ) {
//Collect data from DB and fill a structure.
		if(GetLEGData(&SMDataEntry, DBconn)) {
			//Send data to SM
			if(SendLEGData(&SMDataEntry, ThreadArg->SMRes)){
//рассмотреть поведение при разрыве связи с субд				
				DBSetResult(&SMDataEntry, DBconn);				
				
			} else {
				
				DBSetResult(&SMDataEntry, DBconn);
			
			}
		}
		
	}
	
	PQfinish(DBconn);
	sleep(10);
	return Nothing;
	
}