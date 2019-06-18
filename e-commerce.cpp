/*
An E-COMMERCE Application Created by Abishek.S (EE18B001), IITM
DATE : 18 June 2019
PURPOSE : For SPW Project
*/


/**HEADER FILES**/

#include<bits/stdc++.h>
#include<sys/ioctl.h>   //To get console screen width
#include<termios.h>     //To implement getch() function in Linux and MAC OS

#ifdef WINDOWS
#include<windows.h>
#else
#include<unistd.h>
#endif

/**MACROS**/

#define for0(i,n) for(ll i = 0;i < n;i++)
#define for1(i,n) for(ll i = 1;i<=n;i++)

using namespace std;

/**TYPEDEFs**/

typedef long long ll;
typedef vector<long long> vl;
typedef vector<pair<long long,long long> > vll;
typedef pair<long long,long long> pll;

/**GLOBAL VARIABLES**/

//Structure to get the width of the window

struct winsize w;

//Vector containing all possible characters an UserName can contain - namely :
//Lowercase and Uppercase English Alphabets (a-z) and (A-Z), numbers(0-9), and UnderScore(_)

vector<char> charList;

/**GENERAL USAGE FUNCTIONS**/

//getch() FUNCTION Implemented to work in Linux and Mac OS Systems

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

//Pause() Function Simply makes the screen wait for some character input from the user

void Pause(){
    cout<<"\n\n\n\t\tEnter any character to Proceed.....";
    cin.get();
}

//Clr_Scr() Function clears the screen window

void Clr_Scr(){
    #ifdef WINDOWS
        system("cls");
    #else
        system("clear");
    #endif
}

//This Function changes the window to our desired color - This hasn't been used in this Program, as it runs only on Windows

void Change_Color(string s){
	string a = "COLOR " + s;
    system(a.c_str());
}

//This Function displays a string on the left end of the window

void left_align(string s){
    cout.width(w.ws_col);cout<<std::left<<s<<"  \n";
}

//This function displays a string on the right end of the window

void right_align(string s){
    cout.width(w.ws_col);cout<<std::right<<s<<"  \n";
}

//This function displays a string at the center of the window

void center_align(string s){
    cout.width((w.ws_col/2) + (s.length()/2) + 1);
    cout<<s<<"\n";
    cout.width(w.ws_col);
}

//This Function makes the console unresponsive for a specified number of MilliSeconds

void SLEEP(int sleepMS){
	#ifdef WINDOWS
	    Sleep(sleepMS);
	#else
	    usleep(sleepMS*1000);
	#endif
}

/**CLASSES**/

//Item forms a class of objects which are going to be the Products sold/Listed in the Application

class Item{
    //DATA MEMBERS

  public:
	double Price;
	string Name;
	double Rating;
	string Seller;
	string Review;
    string Section;
    ll No_Raters;
	ll Views;
	ll stock;

    //CONSTRUCTORS

	Item(){
		Price = -1;Rating = 5;
		Views = stock = 0;
		Name = Review = Seller = "";
        Section = "";
        No_Raters = 0;
	}

	Item(string n,string s = "",double pr = -1){
		Price = pr;
		Rating = 5;
		Name = n;
		Seller = s;
		Review = "";
        Section = "";
		Views = stock = 0;
		No_Raters = 0;
	}

    // = OPERATOR OVERLOADED

    Item& operator= (const Item &u) {
  		Price = u.Price;
  		Name = u.Name;
  		Rating = u.Rating;
  		Seller = u.Seller;
  		Review = u.Review;
  		Section = u.Section;
  		No_Raters = u.No_Raters;
  		Views = u.Views;
  		stock = u.stock;
  		return *this;
  	}

    // << OPERATOR OVERLOADED

	friend ostream& operator<<(ostream& os, const Item& u)
	{
	    const size_t nameSize = u.Name.size(),sellSize = u.Seller.size(),revSize = u.Review.size(),secSize = u.Section.size();
	    os << nameSize <<" ";
	    os.write(u.Name.data(), nameSize);
	    os << '\n';
	    os << sellSize<<" ";
	    os.write(u.Seller.data(), sellSize);
	    os << '\n';
	    os << revSize<<" ";
	    os.write(u.Review.data(), revSize);
	    os << '\n';
	    os << secSize<<" ";
	    os.write(u.Section.data(), secSize);
	    os << '\n';
	    os << u.stock<<" ";
	    os << u.Rating <<" ";
	    os << u.Views <<" ";
	    os << u.Price <<" ";
	    os << u.No_Raters <<"\n";
	    return os;
	}

    // >> OPERATOR OVERLOADED

    friend istream& operator>>(istream& is, Item &u)
	{
		size_t nameSize = 0,sellSize = 0,revSize = 0,secSize = 0;
	    is >> nameSize;
	    is.ignore();
	    getline(is,u.Name,'\n');
	    is >> sellSize;
	    is.ignore();
	    getline(is,u.Seller,'\n');
	    is >> revSize;
	    is.ignore();
	    getline(is,u.Review,'\n');
	    is >> secSize;
	    is.ignore();
	    getline(is,u.Section,'\n');
	    is >> u.stock;
	    is >> u.Rating;
	    is >> u.Views;
	    is >> u.Price;
	    is >> u.No_Raters;
	    return is;
	}

    // == OPERATOR OVERLOADED

	bool operator == (const Item& x){
		return (Name == x.Name) && (Seller == x.Seller) && (Section == x.Section);
	}

};

/**COMPARATOR OBJECTS TO BE USED FOR THE HEAPS CONTAINING Items**/

struct cmp_price_inc{
	bool operator() (const Item& x,const Item& y){
	    return x.Price < y.Price;
	}
};

struct cmp_price_dec{
	bool operator() (const Item& x,const Item& y){
	    return x.Price > y.Price;
	}
};

struct cmp_rating_inc{
	bool operator() (const Item& x,const Item& y){
	    return x.Rating < y.Rating;
	}
};

