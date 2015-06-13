#include <iostream>
#include <string>
#include <set>
#include <unistd.h>

using namespace std;

void exact_match(){
	cout << ">Exact match!" << endl;
	cout << ">Please wait" << endl;
	cout << ">while system" << endl;
	cout << ">is accessed." << endl;
	sleep(3);
}
void print_diff(int l){
	cout << "Difficulty: ";
	switch(l){
		case 4:
		case 5:
			cout << "Very Easy." << endl;
			break;
		case 6:
		case 7:
		case 8:
			cout << "Easy." << endl;
			break;
		case 9:
		case 10:
			cout << "Average." << endl;
			break;
		case 11:
		case 12:
			cout << "Hard." << endl;
			break;
		case 13:
		case 14:
		case 15:
			cout << "Very Hard." << endl;
			break;
	}
}
void clear(){
	cout << "\e\r                         \r";
}
int correct(string a, string b){ //Count correct characters
	int count=0;
	for(int i=0; i<a.size(); i++){
		if(a.at(i)==b.at(i)) count++;
	}
	return count;
}
int main(){
	set<string> pass;
	int length=0;
	string p="";
	int i=1;
	do{
		cout << i << ": ";
		cin >> p;
		if(!cin.good()) exit(0);
		if(length==0) length = p.size(); //If the password length has not been determined, set it to the length of the first password the user enters.
		if(p=="done"){ //Exit loop if the entered "password" is "done"
			cout << "\e[A\r                    \r";
			break;
		}
		else if(p.size()==length){
			pass.insert(p);
			i++;
		}
		cout << "\e[A\r                    \r";
	}while(p!="done" && cin.good()); //While user has not entered "done" when prompted for passwords
	cout << "Passwords loaded: " << i-1 << endl;
	print_diff(length);
	sleep(1);
	clear();
	cout << "\e[A";
	clear();
	cout << "\e[A";
	clear();
	while(cin.good() && pass.size()>1){
		cout << ">"; //Fallout-esque password prompt
		string tried;
		int cor;
		cin >> tried;
		while(cin.good() && pass.find(tried)==pass.end()){ //Prompt user to reenter password if entered password does not exist in list of passwords
			cout << "\e[A";
			clear();
			cout << ">";
			cin >> tried;
		}
		pass.erase(tried); //Remove entered password from list of candidates
		cout << ">Entry denied" << endl;
		cout << "> /" << length <<" correct.\r>"; //Prompt user for number of correct characters.
		cin >> cor;
		if(cor==length){
			cout << "\e[A";
			clear();
			exact_match();
		}
		for(set<string>::iterator j=pass.begin(); j!=pass.end(); j++){
			if(cor!=correct(tried,(*j))){ //Remove all candidates that do not have the same amount of correct characters as the tried password.
				pass.erase(*j);
			}
		}
		if(pass.size()==1){ //If there is only one candidate left, print it and exit.
			cout << ">" << *(pass.begin()) << endl;
			exact_match();
		}
		else if(pass.size()!=0){ //If there is still candidates to be considered, print them.
			cout << "Possible matches:" << endl;
			for(set<string>::iterator j=pass.begin();j!=pass.end();j++){
				cout << (*j) << " ";
			}
			cout << endl;
			sleep(3);
			clear();
			cout << "\e[A";
			clear();
			cout << "\e[A";
			clear();
		}
	}
}
