#include "headers.h"

/*static void exit_nicely(PGconn *DBconn)
{
    PQfinish(DBconn);
    exit(1);
}
 */

void DBSetResult(struct SMData *SMDataEntry, PGconn *DBconn){
	
	if(SMDataEntry == NULL || DBconn == NULL)		
		return;	
	
	char dbResultQuery[] = "select * from f_settaskstatus('1');";
	PGresult *PGRes;
 
    fprintf(stdout , "%s\n", dbResultQuery);
	 
    PGRes = PQexec(DBconn, dbResultQuery);

    if (PQresultStatus(PGRes) != PGRES_TUPLES_OK) {
		
        fprintf(stderr, "Не могу получить SMData: %s", PQerrorMessage(DBconn));
        PQclear(PGRes);        
		return;
		
    }	  
	
    PQclear(PGRes);
	
	return;
	
}

int FillStructure(PGresult *PGRes, struct SMData *SMDataEntry){
	
	char FieldName[AWSTRLEN];
	char tValue[AWSTRLEN];
	int nFields;
	int	Iter=0,
		RowNum=0;
		
	if(PGRes == NULL || SMDataEntry == NULL) {
		
		fprintf(stderr, "Ошибка в аргументах FillStructure()\n");
		return 0;	
	
	}
	
	if ((nFields = PQnfields(PGRes)) == 0){
		
		fprintf(stderr, "Количество полученных полей в FillStructure() равно 0\n");
		return 0;	
		
	}
	
	for(Iter=0; Iter < nFields; Iter++) {
			
		if(strlen(PQfname(PGRes, Iter)) >= AWSTRLEN || \
		strlen(PQgetvalue(PGRes, RowNum, Iter)) >= AWSTRLEN ) {
			
			fprintf(stderr, "Слишком длинная строка в FillStructure()\n");
			return 0;
			
		}
		
		strcpy(FieldName, PQfname(PGRes, Iter));
		strcpy(tValue, PQgetvalue(PGRes, RowNum, Iter));
		
		if( strcmp(FieldName, "o_smdataid") == 0 ){
			
			strcpy(SMDataEntry->SMDataID, tValue);	
			
		} else if ( strcmp(FieldName, "o_taskid") == 0 ) {
			
			strcpy(SMDataEntry->TaskID, tValue);
					
		} else if ( strcmp(FieldName, "o_nameid") == 0 ) {
		
			strcpy(SMDataEntry->NameID, tValue);
		
		} else if ( strcmp(FieldName, "o_netid") == 0 ) {
		
			strcpy(SMDataEntry->NetID, tValue);
			
		} else if ( strcmp(FieldName, "o_policy") == 0 ) {
		
			strcpy(SMDataEntry->Policy, tValue);
			
		} else if ( strcmp(FieldName, "o_smoptions") == 0 ) {
		
			strcpy(SMDataEntry->SMOptions, tValue);
// добавить malloc и проверку SMOptions	
		}
	}
	
	SMDataEntry->WasSent = false;
	
	return 1;
	
}

int DBConnIsAlive(PGconn *DBconn){
	
	if(DBconn == NULL) {
		
		fprintf(stderr, "Ошибка в DBConnIsAlive()\n");
		
	}
	
	if (PQstatus(DBconn) == CONNECTION_OK) {
				
		return 1;
		
    }
	
	fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(DBconn));		
	return 0;
	
}

int DoNothing(struct SMData *SMDataEntry){
	
	if( SMDataEntry == NULL) {
		
		fprintf(stderr, "Ошибка в аргументах DoNothing()\n");
		return 0;	
	
	}
	
	if(strcmp(SMDataEntry->SMOptions, "DoNothing") == 0){
		
		return 1;
		
	}
	
	return 0;	
	
}

int GetLEGData(struct SMData *SMDataEntry, PGconn *DBconn)
{    
    
    PGresult   *PGRes;
    int         nFields;    
	int			j;				
	int RowNum=0;
//	struct SMData SMDataEntry;				
	char SMDataQuery[] = "SELECT * from f_gettask('client')";	

    /* Check to see that the backend connection was successfully made */	  
	if(SMDataEntry == NULL || DBconn == NULL)		
		return 0;
			
	if(!DBConnIsAlive(DBconn))
		return 0;
 
    fprintf(stdout , "%s\n", SMDataQuery);
	 
    PGRes = PQexec(DBconn, SMDataQuery);
	
    if (PQresultStatus(PGRes) != PGRES_TUPLES_OK) {
		
        fprintf(stderr, "Не могу получить SMData: %s", PQerrorMessage(DBconn));
        PQclear(PGRes);        
		return 0;
		
    }	
    
    /* first, print out the attribute names and fill a structure*/
    nFields = PQnfields(PGRes);
	
    for  (j = 0; j < nFields; j++){
					
			fprintf(stdout, "%-15s", PQfname(PGRes, j));			
			
		}

	printf("\n\n");

    /* next, print out the rows */
    
	for (j = 0; j < nFields; j++) {
		
            printf("%-15s", PQgetvalue(PGRes, RowNum, j));
			
	}

	printf("\n");    

	if(FillStructure(PGRes, SMDataEntry)) {
		
		if(DoNothing(SMDataEntry)){
		
			sleep(10);
		
		}
	
	}
	
    PQclear(PGRes);
	
	//PrintSMData(SMData);                                                                                                                                                      PQfinish(conn);

    return 1;
}

