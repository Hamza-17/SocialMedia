#include <iostream>
#include<cstring>
#include <fstream>
using namespace std;

class Post;
class Helper;
class User;
class Page;
class Date;
class Comment;
class SocialNetworks;


class Helper{
public:

	static int stringlenght(char* str){    //function to calculate length of string
		int lenght = 0;
		for (int i = 0; str[i] != '\0'; i++){
			lenght++;
		}
		return lenght;
	}


	static char* GetStringFromBuffer(char* str){  //function to allocate memory and copy string
		int lenght = stringlenght(str);
		char *mystr = new char[lenght + 1];
		int i;
		for (i = 0; i < lenght; i++){
			mystr[i] = str[i];
		}
		mystr[i] = '\0';

		return mystr;
	}

	static int CompareString(char* str1, char* str2){  //function to check if strings are equal
		int L1 = stringlenght(str1);
		int L2 = stringlenght(str2);
		int check = 0;

		if (L1 == L2){
			for (int i = 0; i < L1; i++){
				if (str1[i] == str2[i]){
					check++;
				}
			}
		}

		if (check == L1){
			return 0;
		}

		else{
			return 1;
		}
	}


	static char* StringCopy(char* str1, char*str2){
		int i;                  //function to copy one string into another
		for (i = 0; str2[i] != '\0'; i++){
			str1[i] = str2[i];
		}
		str1[i] = '\0';
		return str1;

	}


	static bool FindSubstring(char* tofind, char* mystring){  //Function to find substring in a string
		bool check = false;
		int L1 = stringlenght(tofind);
		int L2 = stringlenght(mystring);
		int k = 0;
		int counter = 0;
		for (int i = 0; mystring[i] != '\0'; i++){
			if (mystring[i] == tofind[k]){
				counter++;
				k++;
			}

			else{

				counter = 0;
				k = 0;
			
			}

			if (counter == L1){
				check = true;
				break;
			}
		}


		return check;
	}

	static void  TrimStart(char* str){   //Function to remove initial spaces
		int count = 0;
		for (int i = 0; str[i] != ' '; i++){
			count++;
		}
		int j = 0;
		for (int i = count; str[i] != '\0'; i++){
			str[j] = str[i];
			j++;
		}
		str[j] = '\0';

	}

};


class Object{
private:
	char* ID;
public:
	Object();
	Object(char*);
	~Object();
	void SetterObject(char*);
	char* GetterObject();
	void PrintID();
	virtual void PrintName();
};

Object::Object(){
	ID = NULL;
}

Object::Object(char* O){
	
	ID = Helper::GetStringFromBuffer(O);
}

void Object::SetterObject(char* O){
	
	ID = Helper::GetStringFromBuffer(O);
}

Object::~Object(){

	if (ID != NULL){
		delete[]ID;
	}

}

void Object::PrintID(){
	cout << ID;
}

 void Object::PrintName(){

	 //print function of base class does nothing, will be over ridden
}

char* Object::GetterObject(){

	return ID;
}


class Date{
private:
	int date;
	int month;
	int year;
public:
	static Date CurrentDate;
	static void SetCurrentDate(int,int,int);
	static void PrintCurrentDate();
	Date(int, int, int);
	~Date();
	void SetterDate(int, int, int);
	void PrintDate();
	int getterDate();
	static int returndate();
};


Date::~Date(){

}

Date::Date(int d = 0, int m = 0, int y = 0){

	date = d;
	month = m;
	year = y;


}

int Date::returndate(){

	return CurrentDate.date;
}

 void Date:: SetCurrentDate(int d, int m, int y)
{
	CurrentDate.date = d;
	CurrentDate.month = m;
	CurrentDate.year = y;
}
 void Date:: PrintCurrentDate()
{
	cout << CurrentDate.date << "/" << CurrentDate.month << "/" << CurrentDate.year << endl;
}

void Date::SetterDate(int d, int m, int y){

	date = d;
	month = m;
	year = y;

}

void Date::PrintDate(){

	cout << date << "/" << month << "/" << year;
}

int Date::getterDate(){
	return date;
}


Date Date::CurrentDate;

class Comment :public Object{

private:
	char* Description;
	Object* CommentBy;
	Post* CommentOn;

public:
	Comment();
	~Comment();
	void SetterDescription(char*);
	void SetterCommentBy(Object* ptr);
	void setterCommentID(char* t);
	void setterCommentOn(Post* ptr);
	char* getterCommentID();
	void PrintComment();
	char* getterdescription();
	void PrintCommentByName();
	void PrintDescription();
	static int totalcomments;
};