struct cmp_rating_dec{
	bool operator() (const Item& x,const Item& y){
	    return x.Rating > y.Rating;
	}
};

struct cmp_views_inc{
	bool operator() (const Item& x,const Item& y){
	    return x.Views < y.Views;
	}
};

struct cmp_views_dec{
	bool operator() (const Item& x,const Item& y){
	    return x.Views > y.Views;
	}
};

/**CLASSES**/

//User represents the details of People who can login to the Application

class User{
    //DATA MEMBERS

  public:
  	string UsrName;
  	string Pwd;
    string Contact_No;
    string Address;
    string Name;
  	int isSeller;
  	ll ProdBought;
  	ll ProdSold;

    //CONSTRUCTOR

  	User(string u = "",string p = "",int i = 0){
  		UsrName = u;
  		Pwd = p;
  		isSeller = i;
  		Contact_No = "";
  		ProdBought = 0;
  		ProdSold = 0;
  		Address = "";
  		Name = "";
  	}

    // = OPERATOR OVERLOADED

  	User& operator= (const User &u) {
  		(this->UsrName) = (u.UsrName);
  	    (this->Pwd) = (u.Pwd);
  		this->isSeller = u.isSeller;
  		(this->Contact_No) = (u.Contact_No);
  		(this->Address) = (u.Address);
  		this->ProdBought = u.ProdBought;
  		this->ProdSold = u.ProdSold;
  		(this->Name) = (u.Name);
  		return *this;
  	}

    // << OPERATOR OVERLOADED

  	friend ostream& operator<<(ostream& os, const User& u)
	{
	    const size_t nameSize = u.Name.size(),addrSize = u.Address.size(),noSize = u.Contact_No.size(),usrSize = u.UsrName.size(),pwdSize = u.Pwd.size();
	    os << nameSize <<" ";
	    os.write(u.Name.data(), nameSize);
	    os << '\n';
	    os << addrSize<<" ";
	    os.write(u.Address.data(), addrSize);
	    os << '\n';
	    os << noSize<<" ";
	    os.write(u.Contact_No.data(), noSize);
	    os << '\n';
	    os << usrSize<<" ";
	    os.write(u.UsrName.data(), usrSize);
	    os << '\n';
	    os << pwdSize<<" ";
	    os.write(u.Pwd.data(), pwdSize);
	    os << '\n';
	    os << u.isSeller<<" ";
	    os << u.ProdBought<<" ";
	    os << u.ProdSold<<"\n";
	    return os;
	}

    // >> OPERATOR OVERLOADED

    friend istream& operator>>(istream& is, User &u)
	{
		size_t nameSize = 0,addrSize = 0,noSize = 0,usrSize = 0,pwdSize = 0;
	    is >> nameSize;
	    is.ignore();
	    getline(is,u.Name,'\n');
	    is >> addrSize;
	    is.ignore();
	    getline(is,u.Address,'\n');
	    is >> noSize;
	    is.ignore();
	    getline(is,u.Contact_No,'\n');
	    is >> usrSize;
	    is.ignore();
	    getline(is,u.UsrName,'\n');
	    is >> pwdSize;
	    is.ignore();
	    getline(is,u.Pwd,'\n');
	    is >> u.isSeller;
	    is >> u.ProdBought;
	    is >> u.ProdSold;
	    return is;
	}
};

//Accounts represents the Trie structure used to store the Usernames for providing Quick Access to their Details

class Accounts{
  public:
	map<char,Accounts*> next;
	Accounts* parent;
    int isUser;
    User usr;
    Accounts(int i = 0){
    	isUser = i;
    	for(auto ch : charList){
    		next[ch] = NULL;
    	}
        parent = NULL;
    }
};

//Site represents the main Class of the Program which combines all other Classes and Operates all functionalities of the Application

class Site{

  //DATA MEMBERS

  public:
  	map<string,vector<Item> > Products;
  	vector<Item*> Cart;
    Accounts* root;

    //CONSTRUCTOR

    Site(){
    	root = new Accounts();
    }

    //MEMBER FUNCTIONS

    //This Function facilitates viewing a particular Product

