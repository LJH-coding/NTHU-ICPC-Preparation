#include<bits/stdc++.h>
using namespace std;
int main(){
	string sol,bf,make;
	cout<<"Your solution file name :";
	cin>>sol;
	cout<<"Brute force file name :";
	cin>>bf;
	cout<<"Make data file name :";
	cin>>make;
	system(("g++ "+sol+" -o sol").c_str());
	system(("g++ "+bf+" -o bf").c_str());
	system(("g++ "+make+" -o make").c_str());
	for(int t = 0;t<10000;++t){
		system("./make > ./1.in");
		double st = clock();
        system("./sol < ./1.in > ./1.ans");
        double et = clock();
        system("./bf < ./1.in > ./1.out");
        if(system("diff ./1.out ./1.ans")) {
			printf("\033[0;31mWrong Answer\033[0m on test #%d",t);
            return 0;
        } 
		else if(et-st>=2000){
			printf("\033[0;32mTime limit exceeded\033[0m on test #%d, Time %.0lfms\n",t,et-st);
			return 0;
		}
		else {
            printf("\033[0;32mAccepted\033[0m on test #%d, Time %.0lfms\n", t, et - st);
        }
	}
}
