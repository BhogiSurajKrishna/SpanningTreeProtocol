#include<bits/stdc++.h>
#include<string>
using namespace std;

class lan{
	public:
		char id;int DP;
		vector<int> adj_bridges;
		vector<int> val_bri;
		vector<int> hosts;
		lan(){
			id = '\0';DP = -1;
		}
};

class ftable
{
	public:
		int host;
		lan fport;
		ftable(int h,lan f){
			host = h;
			fport = f;
		}
};

class bridge{
	public:
		int id;int root;
		int root_distance;
		vector<char> adj_lans;
		vector<char> val_lans;
		vector<ftable> table;
		pair<char,int> RP;
		bridge(){
			id = -1;root = id;
			RP = make_pair('\0',0);
			root_distance = 0;
		}
		void read_line(string s,int n);
};

class data_packet{
public:
	int source;
	int destination;
	char prev;
	int bridge;
	data_packet(){
		prev = 'a';
		bridge = 0;
		source = 0;
		destination = 0;
	}
	data_packet(int s,int d,char p,int b){
		source = s;destination = d;prev = p;bridge = b;
	}
};

void readlan(string str,lan L[]);
