#include<bits/stdc++.h>
#include<string>
#include "bridge.h"
using namespace std;
void bridge::read_line(string s,int n){
	int l = s.size();
	int i=0;
	while(s[i] != ':'){i++;}
	i=i+2;
	while(i <= l){
		adj_lans.push_back(s[i]);
		i=i+2;
	}
	sort(adj_lans.begin(),adj_lans.end());
	id = n;root = n;root_distance = 0;
}

void readlan(string str,lan L[]){
	int l = str.size();
	char c = str[0];string s;
	int i=3;
	while(i < l){
		if(i == l-1){
			stringstream geek(s+string(1,str[i]));
			int x=0;
			geek >> x;
			L[(int)c - 65].hosts.push_back(x);
			i++;

		}
		else if(isspace(str[i]) != 0){
			i++;
		}
		else if(str[i] == 'H'){
			s = "";
			i++;
		}
		else if(isspace(str[i+1]) != 0){
			stringstream geek(s+string(1,str[i]));
			int x=0;
			geek >> x;
			L[(int)c - 65].hosts.push_back(x);
			i++;
		}
		else{
			s = s+string(1,str[i]);
			i++;
		}
	}
	sort(L[(int)c - 65].hosts.begin(),L[(int)c - 65].hosts.end());
}
