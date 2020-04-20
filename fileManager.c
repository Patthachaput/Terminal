#include<stdio.h>
#include<stdlib.h>
#include "mainAuction.h"

/* Hello */

// int main()
// {
// 	USER_T* user;
// 	PRODUCT_T* product;

// 	int init();

// 	int writeUser(USER_T* user);

// 	int writProduct(PRODUCT_T* product);

// 	int writeHistory(HISTORY_T* history);

// 	/*BACKUP_T* getBackUp();*/

// 	USER_T* getUser();

// 	PRODUCT_T* getProduct();

// 	/*HISTORY_T* getHistory();*/

// 	int allFileExist(); /* local function */
// }

int init()
{
	int status;

	FILE* pProduct = NULL;
	FILE* pUser = NULL;
	FILE* pHistory = NULL;
	FILE* pBackup = NULL;

	USER_T numUser;
	PRODUCT_T numProduct;
	int numHistory;
	BACKUP_T numBackUp;

	status = allFileExist();

	pUser = fopen("user.dat", "rb");
	if(pUser == NULL)
	{
		printf("Error to read user file in <init>!\n");
		return 0;
	}
	if(fseek(pUser, -sizeof(USER_T), SEEK_END) == 0)
	{
		fread(&numUser, sizeof(USER_T), 1, pUser);
		TOTALUSER = numUser.idUser;
	}
	else
	{
		TOTALUSER = 0;
	}
	fclose(pUser);

	pProduct = fopen("product.dat", "rb");
	if(pProduct == NULL)
	{
		printf("Error to read product file in <init>!\n");
		return 0;
	}
	if(fseek(pProduct, -sizeof(PRODUCT_T), SEEK_END) == 0)
	{
		fread(&numProduct, sizeof(PRODUCT_T), 1, pProduct);
		TOTALPRODUCT = numProduct.idProduct;
	}
	else
	{
		TOTALPRODUCT = 0;
	}
	fclose(pProduct);

	pHistory = fopen("history.dat", "rb");
	if(pHistory == NULL)
	{
		printf("Error to read history file in <init>!\n");
		return 0;
	}
	if(fseek(pHistory, -sizeof(int), SEEK_END) == 0)
	{
		fread(&numHistory, sizeof(int), 1, pHistory);
		TOTALHISTORY = numHistory;
	}
	else
	{
		TOTALHISTORY = 0;
	}
	fclose(pHistory);

	pBackup = fopen("backup.dat", "rb");
	if(pBackup == NULL)
	{
		printf("Error to read history file in <init>!\n");
		return 0;
	}
	if(fseek(pBackup, -sizeof(BACKUP_T), SEEK_END) == 0)
	{
		fread(&numBackUp, sizeof(BACKUP_T), 1, pBackup);
		TOTALBACKUP = numBackUp.idBackUp;
	}
	else
	{
		TOTALBACKUP = 0;
	}
	fclose(pBackup);

	ADDNEWUSER = 0;
	ADDNEWPRODUCT = 0;
	ADDNEWHISTORY = 0;

	return status;
}

int writeUser(USER_T* user)
{
	int newIdUser = 1;
	int newTotalUser = 0;

	FILE* pUser = NULL;

	newTotalUser = TOTALUSER + ADDNEWUSER;
	for(int i = 0; i < newTotalUser; i++)
	{
		user[i].idUser = i + newIdUser;
		user[i].history = NULL;
	}

	if(newTotalUser > 0)
	{
		pUser = fopen("user.dat", "wb");
		if(pUser == NULL)
		{
			printf("Erroe to open user file! in <writeUser>\n");
			return 0;
		}
		if(fwrite(user, sizeof(USER_T), newTotalUser, pUser) != newTotalUser)
		{
			printf("Erroe to add user! in <writeUser>\n");
			return 0;
		}
		free(user);
		fclose(pUser);
		return 1;
	}

	return 0;
}

int writProduct(PRODUCT_T* product)
{
	int newIdProduct = 1;
	int newTotalProduct = 0;

	FILE* pProduct = NULL;

	newTotalProduct = TOTALPRODUCT + ADDNEWPRODUCT;
	for(int i = 0; i < newTotalProduct; i++)
	{
		product[i].idProduct = i + newIdProduct;
		product[i].host = NULL;
		product[i].userAuthority = NULL;
		product[i].winner = NULL;
	}

	if(newTotalProduct > 0)
	{
		pProduct = fopen("product.dat", "wb");
		if(pProduct == NULL)
		{
			printf("Erroe to open product file! in <writProduct>\n");
			return 0;
		}
		if(fwrite(product, sizeof(PRODUCT_T), newTotalProduct, pProduct) != newTotalProduct)
		{
			printf("Erroe to add product! in <writProduct>\n");
			return 0;
		}
		free(product);
		fclose(pProduct);
		return 1;
	}

	return 0;
}