Comment::Comment(){
	Description = 0;
	CommentBy = 0;
	CommentOn = 0;
}

Comment::~Comment(){
	if (Description != NULL){
		delete[]Description;
	}

	if (CommentBy != NULL){
		delete[]CommentBy;
	}

	if (CommentOn != NULL){
		delete[]CommentOn;
	}

}

void Comment::SetterCommentBy(Object *ptr){
	CommentBy = ptr;
}

void Comment::SetterDescription(char* str){

	Description = Helper::GetStringFromBuffer(str);

}


void Comment::setterCommentOn(Post* ptr){
	CommentOn = ptr;
}

char* Comment::getterCommentID(){
	char* str = GetterObject();
	return str;
}

char* Comment::getterdescription(){
	return Description;
}

void Comment::setterCommentID(char* id){
	SetterObject(id);
}


void Comment::PrintCommentByName(){
	CommentBy->PrintName();
}
void Comment::PrintComment(){
	CommentBy->PrintName();
	cout << endl;
	cout << Description << endl;
}

void Comment::PrintDescription(){
	int count = 0;
	for (int i = 0; Description[i] != ' '; i++){
		count++;
	}

	for (int k = count; Description[k] != '\0'; k++){
		cout << Description[k];
	}
}




class Post :public Object{
private:
	Date SharedDate;
	char* text;
	Object* sharedBy;
	Object** likedBy;
	Comment** comment;
	int TotalLikesCountOfThisPost;
	int TotalCommentsOfThisPost;

public:
	Post();
	~Post();
	void Load(ifstream&);
	void settertext(char* t);
	void setterPostID(char* t);
	char* getterPostID();
	void SetSharedBy(Object* ptr);
	void AddLikedBy(Object* ptr);
	char* ReturnSharedBy();
	void AddComment(Comment*);
	void viewlikes();
	char* gettertext();
	void PrintForSearch();
	void OutputAsTimeline();
	void OutputAsHomepage();
};


Post::Post(){
	text = NULL;
	sharedBy = NULL;
	likedBy = new Object*[10];
	for (int i = 0; i < 10; i++){
		likedBy[i] = 0;
	}

	comment = new Comment*[10];
	for (int i = 0; i < 10; i++){
		comment[i] = 0;
	}

	SharedDate = 0;
	TotalLikesCountOfThisPost = 0;
	TotalCommentsOfThisPost = 0;
}

Post::~Post(){
	if (text != NULL){
		delete[]text;
	}

	if (sharedBy != NULL){
		delete[]sharedBy;
	}

	if (likedBy != NULL){
		delete[]likedBy;
	}
	

	if (sharedBy != NULL){
		delete[]sharedBy;
	}

	for (int i = 0; comment[i] != 0; i++){
		delete[]comment[i];
	}
	delete[]comment;

}



void Post::settertext(char* t){
	text = Helper::GetStringFromBuffer(t);
}

char* Post::getterPostID(){
	char* str = GetterObject();
	return str;
}

char* Post::gettertext(){
	return text;
}

void Post::PrintForSearch(){

	sharedBy->PrintName();
	cout << " wrote " << text << endl;
}

void Post::setterPostID(char* id){
	SetterObject(id);
}

void Post::SetSharedBy(Object* ptr){

	sharedBy = ptr;

}

char* Post::ReturnSharedBy(){
	char* s = sharedBy->GetterObject();
	return s;
}


void Post::AddLikedBy(Object *ptr){
	bool check = false;
	for (int i = 0; likedBy[i] != 0; i++){
		if (Helper::CompareString(ptr->GetterObject(), likedBy[i]->GetterObject()) == 0){ //checking if post is already liked
			check = true;
			break;
		}
	}

	if (check == false){
		likedBy[TotalLikesCountOfThisPost] = ptr;
		TotalLikesCountOfThisPost++;
	}
}




void Post::Load(ifstream &fin){
	char buffer[80];
	fin >> buffer;
	setterPostID(buffer);
	int day, month, year;
	fin >> day;
	fin >> month;
	fin >> year;
	SharedDate.SetterDate(day, month, year);
	fin.getline(buffer, 80);
	fin.getline(buffer, 80);
	settertext(buffer);
}


