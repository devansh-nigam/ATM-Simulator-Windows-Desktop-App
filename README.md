# ATM-Simulator-Windows-Desktop-App

ATM Simulator. This has to simulate most of the activities which happen at an ATM. It is assumed that the account details of all the account holders would be stored in a file which gets used by this simulator.

* Log in using a username and a password. 
* Look at the balance statement 
* Withdraw money - the balance should be checked and updated.
* Allow the user to change the password (PIN) 
* Deposit money

## Description

An Automated Teller Machine(ATM) is a computer based machine, connected to a network, that offers some basic functions to user as to access their bank accounts, check their balance, transfer and retrieval of money. ATMs are convenient, allowing consumers to perform quick, self-serve transactions from everyday banking like deposits and withdrawals to more complex transactions like bill payments and transfers.

Here we need to simulate all activities of ATM like Login, Various Transaction, etc.
To achieve this we have used Win32 API and concepts of C language. First the person should insert the card and enter the pin to login and the details of the account will be displayed on the parent/main window (previously saved data) and the transaction options arise these options are buttons which is by creating child window of predefined dimensions, and by selecting an option we can do atm transactions and the balance will be updated with the help of c language.

## Technologies

Project is created with:
* .NET Framework along with bits of C++ 
* Windows Win32 API
* Visual Studio Code

## Video 

![Algorithm schema](./images/schema.jpg)
