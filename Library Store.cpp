#include <iostream>
#include<string>
#include<stdlib.h>
#include <fstream>
#include <bits/stdc++.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
/*
****************************************Team Members***************************
                        1-Eslam Elsayed ElRamikh
                        2-Maram waleed
                        3-Nagwa ebrahem abdulbaset
                        4-Nayra samy
                        5-Amr Essam AL Sayed


*/
using namespace std ;

int num_book = 0 ;
int num_book_Del = 0 ;
int num_users = 0;
string logged_user="";
int logged_in = 0;

struct Book
{
    int book_id ;
    string book_title ;
    string book_author ;
    int publish_year ;
};

struct User
{
    string user_Name ;
    string Password ;
};
Book library_books [100];
Book library_books_After_Delete [100];
User library_users [100];

void Write_BookFile (int id , string title , string author , int year )
{
    ofstream MyFile;
    MyFile.open("library_books.txt", std::ios_base::app);
    MyFile << "\n"<<"ID : "<< id << "\n";
    MyFile << "Book Title : "<< title << "\n";
    MyFile << "Book Author : "<< author << "\n";
    MyFile << "Book Publish Year : "<< year << "\n";
    MyFile << "_______________________" ;
}
void Read_BookFile ()
{
    string myText;
    ifstream MyReadFile("library_books.txt");
    while (getline (MyReadFile, myText))
        cout << myText << "\n";
    MyReadFile.close();
}
void Load_Books()
{
    string myText ; string strID = "" ;string strYear = "" ; string title = "" ; string author = "" ;
    int id = 0 ; int year = 0;

    ifstream MyReadFile("library_books.txt");
    while (getline (MyReadFile, myText))
        if ( myText[0] != '_' )
        {
            if ( myText[0] == 'I' )
            {
                strID = myText ;
                id = stoi( strID.substr(5,strID.length()) ) ;
                //cout << id << "\n";
            }
            if ( myText[5] == 'T' )
            {
                title = myText ;
                title = title.substr(13,title.length()) ;
                //cout << title << "\n";
            }
            if ( myText[5] == 'A' )
            {
                author = myText ;
                author = author.substr(14,author.length()) ;
                //cout << author << "\n";
            }
            if ( myText[5] == 'P' )
            {
                 strYear = myText ;
                year = stoi( strYear.substr(20,strYear.length()) ) ;
                //cout << year << "\n";
            }
            library_books[num_book] = {id , title , author , year} ;
        }
        else {  num_book = num_book + 1 ;}

    MyReadFile.close();
}
void Add_Book ()
{
    int book_id = 0 ;
    int book_year = 0 ;
    string book_title = "";
    string book_author = "";

    cout << "Enter Book ID : " ;
    cin >> book_id ;

    cout << "Enter Book Title : " ;
    getline(cin >> ws, book_title) ;

    cout << "Enter Book Author : " ;
    getline(cin >> ws, book_author );

    cout << "Enter Book Publish Year : " ;
    cin >> book_year ;
    Load_Books();
    int exist = 0 ;
    for (int i = 0 ; i<num_book ; i++)
    {
        if ( library_books[i].book_id != book_id ) { exist = 0;}
        else { exist = 1; }
    }
    if (exist == 0)
        { Write_BookFile (book_id , book_title , book_author , book_year ) ; }
    else {cout<< "\nTHIS BOOK IS ALREADY EXIST !\n";}
}

void Remove_Book (int id)
{
    Load_Books() ;
    bool del = false ;
    for (int i =0; i<num_book ; i++)
    {
        if ( library_books[i].book_id != id )
            {
                library_books_After_Delete[num_book_Del].book_id = library_books[i].book_id ;
                library_books_After_Delete[num_book_Del].book_title = library_books[i].book_title;
                library_books_After_Delete[num_book_Del].book_author = library_books[i].book_author ;
                library_books_After_Delete[num_book_Del].publish_year = library_books[i].publish_year ;
                num_book_Del = num_book_Del + 1 ;
                del = true ;
            }
        else { continue;  del = false; }
    }
    if (del)
        { num_book = num_book - 1 ; }
    ofstream MyFile("library_books.txt");
    for (int j=0 ; j<num_book ; j++)
        {
            if (j > 0) { MyFile << "\n" ; }
            MyFile << "ID : "<< library_books_After_Delete[j].book_id << "\n";
            MyFile << "Book Title : "<< library_books_After_Delete[j].book_title << "\n";
            MyFile << "Book Author : "<< library_books_After_Delete[j].book_author << "\n";
            MyFile << "Book Publish Year : "<< library_books_After_Delete[j].publish_year << "\n";
            MyFile << "_______________________" ;
        }
    MyFile.close();
}
void Search_with_id( int id )
{
    Load_Books() ;
    bool findbook = false ;
    for (int i =0; i<num_book ; i++)
    {
        if ( library_books[i].book_id == id )
            {
                cout << "ID : " << library_books[i].book_id << endl ;
                cout << "Book Title : " << library_books[i].book_title << endl;
                cout << "Book Author : " << library_books[i].book_author << endl;
                cout << "Book Publish Year : " << library_books[i].publish_year << endl;
                findbook = true ;
            }
        else
            {
                findbook = false ;
            }
    }
    if (!findbook) { cout << "This ID is not Found !" << endl ; }

}