void Post::OutputAsHomepage(){

	int date = Date::returndate();
	if (SharedDate.getterDate() >= date-1){
		cout << "---";
		sharedBy->PrintName();
		cout << " shared '" << text << "'" << endl;
		for (int i = 0; comment[i] != 0; i++){
			cout << "          ";
			comment[i]->PrintCommentByName();
			cout << " wrote: ";
			cout << comment[i]->getterdescription()  << endl;
		}

		cout << endl;
	}
}

void Post::OutputAsTimeline(){


	cout << "---'";
	cout << text << "'---";
	cout << "(";
	SharedDate.PrintDate();
	cout << ")"<<endl;
	for (int i = 0; comment[i] != 0; i++){
		cout << "          ";
		comment[i]->PrintCommentByName();
		cout << " wrote: ";
		cout <<  comment[i]->getterdescription() << endl;
	}

	cout << endl;
}





void Post::viewlikes(){

	for (int i = 0; likedBy[i] != 0; i++){
		cout << likedBy[i]->GetterObject() << "-";
		likedBy[i]->PrintName();
		cout << endl;

	}


}


void Post::AddComment(Comment* c){
	comment[TotalCommentsOfThisPost] = c;
	TotalCommentsOfThisPost++;
}


class Page :public Object{
private:
	char* fname;
	char* lname;
	Post **timeline;
	int TotalPostsCountOfThisPage;

public:
	Page();
	~Page();
	Page(char*, char*, char*);
	char* getterID();
	char* getterFN();
	char* getterLN();
	void setterID(char*);
	void setterFN(char*);
	void setterLN(char*);
	void Load(ifstream&);
	void AddPostInTimeline(Post* ptr);
	void AddPostInHomePage(Post* ptr);
	void PrintPages();
	void PrintName();
};


Page::Page(){

	fname = NULL;
	lname = NULL;
	timeline = new Post*[10];
	for (int i = 0; i < 10; i++){
		timeline[i] = 0;
	}

	TotalPostsCountOfThisPage = 0;
}

void Page::AddPostInTimeline(Post* ptr){


	timeline[TotalPostsCountOfThisPage] = ptr;
	TotalPostsCountOfThisPage++;
}



Page::~Page(){


	if (fname != NULL){
		delete[]fname;
	}

	if (lname != NULL){
		delete[]lname;
	}

	if (timeline != NULL){
		delete[]timeline;
	}

}

void Page::PrintPages(){
	PrintID();
	cout << " - " << fname << " " << lname << endl;;

}

void Page::PrintName(){
	cout  << fname << " " << lname;
}


Page::Page(char*id, char*fn, char*ln) :Object(id){
	fname = Helper::GetStringFromBuffer(fn);
	lname = Helper::GetStringFromBuffer(ln);
}



char* Page::getterID(){

	char* str = GetterObject();
	return str;
}

char* Page::getterFN(){

	return fname;
}

char* Page::getterLN(){

	return lname;
}

void Page::setterID(char*id){

	SetterObject(id);
}

void Page::setterFN(char* fn){

	fname = Helper::GetStringFromBuffer(fn);
}

void Page::setterLN(char* ln){
	
	lname = Helper::GetStringFromBuffer(ln);

}

void Page::Load(ifstream& fin){

	char buffer[50];
	fin >> buffer;
	setterID(buffer);
	fin >> buffer;
	setterFN(buffer);
	fin.getline(buffer, 80);
	setterLN(buffer);

}



class User :public Object{

private:

	char* fname;
	char* lname;
	char** friendIDs;
	char** PageIDs;
	Page** likedpages;
	User** Friends;
	Post** timeline;
	int friendsNo;
	int PagesNo;
    int TotalPostsCountOfThisUser;

public:
	User();
	~User();
	User(char*, char*, char*, char**, char**, int, int);
	char* getterID();
	char* getterFN();
	char* getterLN();
	char** getterFI();
	char** getterPI();
	int getterFrNo();
	int getterPgNo();
	void setterFI(char*, int);
	void setterFrNo(int);
	void setterPgNo(int);
	void setterID(char*);
	void setterFN(char*);
	void setterLN(char*);
	void Load(ifstream &fin);
	void LikePage(Page*, int);
	void AddFriend(User**);
	void printLikedPages();
	void printFriendIDs();
	void AddPostInTimeline(Post* ptr);
	void PrintName();
	void OutputTimeline();
	Page** getterlikedpages();
};