    void view_Product(User& u){
        Clr_Scr();
    	right_align("WELCOME "+u.Name);
    	center_align("E-MARKET");
    	Item temp;
    	cout<<"\n\n\t\tEnter the SECTION : ";
    	cin>>temp.Section;
    	cout<<"\n\n\t\tEnter the NAME of the Product : ";
    	cin.ignore();
    	getline(cin,temp.Name,'\n');
    	cout<<"\n\n\t\tEnter the SELLER NAME : ";
    	cin>>temp.Seller;
    	int there = 0;
    	Item* tmp;
    	for(auto &item : Products[temp.Section]){
    		if(item == temp){
    			item.Views++;
                tmp = &item;
                there = 1;
                break;
    		}
    	}
    	if(!there){
    		Clr_Scr();
    		cout<<"\a"<<flush;
    		cout<<"\n\n\t\t\tNo Such Product !!"<<flush;
    		SLEEP(2000);
    		Clr_Scr();
    	}
    	else{
    		Clr_Scr();
    		right_align("WELCOME "+u.Name);
    	 	center_align("E-MARKET SINGLE PRODUCT VIEW");
            cout<<"\n\t\tNAME : "<<tmp->Name;
            cout<<"\n\t\tSELLER : "<<tmp->Seller;
            cout<<"\n\t\tPRICE : "<<tmp->Price;
            cout<<"\n\t\tSTOCK : "<<tmp->stock;
            cout<<"\n\t\tRATING : "<<tmp->Rating;
            if(u.isSeller) {cout<<"\n\t\tNUMBER OF PEOPLE WHO BOUGHT THIS : "<<tmp->No_Raters;
            cout<<"\n\t\tNUMBER FO PEOPLE WHO VIEWED THIS PRODUCT : "<<tmp->Views;}
            cout<<"\n\n\t\tREVIEWS : ";
            char review[(tmp->Review).length()];
            strcpy(review,(tmp->Review).c_str());
            char* single_rev = strtok(review,"$");
            int count = 0;
            while(single_rev){
            	count++;
            	cout<<"\n\t\t\t"<<count+1<<". "<<single_rev;
            	single_rev = strtok(NULL,"$");
            }
            if(!count){
            	cout<<"\n\t\t\tNO REVIEWS TILL NOW !!";
            }
            cin.ignore();
            Pause();
            if(u.UsrName != "Guest"){
	            int want = 0;
	            center_align("Press 1 for YES, 0 for NO");
	            cout<<"\n\n\t\tDo you wish to add this Product to Cart ? : ";
	            cin>>want;
	            if(want){
	            	Cart.push_back(tmp);
	            	cout<<"\n\t\tSUCCESSFULLY ADDED TO CART !!"<<flush;
	                SLEEP(1000);
	            }
	            cout<<"\n\n\t\tDo you wish to RATE the Product : ";
	            cin>>want;
	            if(want){
	                double t;
	            	cout<<"\n\t\tEnter your RATING (A Number from 0 - 5) for this Product : ";
	            	cin>>t;
	            	tmp->Rating = (double)(tmp->No_Raters * tmp->Rating + t) / (tmp->No_Raters + 1);
	            	tmp->No_Raters++;
	            	cout<<"\n\t\tDo you wish to add a Review : ";
	                cin>>want;
	                if(want){
	                	string s;
	                	cout<<"\n\t\tEnter you Review fro this Product in a Line : ";
	                	cin.ignore();
	                	getline(cin,s,'\n');
	                	tmp->Review = tmp->Review + s + "$";
	                }
	            }
	        }
	        Clr_Scr();
		    cout<<"\n\n\t\t\tProceeding to the E-MARKET MENU."<<flush;
		    SLEEP(500);
		    cout<<".."<<flush;
		    SLEEP(750);
		    cout<<"..."<<flush;
		    SLEEP(500);
		    Clr_Scr();
    	}
    }

    //This Function shows the objects in Cart and we can Delete or Retain some and finally Buy them

    void View_Cart(User& u){
        Clr_Scr();
        right_align("WELCOME "+u.Name);
    	center_align(u.Name+"\'s CART");
    	cout<<"\n\n\t\tREVIEW YOUR ORDER : ";
        int count = 0;
        double Total_Price = 0;
        for0(i,Cart.size()){
        	Item I = *Cart[i];
            cout<<"\n\t\t"<<++count<<". NAME : "<<I.Name;
            cout<<"\n\t\t   SELLER : "<<I.Seller;
            cout<<"\n\t\t   PRICE : "<<I.Price;
            cout<<"\n\t\t   STOCK : "<<I.stock;
            cout<<"\n\t\t   RATING : "<<I.Rating;
            int cont = 0;
            cout<<"\n\n\t\tChoose 1 to CONTINUE, 0 to DELETE";
            cin>>cont;
            if(cont){
            	ll nop = 1e9+7;
            	while(nop > I.stock){
            	    cout<<"\n\t\tHow many stocks of the Product do you want ? :";
            	    cin>>nop;
            	    if(nop > I.stock){
            	    	cout<<"\n\t\tEntered number of Products not available";
            	    }
            	}
            	count += nop;
                Total_Price += (nop * I.Price);
                I.stock -= nop;
            }
            else{
            	Cart.erase(Cart.begin()+i);
            }
        }
        u.ProdBought += count;
        cout<<"\n\n\t\tTOTAL PAYABLE AMOUNT : "<<Total_Price;
        cin.ignore();
        Pause();
        Clr_Scr();
        cout<<"\n\n\t\t\tThank you for Shopping with us !!"<<flush;
        SLEEP(2500);
    }

    //This Function lists all Products or Products of a Particular Section which are filtered and ordered in user-chosen Manner

