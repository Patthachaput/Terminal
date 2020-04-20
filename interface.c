/*
 *
 *
 *
 *
 *
 *
 *  Project CPE111 Data structure - TEAM TERMINAL
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "validate.h"

#define NLOGIN 0
#define LOGIN 1
#define GUEST 2


int loginStatus = 0; /* 0 for not log in, 1 for login with account, 2 for guest */

int logInMenu()
{
    char buffer[32];
    int choice = 0;
    
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
        validate = 1;
        
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
    
    do
    {
        printf("Please enter your infomation\n");
        printf("Email: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%s", email);
    
        do
        {
            memset(password,0, sizeof(password));
            printf("Password: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", password);
            validate = validatePassword(password);
            if(validate == 1)
            {
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
                break;
            }
        }while (validate != 1);
        
        if(validate == 1)
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

void createAuction()
{
    char buffer[64];
    char buffer2[64];
    char name[64];
    char description[120];  /*product description*/
    int category;           /*fixed category*/
    char dateClose;
    double minbid;          /*minimum bid price*/
    //int hostId;             /* user who created this product */
    //USER_T* host;
    int validate = 0;
    
    do
    {
        printf("Please enter the product infomation\n");
        printf("Name: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", name);
        
        memset(name,0, sizeof(password));
        printf("Description: ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%[^\n]", description);
        
        do
        {
            memset(category,0, sizeof(category));
            printf("Category: \n");
            printf("\t1.Home & Garden\n");
            printf("\t2.Collectibles\n"};
            printf("\t3.Sport\n");
            printf("\t4.Electronic\n");
            printf("\t5.Fashion\n");
            printf("\t6.Health & Beauty\n");
            printf("\t7.Motor\n");
            printf("Choose your category\n");
            fgets(buffer,sizeof(buffer),stdin);
                   sscanf(buffer,"%d", category);
            if((choice > 7)||(choice < 1))
            {
               validate = 0;
               printf("Invalid choice! please try again\n\n");
            }
            else
            {
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(buffer2,0, sizeof(buffer2));
            memset(minBid,0, sizeof(minBid));
            printf("Minimum Bid: ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%s", buffer2);
            validate = 0;
            if(strlen(buffer2) == checkDigits(buffer2))
            {
                sscanf(buffer2,"%lf",minBid);
                validate = 1;
                break;
            }
        }while (validate != 1);
        
        do
        {
            memset(dateOpen,0, sizeof(dateOpen));
            printf("Date Close (dd-mm-yyyy hh:tt) : ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%[^\n]", dateOpen);
            validate = validateBankAcc(dateOpen);
            if(validate == 1)
            {
                break;
            }
        }while (validate != 1);
        
        if(validate == 1)
        {
            printf("\nThis is your product information\n");
            printf("\tName: %s\n",email);
            printf("\tDescription: %s\n",password);
            printf("\tFull name (No title): %s\n",name);
            printf("\tAddress: %s\n",address);
            printf("\tPhone Number (Thai): %s\n",phoneNumber);
            printf("\tBank Account: %s\n",bankAccNumber);
            printf("Successful registered!\n\n");
            break;
        }
        
    }while (validate != 1);
}

void personalInfo()
{
    char buffer[32];
    int choice = 0;
    
    printf("=========== Personal Info =========\n\n");
    printf("\t1. Email: %s\n",email);
    printf("\t2. Password: %s\n",password);
    printf("\t3. Full name (No title): %s\n",name);
    printf("\t4. Address: %s\n",address);
    printf("\t5. Phone Number (Thai): %s\n",phoneNumber);
    printf("\t6. Bank Account: %s\n",bankAccNumber);
    printf("\t7. Back to homepage"
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