void User::PrintName(){

	cout  << fname << " " << lname;


}
User::User(){

	fname = NULL;
	lname = NULL;
	friendsNo = 0;
	PagesNo = 0;
	friendIDs = new char*[10];
	for (int i = 0; i < 10; i++){
		friendIDs[i] = 0;
	}

	likedpages = new Page*[10];
	for (int i = 0; i < 10; i++){
		likedpages[i] = 0;
	}

	Friends = new User*[10];
	for (int i = 0; i < 10; i++){
		Friends[i] = 0;
	}

	PageIDs = new char*[10];
	for (int i = 0; i < 10; i++){
		PageIDs[i] = 0;
	}

	timeline = new Post*[10];
	for (int i = 0; i < 10; i++){
		timeline[i] = 0;
	}
	TotalPostsCountOfThisUser = 0;
}

void User::AddPostInTimeline(Post * ptr){

	timeline[TotalPostsCountOfThisUser] = ptr;
	TotalPostsCountOfThisUser++;

}

void User::OutputTimeline(){

	for (int i = 0; i < TotalPostsCountOfThisUser; i++){
		timeline[i]->OutputAsTimeline();
	}

}

Page** User::getterlikedpages(){

	return likedpages;

}

User::~User(){
	

	if (fname != NULL){
		delete[]fname;
	}

	if (lname != NULL){
		delete[]lname;
	}
	
	for (int i = 0; friendIDs[i] != 0; i++){
		delete[]friendIDs[i];
	}

	delete[]friendIDs;
	
	if (likedpages != NULL){
		delete[]likedpages;
	}

	if (timeline != NULL){
		delete[]timeline;
	}

	for (int i = 0; likedpages[i] != 0; i++){
		delete[]likedpages[i];
	}
	delete[]likedpages;

}



void User::printLikedPages(){

	for (int i = 0; likedpages[i] != 0; i++){
		likedpages[i]->PrintPages();
	}
}



void User::printFriendIDs(){


	for (int i = 0; Friends[i] != 0; i++){
		cout << Friends[i]->getterID() << " - " << Friends[i]->getterFN() << " " << Friends[i]->getterLN() << endl;
	}
}



void User::AddFriend(User** FI){
	int totalusers = 20;
	for (int i = 0; friendIDs[i] != 0; i++){
		for (int j = 0; j < totalusers; j++){
			if (Helper::CompareString(FI[j]->getterID(), friendIDs[i]) == 0){
				Friends[i] = FI[j];
				break;
			}
		}
	}
}





void User::LikePage(Page* lp, int index){
	
	likedpages[index] = lp;


}


User::User(char*id, char*fn, char*ln, char**F, char**P, int fI, int Lp) :Object(id){

	fname = Helper::GetStringFromBuffer(fn);
	lname = Helper::GetStringFromBuffer(ln);
	friendsNo = fI;
	PagesNo = Lp;
	friendIDs = new char*[friendsNo];
	for (int i = 0; i < friendsNo; i++){
		friendIDs[i] = new char;
		friendIDs[i] = F[i];
	}
}

char* User::getterID(){

	char* str = GetterObject();
	return str;
}

char* User::getterFN(){

	return fname;
}

char* User::getterLN(){

	return lname;
}

char** User::getterPI(){

	return PageIDs;
}


char** User::getterFI(){

	return friendIDs;
}

int User::getterFrNo(){

	return friendsNo;
}

int User::getterPgNo(){

	return PagesNo;
}

void User::setterFrNo(int n){
	friendsNo = n;
}

void User::setterPgNo(int n){
	PagesNo = n;
}



void User::setterFI(char*fi, int index){

	friendIDs[index] = Helper::GetStringFromBuffer(fi);

}


void User::setterID(char*id){
	SetterObject(id);
}

void User::setterFN(char* fn){
	
	fname = Helper::GetStringFromBuffer(fn);
}

void User::setterLN(char* ln){
	
	lname = Helper::GetStringFromBuffer(ln);
}

void User::Load(ifstream &fin){
	char buffer[30];
	fin >> buffer;
	setterID(buffer);
	fin >> buffer;
	setterFN(buffer);
	fin >> buffer;
	setterLN(buffer);
	int count = 0;
	char Buffer1[30];
	fin >> Buffer1;
	while (Helper::CompareString(Buffer1, "-1") != 0){
		setterFI(Buffer1, count);
		fin >> Buffer1;
		count++;
	}

}