int writeHistory(HISTORY_T* history)
{
	int idUser;
	int sizeofProductBit;
	int sizaofSealAuction;
	int* productBid = NULL;
	int* sealAuction = NULL;
	int numOfHis;

	int newNumOfHis = 1;
	int newTotalNumOfHis = 0;

	FILE* pHistory = NULL;

	newTotalNumOfHis = TOTALHISTORY + ADDNEWHISTORY;
	if(newTotalNumOfHis > 0)
	{
		pHistory = fopen("history.dat", "wb");
		if(pHistory == NULL)
		{
			printf("Error to read history file in <getHistory>!\n");
			return 0;
		}

		for(int i; i < newTotalNumOfHis; i++)
		{
			numOfHis = i + newNumOfHis;
			idUser = history[i].idUser;
			sizeofProductBit = history[i].sizeofProductBit;
			sizaofSealAuction = history[i].sizaofSealAuction;
			productBid = history[i].productBid;
			sealAuction = history[i].sealAuction;

			if(fwrite(&idUser, sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct1>\n");
				return 0;
			}
		    if(fwrite(&sizeofProductBit, sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct2>\n");
				return 0;
			}
		    if(fwrite(&sizaofSealAuction, sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct3>\n");
				return 0;
			}
		    if(fwrite(productBid, sizeofProductBit * sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct4>\n");
				return 0;
			}
		    if(fwrite(sealAuction, sizaofSealAuction * sizeof(int), 1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct5>\n");
				return 0;
			}
		    if(fwrite(&numOfHis, sizeof(int),1, pHistory) != 1)
			{
				printf("Erroe to add writeHistory! in <writProduct6>\n");
				return 0;
			}
			free(productBid);
			free(sealAuction);
		}
		free(history);
	    fclose(pHistory);
	    return 1;
	}

	return 0;
}
/*
int saveBackUp(BACKUP_T* thisBackup)
{
	FILE* pBackup = NULL;
	BACKUP_T checkBackUp;

	pBackup = fopen("backup.dat", "rb");
	if(pBackup == NULL)
	{
		printf("Error to read backup file in <saveBackUp>!\n");
		return 0;
	}
	if(TOTALBACKUP != 0)
	{
		for(int i = 0; i < TOTALBACKUP; i++)
		{
			if(fread(&checkBackUp, sizeof(BACKUP_T), 1, pBackup) != 1)
			{
				printf("Can't read all data from database, please try agin! <saveBackUp>\n");
				return 0;
			}
			if(thisBackUp->haveNewUser == 1)
			{
				if(thisBackUp->user.idUser == checkBackUp.user.idUser)
				{

				}
			}
		}
		
		
	}
	


}
*/

/****************************************************
 *getBackup function if it have backup will return 
 *all dackup data else will return NULL
 ****************************************************
 */
BACKUP_T* getBackUp()
{
	FILE* pBackup = NULL;
	BACKUP_T* allBackUp = NULL;

	pBackup = fopen("backup.dat", "rb");
	if(pBackup == NULL)
	{
		printf("Error to read backup file in <getBackUp>!\n");
		return allBackUp;
	}
	if(TOTALBACKUP != 0)
	{
		allBackUp = calloc(TOTALBACKUP, sizeof(BACKUP_T));
		if(allBackUp == NULL)
		{
			printf("Error with alocade memory in <getBackUp>\n");
			return allBackUp;
		}

		for(int i = 0; i < TOTALBACKUP; i++)
		{
			if(fread(&allBackUp[i], sizeof(BACKUP_T), 1, pBackup) != 1)
			{
				printf("Can't read all data from database, please try agin! <getBackUp>\n");
				return allBackUp;
			}
		}
	}
	fclose(pBackup);

	return allBackUp;
}

USER_T* getUser()
{
	FILE* pUser = NULL;
	USER_T* allUser = NULL;

	pUser = fopen("user.dat", "rb");
	if(pUser == NULL)
	{
		printf("Error to read user file in <getUser>!\n");
		return allUser;
	}
	if(TOTALUSER != 0)
	{
		allUser = calloc(TOTALUSER, sizeof(USER_T));
		if(allUser == NULL)
		{
			printf("Error with alocade memory in <getUser>\n");
			return allUser;
		}

		for(int i = 0; i < TOTALUSER; i++)
		{
			if(fread(&allUser[i], sizeof(USER_T), 1, pUser) != 1)
			{
				printf("Can't read all data from database, please try agin! <getUser>\n");
				return allUser;
			}
		}
	}
	fclose(pUser);

	return allUser;
}

PRODUCT_T* getProduct()
{
	FILE* pProduct = NULL;
	PRODUCT_T* allProduct = NULL;

	pProduct = fopen("product.dat", "rb");
	if(pProduct == NULL)
	{
		printf("Error to read product file in <getProduct>!\n");
		return allProduct;
	}
	if(TOTALPRODUCT != 0)
	{
		allProduct = calloc(TOTALPRODUCT, sizeof(PRODUCT_T));
		if(allProduct == NULL)
		{
			printf("Error with alocade memory in <getProduct>\n");
			return allProduct;
		}

		for(int i = 0; i < TOTALPRODUCT; i++)
		{
			if(fread(&allProduct[i], sizeof(PRODUCT_T), 1, pProduct) != 1)
			{
				printf("Can't read all data from database, please try agin! <getProduct>\n");
				return allProduct;
			}
		}
	}
	fclose(pProduct);

	return allProduct;
}

HISTORY_T* getHistory()
{
	int idUser;
	int sizeofProductBit;
	int sizaofSealAuction;
	int* productBid;
	int* sealAuction;

	FILE* pHistory = NULL;
	HISTORY_T* allHistory = NULL;

	pHistory = fopen("history.dat", "rb");
	if(pHistory == NULL)
	{
		printf("Error to read history file in <getHistory>!\n");
		return allHistory;
	}
	if(TOTALHISTORY != 0)
	{
		allHistory = calloc(TOTALHISTORY, sizeof(HISTORY_T));
		if(allHistory == NULL)
		{
			printf("Error with alocade memory in <getHistory1>\n");
			return allHistory;
		}

		for(int i = 0; i < TOTALHISTORY; i++)
		{
			if(fread(&idUser, sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read idUser, please try agin! <getHistory>\n");
				return allHistory;
			}
			if(fread(&sizeofProductBit, sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read sizeofProductBit, please try agin! <getHistory>\n");
				return allHistory;
			}
			if(fread(&sizaofSealAuction, sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read sizaofSealAuction, please try agin! <getHistory>\n");
				return allHistory;
			}

			productBid = calloc(sizeofProductBit, sizeof(int));
			if(allHistory == NULL)
			{
				printf("Error with alocade memory in <getHistory2>\n");
				return allHistory;
			}
			sealAuction = calloc(sizaofSealAuction, sizeof(int));
			if(allHistory == NULL)
			{
				printf("Error with alocade memory in <getHistory3>\n");
				return allHistory;
			}

			if(fread(productBid, sizeofProductBit * sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read productBid, please try agin! <getHistory>\n");
				return allHistory;
			}
			if(fread(sealAuction, sizaofSealAuction * sizeof(int), 1, pHistory) != 1)
			{
				printf("Can't read sealAuction, please try agin! <getHistory>\n");
				return allHistory;
			}
			if(fseek(pHistory, sizeof(int), SEEK_CUR) == 0)
			{
				printf("Can't seek, please try agin! <getHistory>\n");
				return allHistory;
			}
			allHistory[i].idUser = idUser;
			allHistory[i].productBid = productBid;
			allHistory[i].sealAuction = sealAuction;
			allHistory[i].sizeofProductBit = sizeofProductBit;
			allHistory[i].sizaofSealAuction = sizaofSealAuction;
		}
	}
	fclose(pHistory);

	return allHistory;
}


/************************************************************
 *Local function used dy init.  
 *This function will caheck all file are exit or not,
 *if all file are exit will return 1 else return negative
 *number follow index of file and created it.
 ************************************************************
 */
int allFileExist()
{
	int status = 1;

	FILE* pProduct = NULL;
	FILE* pUser = NULL;
	FILE* pHistory = NULL;
	FILE* pBackup = NULL;

	pUser = fopen("user.dat", "rb");
	if(pUser == NULL)
	{
		pUser = fopen("user.dat", "wb");
		if(pUser == NULL)
		{
			printf("Error with created user file! in <allFileExit>\n");
			exit(1);
		}
		fclose(pUser);
		status = -1;
	}
	fclose(pUser);

	pProduct = fopen("product.dat", "rb");
	if(pProduct == NULL)
	{
		pProduct = fopen("product.dat", "wb");
		if(pProduct == NULL)
		{
			printf("Error with created product file! in <allFileExit>\n");
			exit(2);
		}
		fclose(pProduct);
		status = -2;
	}
	fclose(pProduct);

	pHistory = fopen("history.dat", "rb");
	if(pHistory == NULL)
	{
		pHistory = fopen("history.dat", "wb");
		if(pHistory == NULL)
		{
			printf("Error with created history file! in <allFileExit>\n");
			exit(3);
		}
		fclose(pHistory);
		status = -3;
	}
	fclose(pHistory);

	pBackup = fopen("backup.dat", "rb");
	if(pBackup == NULL)
	{
		pBackup = fopen("backup.dat", "wb");
		if(pBackup == NULL)
		{
			printf("Error with created backup file! in <allFileExit>\n");
			exit(4);
		}
		fclose(pBackup);
		status = -4;
	}
	fclose(pBackup);

	return status;
}