void Search_with_Year( int year )
{
    Load_Books() ;
    int findbook = 0 ;
    for (int i =0; i<num_book ; i++)
    {
        if ( library_books[i].publish_year == year )
            {
                cout << "ID : " << library_books[i].book_id << endl ;
                cout << "Book Title : " << library_books[i].book_title << endl;
                cout << "Book Author : " << library_books[i].book_author << endl;
                cout << "Book Publish Year : " << library_books[i].publish_year << endl;
                findbook = 1 ;
                break ;
            }
        else
            {
                findbook = 0 ;
            }
    }
    if ( findbook == 0) { cout << "This Year is not Found !" << endl ; }

}

void Search_with_Title( string title )
{
    Load_Books() ;
    int findbook = 0 ;
    for (int i =0; i<num_book ; i++)
    {
        if ( library_books[i].book_title == title )
            {
                cout << "ID : " << library_books[i].book_id << endl ;
                cout << "Book Title : " << library_books[i].book_title << endl;
                cout << "Book Author : " << library_books[i].book_author << endl;
                cout << "Book Publish Year : " << library_books[i].publish_year << endl;
                findbook = 1 ;
                break ;
            }
        else
            {
                findbook = 0 ;
            }
    }
    if ( findbook == 0) { cout << "This Title is not Found !" << endl ; }

}

void Search_with_Author( string author )
{
    Load_Books() ;
    int findbook = 0 ;
    for (int i =0; i<num_book ; i++)
    {
        if ( library_books[i].book_author == author )
            {
                cout << "ID : " << library_books[i].book_id << endl ;
                cout << "Book Title : " << library_books[i].book_title << endl;
                cout << "Book Author : " << library_books[i].book_author << endl;
                cout << "Book Publish Year : " << library_books[i].publish_year << endl;
                findbook = 1 ;
                break ;
            }
        else
            {
                findbook = 0 ;
            }
    }
    if ( findbook == 0) { cout << "This Author is not Exist !" << endl ; }

}

// User functions

//Write a user in the file
void Write_User ( string user_Name , string Password )
{
    ofstream MyFile;
    MyFile.open("library_Users.txt", std::ios_base::app);
    MyFile << "\n"<<"Username : "<< user_Name << "\n";
    MyFile << "Password : "<< Password << "\n";
    MyFile << "_______________________" ;
}

//fetch users from file into Users array
void Load_Users()
{
    string myText ; string user = "" ;string Pass = "" ;
    int id = 0 ; int year = 0;

    ifstream MyReadFile("library_Users.txt");
    while (getline (MyReadFile, myText))
        if ( myText[0] != '_' )
        {
            if ( myText[0] == 'U' )
            {
                user = myText ;
                user = user.substr(11,user.length()) ;
            }
            if ( myText[0] == 'P' )
            {
                Pass = myText ;
                Pass = Pass.substr(11,Pass.length()) ;
            }

            library_users[num_users] = {user , Pass } ;

        }
        else {  num_users = num_users + 1 ;}

    MyReadFile.close();
}

//Add a new user to registered users (register)
void Add_User ()
{
    string username = "";
    string password = "";
    cout << "Enter Username : " ;
    getline(cin >> ws, username) ;
    cout << "Enter Password : " ;
    getline(cin >> ws, password );

    Load_Users();
    int exist = 0 ;
    for (int i = 0 ; i<num_users ; i++) //checking for terminate duplications(Constraint)
            {
                if ( library_users[i].user_Name != username )
                    {
                        exist = 0;
                    }
                else
                    {
                         exist = 1;
                         break;
                    }
            }
            if (exist == 0)
                {
                    Write_User (username , password );
                    cout<<"\n Successfully Added User\n";
                }
            else {cout<< "\nThis USER IS ALREADY EXIST !\n";}
}