class SocialNetworks{

private:
	User **users;
	Page **pages;
	Post **timeline;
	User *currentuser;
  //  Date SystemDate;
	static int totalusers;
	static int totalpages;
	static int totalposts;

public:

	void PrintFriends();
	void SetCurrentUser(char*);
	void SetCurrentDate(int,int,int);
	void PrintLikedPages();
	SocialNetworks();
	~SocialNetworks();
	int ReturnDay();
	void AssociateFriends();
	void LoadUsers(ifstream &fin);
	void LoadPages(ifstream &fin);
	void SetTimeline(ifstream &fin);
	void PrintUserTimeline();
	void PrintHomePage();
	void LoadandSetComments(ifstream& fin);
	void ViewPostsOfAPage(char*);
	void ViewLikesOfAPost(char*);
	void Search(char*);
	void Like(char*);
	void Share(char*);
	void AddComment(char*, char*);
	void ViewPost(char*);
	void ConsoleOutput();
	
};

int SocialNetworks::totalpages = 0;
int SocialNetworks::totalusers = 0;
int SocialNetworks::totalposts = 0;




SocialNetworks::SocialNetworks(){

	users = NULL;
	pages = NULL;
	timeline = NULL;
	currentuser = NULL;
	//SystemDate = 0;
}

SocialNetworks::~SocialNetworks(){
	if (users != NULL){
		delete[]users;
	}

	if (pages != NULL){
		delete[]pages;
	}

	if (timeline != NULL){
		delete[]timeline;
	}

	if (currentuser != NULL){
		delete[]currentuser;
	}
}


void SocialNetworks::PrintLikedPages(){
	currentuser->PrintName();
	cout << "-Liked Pages" << endl << endl;
	currentuser->printLikedPages();

}

void SocialNetworks::PrintUserTimeline(){

	currentuser->PrintName();
	cout << "-Time Line" << endl << endl;
	currentuser->OutputTimeline();

}

void SocialNetworks::PrintFriends(){
	currentuser->PrintName();
	cout << "-Friend List" << endl<<endl;
	currentuser->printFriendIDs();


}

int SocialNetworks::ReturnDay(){
	//return SystemDate.getterDate();
	int d=Date::returndate();
	return d;
}

void SocialNetworks::ViewLikesOfAPost(char* str){
	int  a = str[4];
	int b = a - 49;
	Post* currentpost = new Post;
	currentpost = timeline[b];
	cout << "Post Liked By:" << endl;
	currentpost->viewlikes();

}

void SocialNetworks::ViewPost(char* str){
	int  a = str[4];
	int b = a - 49;
	Post* currentpost = new Post;
	currentpost = timeline[b];
	currentpost->OutputAsHomepage();

}

void SocialNetworks::Like(char* str){
	int  a = str[4];
	int b = a - 49;
	Post* currentpost = new Post;
	currentpost = timeline[b];
	currentpost->AddLikedBy(currentuser);

}

void SocialNetworks::Share(char* str){
	int  a = str[4];
	int b = a - 49;
	Post* currentpost = new Post;
	currentpost = timeline[b];
	currentuser->AddPostInTimeline(currentpost);

}

void SocialNetworks::AddComment(char* id, char* text){
	int  a = id[4];
	int b = a - 49;
	Post* newpost = new Post;
	newpost = timeline[b];
	Comment* newcomment = new Comment;
	newcomment->SetterCommentBy(currentuser);
	newcomment->SetterDescription(text);
	newcomment->setterCommentOn(newpost);
	newpost->AddComment(newcomment);
}

void SocialNetworks::AssociateFriends(){

	
	for (int i = 0; i < totalusers; i++){
		users[i]->AddFriend(users);
	}
	


}

void SocialNetworks::SetCurrentUser(char* id){
	int  a = id[1];
	int b = a - 49;
	currentuser = new User;
	currentuser = users[b];
	cout << currentuser->getterFN() << " " << currentuser->getterLN() << " " << "successfully set as current user" << endl;
}

void SocialNetworks::ViewPostsOfAPage(char* str){

	int  a = str[1];
	int b = a - 49;
	Page* currentpage = new Page;
	currentpage = pages[b];
	currentpage->PrintName();
	cout << endl;

	for (int i = 0; i < totalposts; i++){
		if (Helper::CompareString(timeline[i]->ReturnSharedBy(), currentpage->getterID()) == 0){
			timeline[i]->OutputAsTimeline();
	}
}

}



