#include<bits/stdc++.h>
#include<string>
#include<deque>
#include "bridgesim.h"
#include<set>
using namespace std;

bool ordered(trace t1,trace t2){
	if(t1.time == t2.time){
		if(t1.root == t2.root){
			if(t1.dist == t2.dist){
				return(t1.bridge < t2.bridge);
			}
			return(t1.dist < t2.dist);
		}
		return(t1.root < t2.root);
	}
	return(t1.time < t2.time);
}

bool get_best(trace t1,trace t2){
	//if(t1.time > t2.time){return 0;}
	if(t1.root == t2.root){
		if(t1.dist == t2.dist){
			return(t1.bridge < t2.bridge);
		}
		return(t1.dist < t2.dist);
	}
	return(t1.root < t2.root);
}

bool sorter(pair<trace,int> &p1,pair<trace,int> &p2){
	return( (p1.first.time < p2.first.time) || (p1.first.time == p2.first.time && p1.first.bridge < p2.first.bridge));
}

void spanning_protocol(bridge B[],lan L[],int bl,int Ll,int d){
	int time1 = 0;char s= 's',r='r';
	vector<pair<trace, int> > span;
	deque<pair<trace, pair<char, int> > > que[bl];
	
	bool found = false;
	while(not found){

		for(int i=1;i<bl;i++){
			int r_way = 0;char l_way = 'a';
			if(! que[i].empty()){
				pair<trace, pair<char, int> > t1 = que[i].front();
				trace st = t1.first;
				//tr1 st1(st,t1.second.second);

				//if(st.bridge != st.root){
					span.push_back({st,t1.second.second});
					r_way = (t1.second).second;
					l_way = (t1.second).first;
				//}
				que[i].pop_front();
				while(! que[i].empty()){
					pair<trace,pair<int,char> > t2 = que[i].front();
					trace ttop = t2.first;
					//tr1 ttop1(ttop,t2.second.second);
					//if(ttop.bridge != ttop.root){
						span.push_back({ttop,t2.second.second});
					//}
					if(get_best(ttop,st)){
						st = ttop;
						r_way = t2.second.second;
						l_way = t2.second.first;
					}
					que[i].pop_front();
				}
			

				trace orig(time1,i,r,B[i].root_distance,B[i].root); //= {time1,i,B[i].root_distance,B[i].root,r};
				if(st.root < orig.root || (st.root == orig.root && st.dist+1 < orig.dist)){
					//cout<<"good"<<" "<<l_way<<" "<<r_way<<'\n';
					B[i].root_distance = st.dist+1;
					B[i].root = st.root;
					B[i].RP.first = l_way;
					B[i].RP.second = r_way;

					//cout<<B[i].RP.first<<" "<<B[i].RP.second<<'\n';
				}
			}
		}

		for(int i=1;i<bl;i++){
			trace t(time1,i,s,B[i].root_distance,B[i].root);
			//tr1 t4(t,i);
			span.push_back({t,i});
			//vector<int> vi = B[i].adj_bri;
			vector<char> vc = B[i].adj_lans;
					for(auto j=vc.begin();j != vc.end();j++){
						//span.push_back(t);
						vector<int> vi = L[(int)(*j) - 65].adj_bridges;
 
						for(int k=0;k<vi.size();k++){
							if(vi[k] != B[i].root){
								trace t1(time1,vi[k],r,B[vi[k]].root_distance,B[vi[k]].root);
								trace t2 = t;
								//if( (t2.root < t1.root) || (t2.root == t1.root && t2.dist+1 < t1.dist) )
								//{
								vector<trace> temp;
								for(auto h = que[vi[k]].begin();h != que[vi[k]].end();h++){temp.push_back((*h).first);}
									if((find(temp.begin(),temp.end(),trace(time1+1,vi[k],r,t2.dist,t2.root))) == temp.end())
									{
										que[vi[k]].push_front({trace(time1+1,vi[k],r,t2.dist,t2.root),{*j,i}});

										//cout<<(*j)<<'\n';
										//if(i == t2.root){}
									}
									//span.push_back(trace(time1+1,i,r,0,i));
								//}
							}
						}
					}
		}

		time1++;bool found1 = true;
		for(int l=1;l<bl;l++){
			found1 = found1 && (B[l].root == 1);
		}
		found = found1;
	}


if(d == 1){
	sort(span.begin(),span.end(),sorter);
	for(auto i =span.begin();i != span.end();i++){
		//cout<<(*i).first.bridge<<' ';
		cout<<(*i).first.time<<" "<<(*i).first.status<<" "<<'B'<<(*i).first.bridge<<" ("<<"B"<<(*i).first.root<<" "<<(*i).first.dist<<" "<<"B"<<(*i).second<<')'<<'\n';
	}}

for(int h=0;h<Ll;h++){
	vector<int> vl = L[h].adj_bridges;
	if(vl.size() != 0){
	int r = B[vl[0]].root;int dist = B[vl[0]].root_distance;L[h].DP = vl[0];
	for(int k=1;k<vl.size();k++){
		if(dist > B[vl[k]].root_distance || (dist == B[vl[k]].root_distance && vl[k] < r)){
			L[h].DP = vl[k];
		}
	}
}
}

}

lan see1(vector<ftable> v,int dest){
	if(v.size() == 0){lan l;l.DP = -1;
	return l;}
	for(auto i = v.begin();i != v.end();i++){
		if((*i).host == dest){
			return (*i).fport;
		} 
	}
	lan l;l.DP = -1;
	return l; 
}

void learningbri(data_packet p,bridge B[],lan L[],char H[],int c){
	if(c <= 100){
		char c1 = H[p.destination];
		data_packet p1 = p;
		//p1.prev = H[p1.source];
		//p1.bridge = L[p1.prev].DP;
		//vector<int> v0 = L[(int)p1.prev - 65].val_bri;
		//cout<<v0.size();
		for(auto i = L[(int)p1.prev - 65].val_bri.begin();i != L[(int)p1.prev - 65].val_bri.end();i++){

			if((*i) != p1.bridge){

				//vector<ftable> v = B[(*i)].table;
				//cout<<B[(*i)].RP.first<<B[(*i)].adj_lans.size()<<'\n';
				if(see1(B[(*i)].table,p1.source).DP == -1){
					//cout<<"good"<<'\n';
					B[(*i)].table.push_back(ftable(p1.source,L[int(p1.prev) - 65]));
					//cout<<"g1"<<'\n';
				}
				lan l = see1(B[(*i)].table,p1.destination);
				//cout<<l.DP<<'\n';
				if(l.DP != -1 && l.id != p1.prev){
					//cout<<l.id<<'\n';
					//cout<<(*i)<<'\n';
					//cout<<"good"<<l.DP<<'\n';
					data_packet p2 = p1;
					p2.prev = l.id;
					p2.bridge = (*i);
					//p1.bridge = l1.DP;
					c = c+1;
					//cout<<"good"<<c<<'\n';
					learningbri(p2,B,L,H,c); 
				}

				else if(l.DP == -1){
					//vector<char> v1 = B[(*i)].val_lans;
					for(auto j = B[(*i)].val_lans.begin();j != B[(*i)].val_lans.end();j++){
						if((*j) != p1.prev){
							data_packet p2 = p1;
							p2.prev = (*j);
							p2.bridge = (*i);
							c = c+1;
							//cout<<"good"<<c<<'\n';
							learningbri(p2,B,L,H,c);
						}
					}
				}

			}
		}
	}
	
}