    void View_Products(User& u,string sect = ""){
    	Clr_Scr();
    	right_align("Welcome "+u.Name);
    	center_align("E-MARKET");
    	cout<<"\n\n";
        center_align("Press 1 for YES, 0 for NO");
    	int want = 0;
    	ll min_rating = 0,order = 0,mode = 0,max_price = 1e9+7;
    	cout<<"\n\n\t\tDo you wish to add a PRICE FILTER : ";
    	cin>>want;
    	if(want){
    		cout<<"\n\t\tEnter the MAXIMUM PRICE LIMIT : ";
    		cin>>max_price;
    	}
    	cout<<"\n\n\t\tDo you wish to add a RATING FILTER : ";
    	cin>>want;
    	if(want){
    		cout<<"\n\t\tEnter the MINIMUM RATING : ";
    		cin>>min_rating;
    	}
    	cout<<"\n\n\t\tOn what BASIS do you wish to order them : ";
    	cout<<"\n\t\t\t1. PRICE";
    	cout<<"\n\t\t\t2. RATING";
    	cout<<"\n\t\t\t3. NUMBER OF PEOPLE WHO VIEWED";
    	cout<<"\n\n\t\tEnter the choice number : ";
    	cin>>mode;
    	cout<<"\n\n\t\tDo you wish to order them in : ";
    	cout<<"\n\t\t\t1. INCREASING ORDER";
    	cout<<"\n\t\t\t2. DECREASING ORDER";
    	cout<<"\n\n\t\tEnter the choice number : ";
    	cin>>order;
    	Clr_Scr();
    	if(order == 1){
            if(mode == 1){
            	priority_queue<Item,vector<Item>,cmp_price_dec> h;
            	if(sect != ""){
            		for(auto item : Products[sect]){
            			if(item.Rating >= min_rating && item.Price <= max_price){
            				h.push(item);
            			}
            		}
            	}
            	else{
            		for(auto key_val : Products){
            			for(auto item : key_val.second){
            				if(item.Rating >= min_rating && item.Price <= max_price){
            					h.push(item);
            			    }
            			}
            		}
            	}
            	int t = 2,count = 0;
            	while(t == 2){
            		Clr_Scr();
            		center_align("E-MARKET PRODUCTS - " + sect);
                    cout<<"\n";
                    for(ll i = 1;i <= 5 && !h.empty();i++){
                    	Item I = h.top();
                    	cout<<"\n\t\t"<<++count<<". NAME : "<<I.Name;
                    	cout<<"\n\t\t   SELLER : "<<I.Seller;
                    	cout<<"\n\t\t   PRICE : "<<I.Price;
                    	cout<<"\n\t\t   STOCK : "<<I.stock;
                    	cout<<"\n\t\t   RATING : "<<I.Rating;
                    	cout<<"\n";
                        h.pop();
                    }
                    if(h.empty()){
                    	cout<<"\n\t\t----------END OF PRODUCTS----------";
                    }
                    cout<<"\n\tPRESS 1 for EXIT";
                    if(!h.empty()){
                    	cout<<"\n\tPRESS 2 for NEXT PAGE";
                    }
                    cout<<"\n\nEnter your choice of number : ";
                    cin>>t;
            	}
            }
            else if(mode == 2){
            	priority_queue<Item,vector<Item>,cmp_rating_dec> h;
            	if(sect != ""){
            		for(auto item : Products[sect]){
            			if(item.Rating >= min_rating && item.Price <= max_price){
            				h.push(item);
            			}
            		}
            	}
            	else{
            		for(auto key_val : Products){
            			for(auto item : key_val.second){
            				if(item.Rating >= min_rating && item.Price <= max_price){
            					h.push(item);
            			    }
            			}
            		}
            	}
            	int t = 2,count = 0;
            	while(t == 2){
            		Clr_Scr();
            		center_align("E-MARKET PRODUCTS - " + sect);
                    cout<<"\n";
                    for(ll i = 1;i <= 5 && !h.empty();i++){
                    	Item I = h.top();
                    	cout<<"\n\t\t"<<++count<<". NAME : "<<I.Name;
                    	cout<<"\n\t\t   SELLER : "<<I.Seller;
                    	cout<<"\n\t\t   PRICE : "<<I.Price;
                    	cout<<"\n\t\t   STOCK : "<<I.stock;
                    	cout<<"\n\t\t   RATING : "<<I.Rating;
                    	cout<<"\n";
                        h.pop();
                    }
                    if(h.empty()){
                    	cout<<"\n\t\t----------END OF PRODUCTS----------";
                    }
                    cout<<"\n\tPRESS 1 for EXIT";
                    if(!h.empty()){
                    	cout<<"\n\tPRESS 2 for NEXT PAGE";
                    }
                    cout<<"\n\nEnter your choice of number : ";
                    cin>>t;
            	}
            }
            else if(mode == 3){
            	priority_queue<Item,vector<Item>,cmp_views_dec> h;
            	if(sect != ""){
            		for(auto item : Products[sect]){
            			if(item.Rating >= min_rating && item.Price <= max_price){
            				h.push(item);
            			}
            		}
            	}
            	else{
            		for(auto key_val : Products){
            			for(auto item : key_val.second){
            				if(item.Rating >= min_rating && item.Price <= max_price){
            					h.push(item);
            			    }
            			}
            		}
            	}
            	int t = 2,count = 0;
            	while(t == 2){
            		Clr_Scr();
            		center_align("E-MARKET PRODUCTS - " + sect);
                    cout<<"\n";
                    for(ll i = 1;i <= 5 && !h.empty();i++){
                    	Item I = h.top();
                    	cout<<"\n\t\t"<<++count<<". NAME : "<<I.Name;
                    	cout<<"\n\t\t   SELLER : "<<I.Seller;
                    	cout<<"\n\t\t   PRICE : "<<I.Price;
                    	cout<<"\n\t\t   STOCK : "<<I.stock;
                    	cout<<"\n\t\t   RATING : "<<I.Rating;
                    	cout<<"\n";
                        h.pop();
                    }
                    if(h.empty()){
                    	cout<<"\n\t\t----------END OF PRODUCTS----------";
                    }
                    cout<<"\n\tPRESS 1 for EXIT";
                    if(!h.empty()){
                    	cout<<"\n\tPRESS 2 for NEXT PAGE";
                    }
                    cout<<"\n\nEnter your choice of number : ";
                    cin>>t;
            	}
            }
    	}
    	if(order == 2){
            if(mode == 1){
            	priority_queue<Item,vector<Item>,cmp_price_inc> h;
            	if(sect != ""){
            		for(auto item : Products[sect]){
            			if(item.Rating >= min_rating && item.Price <= max_price){
            				h.push(item);
            			}
            		}
            	}
            	else{
            		for(auto key_val : Products){
            			for(auto item : key_val.second){
            				if(item.Rating >= min_rating && item.Price <= max_price){
            					h.push(item);
            			    }
            			}
            		}
            	}
            	int t = 2,count = 0;
            	while(t == 2){
            		Clr_Scr();
            		center_align("E-MARKET PRODUCTS - " + sect);
                    cout<<"\n";
                    for(ll i = 1;i <= 5 && !h.empty();i++){
                    	Item I = h.top();
                    	cout<<"\n\t\t"<<++count<<". NAME : "<<I.Name;
                    	cout<<"\n\t\t   SELLER : "<<I.Seller;
                    	cout<<"\n\t\t   PRICE : "<<I.Price;
                    	cout<<"\n\t\t   STOCK : "<<I.stock;
                    	cout<<"\n\t\t   RATING : "<<I.Rating;
                    	cout<<"\n";
                        h.pop();
                    }
                    if(h.empty()){
                    	cout<<"\n\t\t----------END OF PRODUCTS----------";
                    }
                    cout<<"\n\tPRESS 1 for EXIT";
                    if(!h.empty()){
                    	cout<<"\n\tPRESS 2 for NEXT PAGE";
                    }
                    cout<<"\n\nEnter your choice of number : ";
                    cin>>t;
            	}
            }
            else if(mode == 2){
            	priority_queue<Item,vector<Item>,cmp_rating_inc> h;
            	if(sect != ""){
            		for(auto item : Products[sect]){
            			if(item.Rating >= min_rating && item.Price <= max_price){
            				h.push(item);
            			}
            		}
            	}
            	else{
            		for(auto key_val : Products){
            			for(auto item : key_val.second){
            				if(item.Rating >= min_rating && item.Price <= max_price){
            					h.push(item);
            			    }
            			}
            		}
            	}
            	int t = 2,count = 0;
            	while(t == 2){
            		Clr_Scr();
            		center_align("E-MARKET PRODUCTS - " + sect);
                    cout<<"\n";
                    for(ll i = 1;i <= 5 && !h.empty();i++){
                    	Item I = h.top();
                    	cout<<"\n\t\t"<<++count<<". NAME : "<<I.Name;
                    	cout<<"\n\t\t   SELLER : "<<I.Seller;
                    	cout<<"\n\t\t   PRICE : "<<I.Price;
                    	cout<<"\n\t\t   STOCK : "<<I.stock;
                    	cout<<"\n\t\t   RATING : "<<I.Rating;
                    	cout<<"\n";
                        h.pop();
                    }
                    if(h.empty()){
                    	cout<<"\n\t\t----------END OF PRODUCTS----------";
                    }
                    cout<<"\n\tPRESS 1 for EXIT";
                    if(!h.empty()){
                    	cout<<"\n\tPRESS 2 for NEXT PAGE";
                    }
                    cout<<"\n\nEnter your choice of number : ";
                    cin>>t;
            	}
            }
            else if(mode == 3){
            	priority_queue<Item,vector<Item>,cmp_views_inc> h;
            	if(sect != ""){
            		for(auto item : Products[sect]){
            			if(item.Rating >= min_rating && item.Price <= max_price){
            				h.push(item);
            			}
            		}
            	}
            	else{
            		for(auto key_val : Products){
            			for(auto item : key_val.second){
            				if(item.Rating >= min_rating && item.Price <= max_price){
            					h.push(item);
            			    }
            			}
            		}
            	}
            	int t = 2,count = 0;
            	while(t == 2){
            		Clr_Scr();
            		center_align("E-MARKET PRODUCTS - " + sect);
                    cout<<"\n";
                    for(ll i = 1;i <= 5 && !h.empty();i++){
                    	Item I = h.top();
                    	cout<<"\n\t\t"<<++count<<". NAME : "<<I.Name;
                    	cout<<"\n\t\t   SELLER : "<<I.Seller;
                    	cout<<"\n\t\t   PRICE : "<<I.Price;
                    	cout<<"\n\t\t   STOCK : "<<I.stock;
                    	cout<<"\n\t\t   RATING : "<<I.Rating;
                    	cout<<"\n";
                        h.pop();
                    }
                    if(h.empty()){
                    	cout<<"\n\t\t----------END OF PRODUCTS----------";
                    }
                    cout<<"\n\tPRESS 1 for EXIT";
                    if(!h.empty()){
                    	cout<<"\n\tPRESS 2 for NEXT PAGE";
                    }
                    cout<<"\n\nEnter your choice of number : ";
                    cin>>t;
            	}
            }
    	}
    	Clr_Scr();
        cout<<"\n\n\t\t\tProceeding to the E-MARKET MENU."<<flush;
        SLEEP(500);
        cout<<".."<<flush;
        SLEEP(750);
        cout<<"..."<<flush;
        SLEEP(500);
        Clr_Scr();
    }