void SocialNetworks::PrintHomePage(){

	currentuser->PrintName();
	cout << " - " << "Home Page" << endl<<endl<<endl;
	for (int k = 0; currentuser->getterFI()[k] != 0; k++){
		for (int i = 0; i < totalposts; i++){
			if (Helper::CompareString(timeline[i]->ReturnSharedBy(), currentuser->getterFI()[k]) == 0){
				timeline[i]->OutputAsHomepage();
			}
		}
	}



	Page** P = currentuser->getterlikedpages();
	
	for (int i = 0; P[i] != 0; i++){
		for (int k = 0; k < totalposts; k++){
			if (Helper::CompareString(timeline[k]->ReturnSharedBy(),P[i]->getterID()) == 0){
				timeline[k]->OutputAsHomepage();
			}

		}

	}

}



void SocialNetworks::LoadandSetComments(ifstream& fin){
	int totalcomments;
	fin >> totalcomments;
	for (int i = 0; i < totalcomments; i++){
		Comment* newcomments = new Comment;
		char buffer[200];
		fin >> buffer;
		newcomments->setterCommentID(buffer);
		fin >> buffer;
		for (int i = 0; i < totalposts; i++){
			if (Helper::CompareString(buffer, timeline[i]->getterPostID()) == 0){
				newcomments->setterCommentOn(timeline[i]);
				timeline[i]->AddComment(newcomments);
			}
		}

		fin >> buffer;
		if (buffer[0] == 'u'){
			for (int i = 0; i < totalusers; i++){
				if (Helper::CompareString(users[i]->getterID(), buffer) == 0){
					newcomments->SetterCommentBy(users[i]);
				}
			}
		}

		else{

			for (int i = 0; i < totalpages; i++){
				if (Helper::CompareString(pages[i]->getterID(), buffer) == 0){
					newcomments->SetterCommentBy(pages[i]);
				}
			}
		}
		
		fin.getline(buffer, 200);
		newcomments->SetterDescription(buffer);
	}

	


}



void SocialNetworks::SetTimeline(ifstream &fin){
	fin >> totalposts;
	timeline = new Post*[totalposts];

	for (int i = 0; i < totalposts; i++){
		timeline[i] = new Post;
		timeline[i]->Load(fin);
		char buffer[30];
		fin >> buffer;
		if (buffer[0] == 'u'){
			for (int a = 0; a < totalusers; a++){
				if (Helper::CompareString(users[a]->getterID(), buffer) == 0){
					timeline[i]->SetSharedBy(users[a]);
					users[a]->AddPostInTimeline(timeline[i]);
					break;
				}
			}
		}

		else {

			for (int b = 0; b < totalpages; b++){
				if (Helper::CompareString(pages[b]->getterID(), buffer) == 0){
					timeline[i]->SetSharedBy(pages[b]);
					pages[b]->AddPostInTimeline(timeline[i]);
					break;
				}
			}

		}

		fin >> buffer;
		int count = 0;
		while (Helper::CompareString(buffer, "-1") != 0){
			if (buffer[0] == 'u'){
				for (int c = 0; c < totalusers; c++){
					if (Helper::CompareString(users[c]->getterID(), buffer) == 0){
						timeline[i]->AddLikedBy(users[c]);
						break;
					}
				}
			}

			else{

				for (int d = 0; d < totalpages; d++){
					if (Helper::CompareString(pages[d]->getterID(), buffer) == 0){
						timeline[i]->AddLikedBy(pages[d]);
						break;
					}
				}

			}

			fin >> buffer;
			count++;
		}

	}
}

void SocialNetworks::LoadPages(ifstream &fin){

	fin >> totalpages;
	pages = new Page*[totalpages];

	for (int i = 0; i < totalpages; i++){
		pages[i] = new Page;
		pages[i]->Load(fin);
	}

}


void SocialNetworks::SetCurrentDate(int d,int m,int y){
	//SystemDate.SetterDate(d, m, y);
	Date::SetCurrentDate(d, m, y);
	cout << "System Date: ";
	//SystemDate.PrintDate();
	Date::PrintCurrentDate();
	cout << endl;
}

