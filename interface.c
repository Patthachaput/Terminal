/*
 * interface.c
 *
 *      the main file that interact with user and call other functions
 *  from other file to process the program
 *
 *
 *  Project CPE111 Data structure - TEAM TERMINAL
 *  Member: Natacha Punyathanasub       (Nut)       62070503415
 *          Patthachaput Thanesmaneerat (Jui)       62070503432
 *          Supakorn Srisawas           (Field)     62070503464
 *          Narapathra Morakrant        (Foremost)  62070503464
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "validate.h"
#include "mainAuction.h"
#include "dataBuilder.h"

#define NLOGIN 0
#define LOGIN 1
#define GUEST 2


int loginStatus = 0; /* 0 for not log in, 1 for login with account, 2 for guest */
USER_T* loginUser;

int logInMenu()
{
    char buffer[32];
    int choice = 0;
    
    if(init()==0)
    {
        printf("Initial process failed\n");
        exit(1);
    }
    buildData();
    
    printf("=============== Login =============\n\n");
    printf("           1.Log in                \n");
    printf("           2.Log in as guest       \n");
    printf("           3.Register              \n");
    printf("           4.Exit program          \n\n");
    printf("===================================\n\n");

    do
    {
        loginStatus = NLOGIN;
        choice = 0;
        printf("How do you want to login? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);

        if((choice > 4)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
    
    }while ((choice > 4)||(choice < 1));
    
    printf("\n");
    
    return choice;
}

int login()
{
    char buffer[64];
    char email[64];
    char password[64];
    int len = 0;
    int validate = 0;
    
    do
    {
        printf("Please enter your email and password to login\n");
        printf("Email: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", email);
        printf("Password: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", password);
        
        if ((strcmp(email,"\0")==1)&&(strcmp(password,"\0")==1))
        {
            validate = -1;
            break;
        }
        
        //validate = checkUser(email,password);
        
        validate = 1; /* we will assume that we log in now*/
        
        if(validate == 1)
        {
            loginStatus = LOGIN;
            printf("Successful login!\n\n");
            break;
        }
        else
        {
            printf("Incorrect email or password! please try again\n");
        }
        
    }while (validate != 1);
    
    printf("\n");
    
    return validate;
}

int registration()
{
    char buffer[64];
    char email[64];
    char password[64];
    char name[64];
    char address[64];
    char phoneNumber[64];
    char bankAccNumber[64];
    int validate = 0;
    USER_T newUser;
    
    do
    {
        printf("Please enter your infomation\n");
        printf("Email: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", email);
        strcpy(newUser.email,email);
    
        do
        {
            memset(password,0, sizeof(password));
            printf("Password: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", password);
            validate = validatePassword(password);
            if(validate == 1)
            {
                strcpy(newUser.password,password);
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(name,0, sizeof(name));
            printf("Full name (No title): ");
            fgets(name,sizeof(name),stdin);
            validate = validateName(name);
            if(validate == 1)
            {
                strcpy(newUser.name,name);
                break;
            }
        }while (validate != 1);
            
        printf("Address: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", address);
        
        do
        {
            memset(phoneNumber,0, sizeof(phoneNumber));
            printf("Phone Number (Thai): ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", phoneNumber);
            validate = validatePhoneNumThai(phoneNumber,buffer);
            if(validate == 1)
            {
                strcpy(newUser.phoneNumber,phoneNumber);
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(bankAccNumber,0, sizeof(bankAccNumber));
            printf("Bank Account: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", bankAccNumber);
            validate = validateBankAcc(bankAccNumber,buffer);
            if(validate == 1)
            {
                strcpy(newUser.bankAccNumber,bankAccNumber);
                break;
            }
        }while (validate != 1);
        
        if(validate == 1)
        {
            insertUser(newUser);
            printf("\nThis your information\n");
            printf("\tEmail: %s\n",email);
            printf("\tPassword: %s\n",password);
            printf("\tFull name (No title): %s\n",name);
            printf("\tAddress: %s\n",address);
            printf("\tPhone Number (Thai): %s\n",phoneNumber);
            printf("\tBank Account: %s\n",bankAccNumber);
            printf("Successful registered!\n\n");
            break;
        }
        
    }while (validate != 1);
    
    printf("\n");
    
    return validate;
}

int browse()
{
    char buffer[32];
    int choice = 0;
    
    printf("=============== Browse ============\n\n");
    printf("           1.Categories            \n");
    printf("           2.Date                  \n");
    printf("           3.Bid Price             \n");
    printf("           4.Back                  \n\n");
    printf("===================================\n\n");
    
    do
    {
        choice = 0;
        printf("How do you want to browse? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
       
        if((choice > 4)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
       
    }while ((choice > 4)||(choice < 1));
    
    printf("\n");
    
    return choice;
}

void bidHistory()
{
    
}

void saleHistory()
{
    
}

void printCategory(int category)
{
    int choice = 0;
    switch (choice) {
        case 1:
            printf("Category: Home & Garden\n");
            break;
        case 2:
            printf("Category: Collectibles\n");
            break;
        case 3:
            printf("Category: Sport\n");
            break;
        case 4:
            printf("Category: Electronic\n");
            break;
        case 5:
            printf("Category: Fashion\n");
            break;
        case 6:
            printf("Category: Health & Beauty\n");
            break;
        case 7:
            printf("Category: Motor\n");
            break;
        default:
            break;
    }
}

DATE_T createDateStruct(char input[64])
{
    DATE_T dateClose;
    char date[32];
    char time[32];
    int day=0;
    int month=0;
    int year=0;
    int hour=0;
    int minute=0;
    
    sscanf(input,"%s %s",date,time);
    sscanf(date,"%d-%d-%d",&day,&month,&year);
    sscanf(time,"%d:%d", &hour, &minute);
    
    dateClose.hour = hour;
    dateClose.minute = minute;
    dateClose.day = day;
    dateClose.month = month;
    dateClose.year = year;
    
    return dateClose;
}

void createAuction()
{
    char buffer[64];
    char buffer2[64];
    int choice = 0;
    char name[64];
    char description[120];      /*product description*/
    int category = 0;           /*fixed category*/
    char dateClose[64];
    double minBid = 0;          /*minimum bid price*/
    int validate = 0;
    PRODUCT_T newProduct;
    
    do
    {
        printf("Please enter the product infomation\n");
        printf("Name: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", name);
        
        memset(name,0, sizeof(name));
        printf("Description: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", description);
        strcpy(newProduct.description,description);
        
        do
        {
            category = 0;
            printf("Category: \n");
            printf("\t1.Home & Garden\n");
            printf("\t2.Collectibles\n");
            printf("\t3.Sport\n");
            printf("\t4.Electronic\n");
            printf("\t5.Fashion\n");
            printf("\t6.Health & Beauty\n");
            printf("\t7.Motor\n");
            printf("Choose your category ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%d", &category);
            if((category > 7)||(category < 1))
            {
               validate = 0;
               printf("Invalid choice! please try again\n\n");
            }
            else
            {
                newProduct.category = category;
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(buffer2,0, sizeof(buffer2));
            minBid =0;
            printf("Minimum Bid: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", buffer2);
            validate = 0;
            if(strlen(buffer2) == checkDigits(buffer2))
            {
                sscanf(buffer2,"%lf", &minBid);
                newProduct.minbid = minBid;
                validate = 1;
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(dateClose,0, sizeof(dateClose));
            printf("Date Close (dd-mm-yyyy hh:tt) : ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%[^\n]", dateClose);
            validate = validateDateTime(dateClose);
            if(validate == 1)
            {
                newProduct.dateClose = createDateStruct(dateClose);
                break;
            }
        }while (validate != 1);
        
        newProduct.hostId = loginUser->idUser;
        newProduct.host = loginUser;
        
        if(validate == 1)
        {
            insertProduct(newProduct);
            printf("\nThis is your product information\n");
            printf("\tName: %s\n",name);
            printf("\tDescription: %s\n",description);
            printCategory(category);
            printf("\tMinimum Bid: %0.2lf\n",minBid);
            printf("\tDate Close: %s\n",dateClose);
            printf("Successful created the auction!\n\n");
            break;
        }
        
    }while (validate != 1);
}

int personalInfo()
{
    char buffer[32];
    int choice = 0;
    char email[64];
    char password[64];
    char name[64];
    char address[64];
    char phoneNumber[64];
    char bankAccNumber[64];
    
    printf("=========== Personal Info =========\n\n");
    printf("\t1. Email: %s\n",email);
    printf("\t2. Password: %s\n",password);
    printf("\t3. Full name (No title): %s\n",name);
    printf("\t4. Address: %s\n",address);
    printf("\t5. Phone Number (Thai): %s\n",phoneNumber);
    printf("\t6. Bank Account: %s\n",bankAccNumber);
    printf("\t7. Back to homepage\n");
    printf("\n");
    printf("===================================\n\n");
    
    do
    {
        choice = 0;
        printf("What do you want to edit? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
       
        if((choice > 7)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
       
    }while ((choice > 7)||(choice < 1));
           
    return choice;

}

int homePage()
{
    char buffer[32];
    int choice = 0;

    printf("============== Homepage ===========\n\n");
    printf("           1.Browse                \n");
    printf("           2.Bid history           \n");
    printf("           3.Sale history          \n");
    printf("           4.Create new auction    \n");
    printf("           5.Edit personal info    \n");
    printf("           6.Log out               \n\n");
    printf("===================================\n\n");

    do
    {
        choice = 0;
        printf("How do you want to login? ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d", &choice);
        
        if((choice > 6)||(choice < 1))
        {
            printf("Invalid choice! please try again\n\n");
        }
        else
        {
            break;
        }
        
    }while ((choice > 6)||(choice < 1));
    
    printf("\n");
    
    return choice;
}

int main()
{
    int choice = 0;
    
    do
    {
        choice = logInMenu();
        
        if (choice == 1)
        {
            choice = login();
            do
            {
                if(choice == LOGIN)
                {
                    choice = homePage();
                    switch (choice) {
                        case 1:
                            if (browse() == 4)
                            {
                                choice = 1;
                            }
                            break;
                        case 2:
                            bidHistory();
                            break;
                        case 3:
                            saleHistory();
                            break;
                        case 4:
                            createAuction();
                            break;
                        case 5:
                            personalInfo();
                            break;
                        default:
                            break;
                    }
                }
            }while (choice == 1);
        }
        else if (choice == 2)
        {
            browse();
        }
        else if (choice == 3)
        {
            registration();
        }
        else
        {
            break;
        }
        
    }while (choice != 4);
    
    return 0;
}