    //This Function shows the main Market Menu where we can view and buy Products

    void Market(User &u){
        int mode = -1;
    	while(mode != 5){
    		Clr_Scr();
    	    right_align("WELCOME " + u.Name);
    	    center_align("E-MARKET - MENU");
            cout<<"\n\n";
            cout<<"\t\tChoose an option : \n";
            cout<<"\t\t\t1. View All Products\n";
            cout<<"\t\t\t2. View a Section of Products\n";
            cout<<"\t\t\t3. View Particular Product\n";
            cout<<"\t\t\t4. View Cart\n";
            cout<<"\t\t\t5. Return Back\n";
            cin>>mode;
            switch(mode){
            	case 1:{
            		View_Products(u);
            		break;
            	}
            	case 2:{
            		cout<<"\n\n\t\tEnter the Section of Products you wish to look at : ";
            		string tmp;
            		cin>>tmp;
            		View_Products(u,tmp);
            		break;
            	}
            	case 3:{
            		view_Product(u);
            		break;
            	}
                case 4:{
                	if(u.Name == "Guest" && u.UsrName == "Guest"){
                		Clr_Scr();
                		cout<<"\n\n\t\tLogin First to Use these Features"<<flush;
                        SLEEP(2500);
                	}
                	else{
                        View_Cart(u);
                    }
                    break;
                }
            	default:{
            		mode = 5;
            		break;
            	}
            }
    	}
    }

    //This Function shows the Profile Details of the User

    void View_Profile(User &u){
        Clr_Scr();
        right_align("WELCOME " + u.Name);
        center_align("PROFILE");
        cout<<"\n\n\t\tUSERNAME : "<<u.UsrName;
        cout<<"\n\t\tPASSWORD : ";
        for0(i,u.Pwd.length()) cout<<'*';
        cout<<"\n\t\tREGISTERED AS A SELLER : ";
        if(u.isSeller) cout<<"YES";
        else cout<<"NO";
        cout<<"\n\t\tADDRESS : "<<u.Address;
        cout<<"\n\t\tMOBILE NUMBER : "<<u.Contact_No;
        cout<<"\n\t\tPRODUCTS BOUGHT : "<<u.ProdBought;
        if(u.isSeller) cout<<"\n\t\tPRODUCTS SOLD : "<<u.ProdSold;
        cin.ignore();
        Pause();
        Clr_Scr();
    }