void SocialNetworks::Search(char* str){
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	for (int i = 0; i < totalusers; i++){
		if (Helper::CompareString(users[i]->getterFN(), str) == 0 || Helper::CompareString(users[i]->getterLN(), str) == 0){
			if (count1 == 0){
				cout << "Users: " << endl;
			}
			cout << "---";
			users[i]->PrintID();
			cout << " - ";
			users[i]->PrintName();
			cout << endl;
			count1++;
		}

	}

	for (int i = 0; i < totalpages; i++){
		if (Helper::CompareString(pages[i]->getterFN(), str) == 0 || Helper::FindSubstring(str, pages[i]->getterLN()) == true){
			if (count2 == 0){
				cout << endl<< "Pages: " << endl;
			}
			cout << "---";
			pages[i]->PrintID();
			cout << " - ";
			pages[i]->PrintName();
			cout << endl;
			count2++;
		}
	}



	for (int i = 0; i < totalposts; i++){
		if (Helper::FindSubstring(str, timeline[i]->gettertext()) == true){
			if (count3 == 0){
				cout <<endl<< "Posts: " << endl;
			}
			cout << "---";
			cout << timeline[i]->getterPostID();
			cout << " - ";
			timeline[i]->PrintForSearch();
			count3++;
		}

	}

}


void SocialNetworks::LoadUsers(ifstream &fin){
	fin >> totalusers;
	users = new User*[totalusers];

	for (int i = 0; i < totalusers; i++){
		users[i] = new User;
		users[i]->Load(fin);
		int count = 0;
		char Buffer1[30];
		fin >> Buffer1;
		while (Helper::CompareString(Buffer1, "-1") != 0){
			for (int k = 0; k < totalpages; k++){

				if (Helper::CompareString(pages[k]->getterID(), Buffer1) == 0){
					users[i]->LikePage(pages[k], count);
					break;
				}

			}


			fin >> Buffer1;

			count++;
		}
	}

	AssociateFriends();
}




void SocialNetworks::ConsoleOutput(){


	ifstream fin;
	fin.open("Users.txt");
	ifstream finput;
	finput.open("Pages.txt");
	LoadPages(finput);
	LoadUsers(fin);
	char buffer1[] = "u7";
	cout << "Command:       Set Current User " << buffer1<< endl;
	SetCurrentUser(buffer1);
	cout << endl;
	int d = 15, m = 11, y = 2017;
	cout << "Command:       Set Current System Data " << d << " " << m << " " << y << endl;
	SetCurrentDate(d, m, y);
	cout << endl;
	cout << "Command:       View Friend List" << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	PrintFriends();
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "Command:       View Liked Pages" << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	PrintLikedPages();
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	ifstream f;
	f.open("Posts.txt");
	SetTimeline(f);
	ifstream F;
	F.open("Comments.txt");
	LoadandSetComments(F);
	cout << "Command:       View Home" << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	PrintHomePage();
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "Command:       View Timeline" << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	PrintUserTimeline();
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	char buffer2[] = "post5";
	cout << "Command:       ViewLikedList(" <<buffer2<<")"<< endl<<endl;
	ViewLikesOfAPost(buffer2);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "Command:       LikePost(" << buffer2 << ")" << endl;
	Like(buffer2);
	cout << "Command:       ViewLikedList(" << buffer2 << ")" << endl << endl;
	ViewLikesOfAPost(buffer2);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	char buffer3[] = "post4";
	char text1[] = " GoodLuck for your Result";
	cout << "Command:       PostComment(" << buffer3<<","<<text1 << ")" << endl << endl;
	AddComment(buffer3, text1);
	ViewPost(buffer3);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	char buffer4[] = "post8";
	char text2[] = " Thanks for the wishes";
	cout << "Command:       PostComment(" << buffer4 << "," << text2 << ")" << endl << endl;
	AddComment(buffer4, text2);
	ViewPost(buffer4);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	char buffer5[] = "post5";
	cout << "Command:       SharePost(" << buffer5 << ")" << endl << endl;
	Share(buffer5);
	cout << "Command:       View Timeline" << endl;
	PrintUserTimeline();
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	char buffer6[] = "p1";
	cout << "Command:       ViewPage(" << buffer6 << ")" << endl << endl;
	ViewPostsOfAPage(buffer6);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	char search1[] = "Birthday";
	cout << "Command:       Search('" << search1 << "')" << endl << endl;
	Search(search1);
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	char search2[] = "Ali";
	cout << "Command:       Search('" << search2 << "')" << endl << endl;
	Search(search2);
	
}




int main(){

	SocialNetworks S;
	S.ConsoleOutput();
	system("pause");
	return 0;

}