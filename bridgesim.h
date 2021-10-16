#include<bits/stdc++.h>
#include<string>
#include "bridge.h"
//#include "bridge.cpp"
using namespace std;

class message{
	public:
		int root;int dist;
		bridge source;
		int destination;char lan;
		message()
		{
			root = -1;dist = -1;
			destination = -1;lan = '\0';
		}
};

struct messageComparer
{
    bool operator()(message const &j1, message const &j2)
    {
    	if(j1.destination < j2.destination) return true;
    	else return false;
        //compare j1 and j2 and return true or false
    }
};

class trace{
	public:
		int time;int bridge;int dist;int root;
		char status;//message m;
		trace(int t,int b,char s,int d,int r){
			time = t;bridge = b;status = s;
			dist = d;root = r;
		}
		bool operator==(trace const &a){
			return(this->time==a.time && this->bridge==a.bridge && this->dist==a.dist && this->root==a.root && this->status==a.status);
		}
};

// class tr1{
// 	public:
// 		trace t;
// 		int from;
// 		tr1(trace t1,int r){
// 			t = t1;
// 			from = r; 
// 		}
// 		bool operator==(tr1 const &a){
// 			return(this->t==a.t && this->from==a.from);
// 		}
// };

bool ordered(trace t1,trace t2);
bool get_best(trace t1,trace t2);
void spanning_protocol(bridge B[],lan L[],int bl,int Ll,int d);
lan see1(vector<ftable> v,int dest);
void learningbri(data_packet p,bridge B[],lan L[],char H[],int c);
bool sorter(pair<trace,int> &p1,pair<trace,int> &p2);


// bool comp1(const pair<trace, pair<char, int> > &a, const pair<trace, pair<char, int> > &b);
//bool operator==()