//Removing user from Registered users
void Remove_User ()
{   string user ; string pass; int x;
    Load_Users() ;
    cout<<"Please enter the USERNAME you want to delete : ";
    cin>>user;
    cout<<"Please enter the Password for that user to confirm  : ";
    cin>>pass;
    bool exist = false ;
                for (int i =0; i<num_users ; i++) //Check if this user is exist in our list
                {
                                if ( library_users[i].user_Name == user   &&  library_users[i].Password == pass)
                                    {
                                          exist = true ;
                                            x = i ; //saving it's position
                                            break ;
                                    }
                    else { continue; }
                }
    if (exist)
        {
            num_users -=  1; //minimizing the array of users by 1

                for (int i=x; i<num_users; i++) //Overwrite this element by it's next element and so on to the end of array size (Traversal)
                {
                    library_users[i] = library_users[i+1];
                }


            ofstream MyFile("library_Users.txt");
            ofstream temp;
            temp.open("temp.txt", std::ios_base::app);     //creating a temporary file to save the new data (after deletion)

                for(int i=0;i<num_users;i++)//writing from the array into the temp file
                {


                            temp << "\n"<<"Username : "<< library_users[i].user_Name << "\n";
                            temp << "Password : "<< library_users[i].Password << "\n";
                            temp << "_______________________" ;
                }

                        MyFile.close();
                        temp.close();
                        remove("library_Users.txt"); //delete the origin file
                        rename("temp.txt", "library_Users.txt"); //rename the temp file with the original name
                        MyFile.close();
        }else
                        {
                                cout<<"Invalid Username or Password !!";

                        }
}

void login()
{   bool exist = false ;
    Load_Users();
    string user ; string pass;
    cout<<"Please enter your Username : ";
    cin>>user;
    cout<<"Please enter your Password : ";
    cin>>pass;
                    if(logged_in == 0) // if there is not a user logged in yet
                    {
                        for(int i=0; i<num_users;i++)   //Authentication Check!
                        {
                            if(library_users[i].user_Name == user   &&  library_users[i].Password == pass)
                                {
                                        cout<<"Logged in Successfully"<<endl;
                                        cout<<"\t\t\t\t\t\tWelcome\t "<<user<<endl;;
                                                logged_user=user;
                                                logged_in = 1 ;
                                                exist = true;
                                                break;

                                }
                        }
                        if(!exist){cout<<"Invalid Username or Password \n Try to register first !"<<endl;}

                    }else{cout<<"You already logged in "<<endl;;}

}
int main ()
{


    int choice;
    cout<<"********************* Welcome To Library Management System ********************"<<endl;
    if(logged_user !=""){cout<<"\t\tHello\t"<<logged_user<<endl;}
    while(1)
    {
        cout<<"What would you want me to do ?"<<endl;
        cout<<"1. Register"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"3. View all Books"<<endl;
        cout<<"4. Search Book by Title"<<endl;
        cout<<"5. Add Book"<<endl;
        cout<<"6. Remove Book"<<endl;
        cout<<"7. Remove User"<<endl;
        cout<<"8. Exit"<<endl;
        cin>>choice;
        if(choice == 1)
        {
           Add_User();
        }
        else if(choice == 2)
        {
            login();
        }
        else if(choice == 3)
        {
            Read_BookFile();
        }
        else if(choice == 4)

        {
            string s;
             cin>>s;
            Search_with_Title(s);
        }
        else if(choice == 5)
        {
            Add_Book();
        }
        else if(choice == 6)
        {   int x;
            cout<<"Enter the Book ID that will be removed"<<endl;
            cin>>x;
            Remove_Book(x);
        }
        else if(choice == 7)
        {
            Remove_User();
        }
        else if(choice == 8)
        {
           cout<<"Thank You for using our software"<<endl<<"Have a Nice Day !"<<endl;
           break;
        }
        else
        {
            main();
            break;
        }
    }













   /* Read_BookFile ();
    int x;
    cin>> x;
    Remove_Book(x);
    Read_BookFile();*/

    //Add_User();
    //Add_User();

    // Add_User();
    // Add_User();
    //Remove_User();

    //Read_BookFile();
    //Add_User();
    //cout<<endl;
    //cout<<num_users;
    //Add_Book () ;
    //Remove_Book (407) ;
    //Write_User("Ramikh","123");
    //Load();
    //Search_with_id(999);
    //Search_with_Year(1975);
    //Search_with_Title("title 2") ;
    //Search_with_Author("author 3");

    return 0;
}
