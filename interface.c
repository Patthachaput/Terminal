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
 *          Supakorn Srisawas           (Field)     62070503449
 *          Narapathra Morakrant        (Foremost)  62070503464
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "validate.h"
#include "dataBuilder.h"

#define NLOGIN 0
#define LOGIN 1
#define GUEST 2


int loginStatus = 0; /* 0 for not log in, 1 for login with account, 2 for guest */
USER_T* loginUser;
DATE_T currentDate;

int logInMenu()
{
    char buffer[32];
    int choice = 0;
    
    printf("============================ Login ==========================\n\n");
    printf("                        1.Log in                             \n");
    printf("                        2.Log in as guest                    \n");
    printf("                        3.Register                           \n");
    printf("                        4.Exit program                       \n\n");
    printf("=============================================================\n\n");

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

int loginInput()
{
    char buffer[64];
    char email[64];
    char password[64];
    int len = 0;
    int validate = 0;
    USER_T* bufferUser;
    
    
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
            loginStatus = NLOGIN;
            break;
        }
        
        //validate = validateEmail(email);
        validate = 1;
        if(validate == 1)
        {
            bufferUser = searchUserByEmail(email);
            
            if(strcmp(bufferUser->password,password)==0)
            {
                loginStatus = LOGIN;
                loginUser = bufferUser;
                printf("Successful login!\n\n");
                break;
            }
            else
            {
                loginUser = NULL;
                printf("Incorrect email or password! please try again\n");
            }

        }
        
    }while (loginStatus != 1);
    
    /*
    printf("=========== Personal Info =========\n\n");
    printf("\t Email: %s\n",loginUser->email);
    printf("\t Password: %s\n",loginUser->password);
    printf("\t Full name (No title): %s\n",loginUser->name);
    printf("\t Address: %s\n",loginUser->address);
    printf("\t Phone Number (Thai): %s\n",loginUser->phoneNumber);
    printf("\t Bank Account: %s\n",loginUser->bankAccNumber);
    printf("\n");
    printf("===================================\n\n");
    printf("\n");
    */
    return loginStatus;
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
        printf("Please enter your information\n");

        do
        {
            printf("\n");
            memset(email,0, sizeof(email));
            printf("Email: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", email);
            //validate = validateEmail(email);
            validate = 1;
            if(validate == 1)
            {
                strcpy(newUser.email,email);
                break;
            }
        }while (validate != 1);
    
        do
        {
            printf("\n");
            memset(password,0, sizeof(password));
            printf("Please enter password following to these rules\n");
            printf("- At least 8 characters long and no longer than 12 characters\n");
            printf("- MUST contain at least one upper case letter\n");
            printf("- MUST contain at least one lower case letter\n");
            printf("- MUST contain at least two digits\n");
            printf("- MUST contain at least one of the following special characters: ? @ %% $ #\n");
            printf("- MUST not contain any other special characters not in the list above\n");
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
            printf("\n");
            memset(name,0, sizeof(name));
            printf("Full name (No title): ");
            fgets(name,sizeof(name),stdin);
            validate = validateName(name);
            if(validate == 1)
            {
                printf("\t\t%s\n",name);
                strcpy(newUser.name,name);
                break;
            }
        }while (validate != 1);
        
        do
        {
            printf("\n");
            memset(address,0, sizeof(address));
            printf("Please enter address following to these rules\n");
            printf("- Begins with a number (the house number) which can include a slash, e.g. “34/12”\n");
            printf("but must have at least one digit before and one digit after the slash.\n");
            printf("- Next a street name which can include numbers as well as letters\n");
            printf("- Next an optional label “Road”, “Street” or “Lane”\n");
            printf("- a postal code must be five digits and which must begin with “10”\n");
            printf("Address (Bangkok): ");
            fgets(address,sizeof(address),stdin);
            validate = validateAddress(address);
            if(validate == 1)
            {
                strcpy(newUser.address,address);
                break;
            }
        }while (validate != 1);
        
        do
        {
            printf("\n");
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
            printf("\n");
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
            printf("\n");
            if(registerNewUser(newUser) == 0)
            {
                printf("The user with this email is already exist\n");
                printf("Please try again\n");
            }
            else
            {
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
        }
        
    }while (validate != 1);
    
    printf("\n");
    
    return validate;
}