    //This Function allows to Update/Change certain Details of the User

    void Update_Profile(User &u){
        Clr_Scr();
        right_align("WELCOME " + u.Name);
        center_align("UPDATE/CHANGE PROFILE");
        cout<<"\n\n";
        center_align("Press 1 for YES, 0 for NO");
        int want = -1;
        cout<<"\n\n\t\tDo you wish to change your NAME ? : ";
        cin>>want;
        if(want){
            string n;
            cout<<"\n\t\tEnter your new NAME : ";
            cin>>n;
            u.Name = n;
        }
        cout<<"\n\n\t\tDo you wish to change your ADDRESS : ";
        cin>>want;
        if(want){
            string add;
            cout<<"\n\t\tEnter your new ADDRESS : ";
            cin.ignore();
            getline(cin,add,'\n');
            u.Address = add;
        }
        cout<<"\n\n\t\tDo you wish to change your MOBILE NUMBER ? : ";
        cin>>want;
        if(want){
            string num;
            cout<<"\n\t\tEnter your new MOBILE NUMBER : ";
            cin>>num;
            u.Contact_No = num;
        }
        cout<<"\n\n\t\tDo you wish to change your SELLER status ? : ";
        cin>>want;
        if(want){
            cout<<"\n\t\tDo you want to register as a seller (1 for YES, 0 for NO) : ";
            cin>>u.isSeller;
        }
        cout<<"\n\n\t\tDo you wish to change your PASSWORD ? : ";
        cin>>want;
        if(want){
            char ch;
            string p;
            cout<<"\n\t\tEnter your new PASSWORD ? : ";
            cin.ignore();
            while((ch = getch()) != '\n' && ch != ' '){
                p += ch;
                cout<<"*";
            }
            u.Pwd = p;
        }
        Clr_Scr();
        cout<<"\n\n\n\t\tGOING BACK."<<flush;
        SLEEP(500);
        cout<<".."<<flush;
        SLEEP(750);
        cout<<"..."<<flush;
        SLEEP(1000);
    }

    //This Function allows the user who is registered as a seller to list his Product for Sale

    void List_sale(User &u){
        Clr_Scr();
        right_align("WELCOME " + u.Name);
	    center_align("List Product for Sale");
	    Item tmp;
	    tmp.Seller = u.UsrName;
	    cout<<"\n\n\t\tEnter the section to which the product belongs : ";
	    cin>>tmp.Section;
	    cout<<"\n\t\tEnter Name of Product : ";
	    cin.ignore();
	    getline(cin,tmp.Name,'\n');
	    int taken = 0;
	    for(auto item : Products[tmp.Section]){
	    	if(item == tmp){taken = 1;break;}
	    }
	    if(taken){
	    	Clr_Scr();
	    	cout<<'\a'<<flush;
	    	cout<<"\n\n\t\t\tItem already listed by you for Sale !! Update it's INFO if you wish to ...."<<flush;
	    	SLEEP(3000);
	    }
	    else{
		    cout<<"\n\t\tEnter price of Product in Rs. : ";
		    cin>>tmp.Price;
		    cout<<"\n\t\tEnter number of pieces available : ";
	        cin>>tmp.stock;
	        u.ProdSold += tmp.stock;
	        Products[tmp.Section].push_back(tmp);
	        Clr_Scr();
	        cout<<"\n\n\n\t\t\tThank you for Listing your product on our website !!\n"<<flush;
	        SLEEP(2500);
	    }
	    Clr_Scr();
    }

    //This Function allows the Seller to Update/Change/Delete the Products he listed for Sale

    void Update_sale(User &u) {
    	Clr_Scr();
    	right_align("WELCOME "+u.Name);
	    center_align("Find Product on Sale");
	    int want = 0;
	    Item tmp;
	    tmp.Seller = u.UsrName;
	    cout<<"\n\n\t\tEnter the Original Product Section : ";
        cin>>tmp.Section;
        cout<<"\n\t\tEnter the Original Product Name : ";
        cin.ignore();
        getline(cin,tmp.Name,'\n');
        Item item;
        for0(i,Products[tmp.Section].size()){
        	item = Products[tmp.Section][i];
        	if(item.Name == tmp.Name && item.Seller == tmp.Seller){
        		tmp = item;
        		Products[tmp.Section].erase(Products[tmp.Section].begin()+i);
        		want = 1;
        		break;
        	}
        }
        if(want){
        	Clr_Scr();
        	right_align("WELCOME " + u.Name);
        	center_align("Update/Change Product on Sale INFO");
        	cout<<"\n";
            center_align("Press 1 for YES, 0 for NO");
            cout<<"\n\t\tDo you wish to Delete this product from the sale Listing ? :";
            cin>>want;
            if(!want){
                cout<<"\n\n\t\tDo you wish to change the product's NAME ? : ";
                cin>>want;
                if(want){
                	cout<<"\n\t\tEnter the new NAME : ";
                	cin.ignore();
                	getline(cin,tmp.Name,'\n');
                }
                cout<<"\n\n\t\tDo you wish to change the product's PRICE ? : ";
                cin>>want;
                if(want){
                	cout<<"\n\t\tEnter the new PRICE : ";
                	cin>>tmp.Price;
                }
                cout<<"\n\n\t\tDo you wish to change the product's NUMBER FO STOCKS ? : ";
                cin>>want;
                if(want){
                	cout<<"\n\t\tEnter the new NUMBER OF STOCKS : ";
                	cin>>tmp.stock;
                }
            }
            Clr_Scr();
            cout<<"\n\n\n\t\t\tProceeding to MAIN MENU."<<flush;
            SLEEP(500);
            cout<<".."<<flush;
            SLEEP(750);
            cout<<"..."<<flush;
            SLEEP(500);
        }
        else{
        	Clr_Scr();
        	cout<<'\a'<<flush;
        	cout<<"\n\n\t\t\tNO SUCH RECORD !!"<<flush;
        	SLEEP(2000);
        }
        Clr_Scr();
    }

