#include <iostream>
#include <string>
#include <set>

using namespace std;

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
		if(p.size()==length){
			pass.insert(p);
			i++;
		}
		else if(p!="done"){ //If the user enters an invalid password (wrong length), and the entered password is not "done"...
			//...prompt user to reenter the password.
			cout << "Please retype password " << i << ":" << endl;
			continue;
		}
	}while(p!="done" && cin.good()); //While user has not entered "done" when prompted for passwords
	cout << "Passwords loaded: " << i-1 << endl;
	print_diff(length);
	while(cin.good() && pass.size()>1){
		cout << ">"; //Fallout-esque password prompt
		string tried;
		int cor;
		cin >> tried;
		while(cin.good() && pass.find(tried)==pass.end()){ //Prompt user to reenter password if entered password does not exist in list of passwords
			cout << "Please retype password:" << endl << ">";
			cin >> tried;
		}
		pass.erase(tried); //Remove entered password from list of candidates
		cout << "> /" << length <<" correct.\r>"; //Prompt user for number of correct characters.
		cin >> cor;
		for(set<string>::iterator j=pass.begin(); j!=pass.end(); j++){
			if(cor!=correct(tried,(*j))){ //Remove all candidates that do not have the same amount of correct characters as the tried password.
				pass.erase(*j);
			}
		}
		if(pass.size()==1){ //If there is only one candidate left, print it and exit.
			cout << ">" << *(pass.begin()) << endl;
			cout << "Access granted." << endl;
		}
		else if(pass.size()!=0){ //If there is still candidates to be considered, print them.
			cout << "Possible matches:" << endl;
			for(set<string>::iterator j=pass.begin();j!=pass.end();j++){
				cout << (*j) << " ";
			}
			cout << endl;
		}
	}
}