int browseByCatagory()
{
    char buffer[32];
    int choice = 0;
    
    printf("===================== Browse by catagory ====================\n\n");
    printf("                      1.Home & Garden                        \n");
    printf("                      2.Collectibles                         \n");
    printf("                      3.Sport                                \n");
    printf("                      4.Electronic                           \n");
    printf("                      5.Fashion                              \n");
    printf("                      6.Health & Beauty                      \n");
    printf("                      7.Motor                                \n\n");
    printf("=============================================================\n\n");
    
    do
    {
        choice = 0;
        printf("Choose your category to browse : ");
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
       
    }while ((choice > 4)||(choice < 1));
    
    dateTimeToday(&currentDate.day,&currentDate.month,&currentDate.year,&currentDate.hour,&currentDate.minute);
    showProductByCat(choice,currentDate);
    
    return 0;
}

int subBrowse(int choice)
{
    switch (choice) {
        case 1:
            browseByCatagory();
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
    
    return 0;
}

int browse()
{
    char buffer[32];
    int choice = 0;
    
    printf("=========================== Browse ==========================\n\n");
    printf("                         1.Categories                         \n");
    printf("                         2.Date                               \n");
    printf("                         3.Bid Price                          \n");
    printf("                         4.Back                               \n\n");
    printf("=============================================================\n\n");

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

int createAuction()
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
        memset(name,0, sizeof(name));
        printf("Name: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", name);
        strcpy(newProduct.name,name);
        
        memset(description,0, sizeof(description));
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
        
        /* we assumed, we are logged in but not really have a user id yet */
        //newProduct.hostId = loginUser->idUser;
        //newProduct.host = loginUser;
        
        if(validate == 1)
        {
            insertProduct(newProduct,loginUser);
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
    
    return 1;
}

int personalInfo()
{
    char buffer[32];
    int choice = 0;
    
    printf("======================== Personal Info ======================\n\n");
    printf("          1. Email: %s                                  \n",loginUser->email);
    printf("          2. Password: %s                               \n",loginUser->password);
    printf("          3. Full name (No title): %s                   \n",loginUser->name);
    printf("          4. Address: %s                                \n",loginUser->address);
    printf("          5. Phone Number (Thai): %s                    \n",loginUser->phoneNumber);
    printf("          6. Bank Account: %s                           \n",loginUser->bankAccNumber);
    printf("          7. Back to homepage                           \n\n");
    printf("=============================================================\n\n");
   
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

int editInfo(int choice)
{
    char buffer[64];
    char email[64];
    char password[64];
    char name[64];
    char address[64];
    char phoneNumber[64];
    char bankAccNumber[64];
    int validate = 0;
    
    switch (choice) {
        case 1:
            do
            {
                printf("\n");
                memset(email,0, sizeof(email));
                printf("Email: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", email);
                //validate = validateEmail(email);
                validate = 1;
                if(validate == 1)
                {
                    strcpy(loginUser->email,email);
                    break;
                }
            }while (validate != 1);
            break;
        case 2:
            do
            {
                printf("\n");
                memset(password,0, sizeof(password));
                printf("Please enter password following to these rules\n");
                printf("- At least 8 characters long and no longer than 12 characters\n");
                printf("- MUST contain at least one upper case letter\n");
                printf("- MUST contain at least one lower case letter\n");
                printf("- MUST contain at least two digits\n");
                printf("- MUST contain at least one of the following special characters: ? @ %% $ #\n");
                printf("- MUST not contain any other special characters not in the list above\n");
                printf("Password: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", password);
                validate = validatePassword(password);
                if(validate == 1)
                {
                    strcpy(loginUser->password,password);
                    break;
                }
            }while (validate != 1);
            break;
        case 3:
            do
            {
                printf("\n");
                memset(name,0, sizeof(name));
                printf("Full name (No title): ");
                fgets(name,sizeof(name),stdin);
                validate = validateName(name);
                if(validate == 1)
                {
                    printf("\t\t%s\n",name);
                    strcpy(loginUser->name,name);
                    break;
                }
            }while (validate != 1);
            break;
        case 4:
            do
            {
                printf("\n");
                memset(address,0, sizeof(address));
                printf("Please enter address following to these rules\n");
                printf("- Begins with a number (the house number) which can include a slash, e.g. “34/12”\n");
                printf("but must have at least one digit before and one digit after the slash.\n");
                printf("- Next a street name which can include numbers as well as letters\n");
                printf("- Next an optional label “Road”, “Street” or “Lane”\n");
                printf("- a postal code must be five digits and which must begin with “10”\n");
                printf("Address (Bangkok): ");
                fgets(address,sizeof(address),stdin);
                validate = validateAddress(address);
                if(validate == 1)
                {
                    strcpy(loginUser->address,address);
                    break;
                }
            }while (validate != 1);
            break;
        case 5:
            do
            {
                printf("\n");
                memset(phoneNumber,0, sizeof(phoneNumber));
                printf("Phone Number (Thai): ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", phoneNumber);
                validate = validatePhoneNumThai(phoneNumber,buffer);
                if(validate == 1)
                {
                    strcpy(loginUser->phoneNumber,phoneNumber);
                    break;
                }
            }while (validate != 1);
            break;
        case 6:
            do
            {
                printf("\n");
                memset(bankAccNumber,0, sizeof(bankAccNumber));
                printf("Bank Account: ");
                fgets(buffer,sizeof(buffer),stdin);
                sscanf(buffer,"%s", bankAccNumber);
                validate = validateBankAcc(bankAccNumber,buffer);
                if(validate == 1)
                {
                    strcpy(loginUser->bankAccNumber,bankAccNumber);
                    break;
                }
            }while (validate != 1);
            break;
        default:
            break;

    }
    
    return 0;
}

int homePage()
{
    char buffer[32];
    int choice = 0;

    printf("========================== Homepage =========================\n\n");
    printf("                       1.Browse                              \n");
    printf("                       2.Bid history                         \n");
    printf("                       3.Sale history                        \n");
    printf("                       4.Create new auction                  \n");
    printf("                       5.Edit personal info                  \n");
    printf("                       6.Log out                             \n\n");
    printf("=============================================================\n\n");
    
    do
    {
        choice = 0;
        printf("What do you want to do? ");
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
    
    buildData();   /* build data structure by reading data in the file */
    
    printf("=============================================================\n");
    printf("                     ONLINE AUCTION PROGRAM                  \n");
    printf("=============================================================\n\n");
    do
    {
        choice = logInMenu();
        
        if (choice == 1)
        {
            choice = loginInput();
            do
            {
                if(choice == LOGIN)
                {
                    choice = homePage();
                    switch (choice) {
                        case 1:
                            choice = browse();
                            if(choice != 4)
                            {
                                subBrowse(choice);
                            }
                            choice = 1;
                            break;
                        case 2:
                            bidHistory();
                            choice = 1;
                            break;
                        case 3:
                            saleHistory();
                            choice = 1;
                            break;
                        case 4:
                            if (createAuction() == 1)
                            {
                                choice = 1;
                            }
                            break;
                        case 5:
                            choice = personalInfo();
                            editInfo(choice);
                            choice = 1;
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
            closeProgram();
            break;
        }
        
    }while (choice != 4);
    
    return 0;
}