    //This Function shows the Menu Screen the user/Seller sees after Logging In

    void MenuScreen(User &u,int status){
        int mode= -1;
        if(!status){
	        while(mode != 4){
	        	Clr_Scr();
	            right_align("WELCOME " + u.Name);
	            center_align("MAIN MENU");
	            cout<<"\n\n\t\tChoose an Option : \n\n";
	            cout<<"\t\t\t1. Go to the Products Section\n";
	            cout<<"\t\t\t2. View Profile\n";
	            cout<<"\t\t\t3. Update/Change Profile\n";
	            cout<<"\t\t\t4. Logout\n";
	            cin>>mode;
	            switch(mode){
	            	case 1:{
	            		Market(u);
	            		break;
	            	}
	            	case 2:{
	            		View_Profile(u);
	            		break;
	            	}
	            	case 3:{
	            		Update_Profile(u);
	            		break;
	            	}
	            	default:{
	            		mode = 4;
	            		break;
	            	}
	            }
	        }
	    }
	    else{
	    	while(mode != 6){
	        	Clr_Scr();
	            right_align("WELCOME " + u.Name);
	            center_align("MAIN MENU");
	            cout<<"\n\n\t\tChoose an Option : \n\n";
	            cout<<"\t\t\t1. Go to the Products Section\n";
	            cout<<"\t\t\t2. View Profile\n";
	            cout<<"\t\t\t3. Update/Change Profile\n";
	            cout<<"\t\t\t4. List Product For Sale\n";
	            cout<<"\t\t\t5. Update/Change Product on Sale INFO\n";
	            cout<<"\t\t\t6. Logout\n";
	            cin>>mode;
	            switch(mode){
	            	case 1:{
	            		Market(u);
	            		break;
	            	}
	            	case 2:{
	            		View_Profile(u);
	            		break;
	            	}
	            	case 3:{
	            		Update_Profile(u);
	            		break;
	            	}
	            	case 4:{
	            		List_sale(u);
	            		break;
	            	}
	            	case 5:{
	            		Update_sale(u);
	            		break;
	            	}
	            	default:{
	            		Cart.clear();
	            		mode = 6;
	            		break;
	            	}
	            }
	        }
	    }
    }

    //This Function shows the LoginScreen for the User/Seller to Log In

    void LoginScreen(int mode){
    	Clr_Scr();
        if(mode){
            cout<<"\n\n";
            center_align("SELLER LOGIN");
        }
        else{
            cout<<"\n\n";
            center_align("USER LOGIN");
        }
        cout<<"\n\n";
        string u,p="";
        cout<<"\t\t\tUSERNAME : ";
        cin>>u;
        cout<<"\t\t\tPASSWORD : ";
        char ch;
        cin.ignore();
        while((ch = getch()) != '\n' && ch != ' '){
            p += ch;
            cout<<"*";
        }
        Clr_Scr();
        Accounts* a = find(u);
        if(a && a->isUser && p == (a->usr).Pwd){
        	if((a->usr).isSeller && mode){
		        cout<<"\n\n\t\tLogging In "<<flush;
		        SLEEP(500);
		        cout<<"."<<flush;
		        SLEEP(1000);
		        cout<<".."<<flush;
		        SLEEP(1000);
		        cout<<"..."<<flush;
		        SLEEP(1000);
		        Clr_Scr();
		        MenuScreen(a->usr,1);
	        }
	        else if(!mode){
	        	cout<<"\n\n\t\tLogging In "<<flush;
		        SLEEP(500);
		        cout<<"."<<flush;
		        SLEEP(1000);
		        cout<<".."<<flush;
		        SLEEP(1000);
		        cout<<"..."<<flush;
		        SLEEP(1000);
		        Clr_Scr();
		        MenuScreen(a->usr,0);
	        }
	        else{
	        	cout<<"\a"<<flush;
	        	cout<<"\n\n\t\tThe entered user is not a registered seller\n"<<flush;
	        	SLEEP(2000);
	        }
        }
        else{
        	cout<<"\a"<<flush;
        	cout<<"\n\n\t\tNo Such User"<<flush;
        	SLEEP(2000);
        }
    }

    //This Function inserts a new User in the Trie Structure

    void insert(User &u){
	    string word = (u.UsrName);
        Accounts* tmp = root;
        for(ll i = 0;i < word.length();i++){
        	if(!(tmp->next[word[i]])){
                tmp->next[word[i]] = new Accounts();
                tmp->next[word[i]]->parent = tmp;
                tmp = tmp->next[word[i]];
        	}
        	else tmp = tmp->next[word[i]];
        }
        (tmp->usr) = u;
        tmp->isUser = 1;
    }

    //This Function Finds an existing user in the Trie structure

    Accounts* find(string word){
        Accounts* tmp = root;
        Accounts* found = NULL;
        if(!tmp) return found;
        for(ll i = 0;i < word.length();i++){
        	tmp = tmp->next[word[i]];
        	if(!tmp){
                break;
        	}
        }
        if(tmp) found = tmp;
        return found;
    }

    //This Function removes an existing User from the Trie Structure

    void remove(string word){
    	Accounts* found = find(word);
    	if(found){
            bool stop = false;
            while(!stop && found && found != root){
            	for(auto ch : charList){
    				if(found->next[ch]) {stop = true;break;}
    	        }
    	        if(!stop){
    	        	Accounts* tmp = found->parent;
    	        	if(tmp){
	                    for(auto ch : charList){
	    					if(tmp->next[ch] == found) {tmp->next[ch] = NULL;break;}
	    	            }
	    	        }
    	            delete found;
    	            found = tmp;
                    if(found && found->isUser) break;
    	        }
            }
    	}
    	else{
    		cout<<"USER NOT FOUND!!\n\n";
    	}
    }

