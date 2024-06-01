#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
struct User{
    std::string username;
    std::string password; 

};
struct Transaction{
    std::string date;
    std::string category;
    std::string type;
    double amount;
     };

    class financeManager{
       User currentUser;
       std::vector<Transaction> transaction;
    public:
    bool Login();
    void registerUser();
    void addTransaction();
    void viewTransaction();
    void generateReport();
    void saveData();
    void loadData();
    
     };
   

    bool financeManager::Login(){

        std::cout<<"Enter username:"<<std::endl;
        std::cin>>currentUser.username;
        std::cout<<"Enter password:"<<std::endl;
        std::cin>>currentUser.password;

        std::ifstream userFile("users.txt");
        std::string name,password;
        bool loginSuccess = false;
        while(userFile>>name>>password){
            if(currentUser.username==name && currentUser.password==password){
                std::cout<<"Login successfull."<<std::endl;
                loginSuccess = true;
                break;


            }
            
        }
                if(!loginSuccess){

                std::cout<<"Invalid username or password."<<std::endl;
            }
            

   return loginSuccess;

    }
   void financeManager::registerUser(){
    std::cout<<"Enter a new username."<<std::endl;
    std::cin>>currentUser.username;
    std::cout<<"Enter a new password."<<std::endl;
    std::cin>>currentUser.password;


    std::ofstream userFile("users.txt",std::ios::app);
    userFile<<currentUser.username<<" "<<currentUser.password<<std::endl;
    std::cout<<"Registration Successfull."<<std::endl;

    }
    
    void financeManager::addTransaction(){
        Transaction t;
        std::cout<<"Enter Date (DD,MM,YYYY):";
        std::cin>>t.date;
        std::cout<<"Enter Categoray:"<<std::endl;
        std::cin>>t.category;
        std::cout<<"Enter Type(income/expense):"<<std::endl;
        std::cin>>t.type;
        std::cout<<"Enter Amount:"<<std::endl;
        std::cin>>t.amount;
        transaction.push_back(t);
        std::cout<<"Transaction added  successfully."<<std::endl;

    }
void financeManager::viewTransaction(){
    std::cout<<"Date    |Category     |Type     |Amount"<<std::endl;
    std::cout<<"---------------------------------------"<<std::endl;
    for(auto &t :transaction){
        std::cout<<t.date<<"|"<<t.category<<"|"<<t.type<<"|"<<"|"<<t.amount<<std::endl;

    }
}
void  financeManager::saveData(){
    std::ofstream transactionFile(currentUser.username+ "_transaction.txt");
    for(auto &t:transaction){ 
        transactionFile<<t.date<<" "<<t.category<<" "<<t.type<<" "<<t.amount<<std::endl;


    }

}

void financeManager::loadData(){
transaction.clear();
std::ifstream transactionFile(currentUser.username+"_transaction.txt");
//ye yahan Trans q kre hen dont know find out
Transaction t;
while(transactionFile>> t.date >> t.category >> t.type >> t.amount){
    transaction.push_back(t);
}
}
void financeManager::generateReport(){
    double totalIncome=0;
    double totalExpense=0;
    for(auto & t: transaction){
        if(t.type=="income"){
            totalIncome+=t.amount;
        }
        else if(t.type=="expense"){
            totalExpense+=t.amount;
        }

    }
    double netSaving=totalIncome- totalExpense;
    std::cout<<"Total Income."<<totalIncome<<std::endl;
    std::cout<<"Total Expense."<<totalExpense<<std::endl;
    std::cout<<"Net Savings."<<netSaving<<std::endl;


}
 void displayMenu() {
    std::cout << "1. Add Transaction." << std::endl;
    std::cout << "2. View Transactions." << std::endl;
    std::cout << "3. Generate Report." << std::endl;
    std::cout << "4. Save and Exit." << std::endl;
    std::cout << "Enter your choice: ";
}
int main (){
    
    financeManager manager;
    int choice;
    std::cout<<"1.Login."<<std::endl;
    std::cout<<"2.Register."<<std::endl;
    std::cin>>choice;
    if(choice ==1){
        while(!manager.Login()){
            return 1;
        }

    }
    else if (choice==2){
        manager.registerUser();
        if(!manager.Login()){
            return 1;
        }
    }
    else {
        std::cout<<"Invalid choice. "<<std::endl;
      
       return 0;
     
        
    }


    manager.loadData();
    while (true) {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                manager.addTransaction();
                break;
            case 2:
                manager.viewTransaction();
                break;
            case 3:
                manager.generateReport();
                break;
            case 4:
                manager.saveData();
                std::cout << "Data saved. Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}