    //This Function Prints the Users stored in the Trie structure recursively into the file denoted by fout

    void print(ofstream& fout,Accounts* node){
        if(node){
            if(node->isUser){
                fout<<node->usr;
            }
            for(auto ch : charList){
                if(node->next[ch]){
                    print(fout,node->next[ch]);
                }
            }
        }
    }

    //This Function Loads data from the files into the structures at the beginning of Program

    void Load(){
    	ifstream fin("DataBase.dat",ios::in | ios::binary);
    	Item tmp;
    	if(fin){
	    	while(fin>>tmp){
	    		Products[tmp.Section].push_back(tmp);
	    	}
	    	fin.close();
        }
      	fin.open("Accounts.dat",ios::in | ios::binary);
    	User u;
    	if(fin){
            while(fin>>u){
            	insert(u);
            }
            fin.close();
    	}
    }

    //This Function UnLoads data into the files from the structures at the end of Program

    void UnLoad(){
    	ofstream fout("DataBase.dat",ios::out | ios::binary);
    	for(auto key_val : Products){
    		for(auto tmp : key_val.second)
    		{
    		    fout<<tmp;
    		}
    	}
    	fout.close();
    	fout.open("Accounts.dat",ios::out | ios::binary);
    	print(fout,root);
    	fout.close();
    }

    //This Function helps a new user to sign up for the Application

    void SignUp(){
    	Clr_Scr();
    	center_align("Welcome to the E-MARKET");
    	cout<<"\n\n";
    	User a;
    	cout<<"\t\tEnter your Name : ";
        cin>>a.Name;
        int ok = 1;
        while(ok){
        	cout<<"\n\t\tEnter your preferred Username : ";
        	cin>>a.UsrName;
        	if(a.UsrName == "Guest"){
        		cout<<"\a"<<flush;
        		cout<<"\n\t\tNot allowed to choose this Username !!"<<flush;
        		SLEEP(1000);
        	}
        	else {
	        	Accounts* tmp = find(a.UsrName);
	        	if(tmp && tmp->isUser){
	        		cout<<"\a"<<flush;
	        		cout<<"\n\t\tUsername already taken !! Choose a different one !!"<<flush;
	        		SLEEP(1000);
	        	}
	        	else ok = 0;
	        }
        }
        cout<<"\n\t\tEnter your Password : ";
        cin>>a.Pwd;
        cout<<"\n\t\tEnter your Delivery Address : ";
        cin.ignore();
        getline(cin,a.Address,'\n');
        cout<<"\n\t\tEnter you Mobile Number : ";
        cin>>a.Contact_No;
        cout<<"\n\t\tDo you want to register as a seller ? (1 for YES, 0 for NO) : ";
        cin>>a.isSeller;
        insert(a);
        Clr_Scr();
        cout<<"\n\n\n\t\t\tThank you for signing up with us !!"<<flush;
        SLEEP(2000);
    }

    //This Function helps in Deleting an existing user from entirely - calls remove() to delete user from the Trie as well

    void Delete_user(){
        Clr_Scr();
        center_align("DELETE USER");
        string n;
        cout<<"\n\n\t\tEnter the UserName : ";
        cin>>n;
        Accounts* tmp = find(n);
        if(tmp){
            string p;
            cout<<"\n\t\tConfirm Your Password : ";
            char ch;
            cin.ignore();
            while((ch = getch()) != '\n' && ch != ' '){
                p += ch;
                cout<<"*";
            }
            if((tmp->usr).Pwd == p){
                remove(n);
                Clr_Scr();
                cout<<"\n\n\n\t\tSUCCESSFULLY REMOVED USER !!"<<flush;
                SLEEP(2000);
            }
            else{
                Clr_Scr();
                cout<<"\a"<<flush;
                cout<<"\n\n\n\t\tPASSWORD DOESN'T MATCH !!"<<flush;
                SLEEP(2000);
            }
        }
        else{
            Clr_Scr();
            cout<<"\a"<<flush;
            cout<<"\n\n\n\t\tNO SUCH USER !!"<<flush;
            SLEEP(2000);
        }
    }

    //This Function shows the Home Screen which is shown just after the Program starts

    void HomeScreen(){
        Load();
    	int mode = -1;
    	while(mode != 6){
    		Clr_Scr();
    		//Change_Color("1C");
    	    right_align("Not Logged in");
    	    center_align("Welcome to the E-MARKET");
            cout<<"\n\n";
            cout<<"\t\tChoose an option : \n";
            cout<<"\t\t\t1. Go to the Products Section\n";
            cout<<"\t\t\t2. User Login\n";
            cout<<"\t\t\t3. Seller Login\n";
            cout<<"\t\t\t4. Sign Up\n";
            cout<<"\t\t\t5. Delete User\n";
            cout<<"\t\t\t6. Exit\n";
            cin>>mode;
            switch(mode){
            	case 1:{
            		User u("Guest");
            		u.Name = "Guest";
            		Market(u);
            		break;
            	}
            	case 2:{
            		LoginScreen(0);
            		break;
            	}
            	case 3:{
            		LoginScreen(1);
            		break;
            	}
                case 4:{
                    SignUp();
                    break;
                }
                case 5:{
                    Delete_user();
                    break;
                }
            	default:{
            		mode = 6;
            		break;
            	}
            }
    	}
        UnLoad();
    }

};


/**MAIN FUNCTION**/

int main(){
    //This structure is used to get our Screen Width as mentioned earlier - The Global Variable w is used here

	ioctl(0,TIOCGWINSZ, &w);

    //The charList vector (Global) is initialized here

	for0(i,26){
		charList.push_back(char(i+'a'));
		charList.push_back(char(i+'A'));
	}
	for0(i,10){
		charList.push_back(char(i+'0'));
	}
	charList.push_back('_');

    //Object of Site (Main Class of our Program) being Created

	Site S1;

	S1.HomeScreen();
}
