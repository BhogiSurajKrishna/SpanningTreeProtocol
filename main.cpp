#include<bits/stdc++.h>
#include "bridgesim.h"
#include<algorithm>
using namespace std;

bool comp(ftable f1,ftable f2){
	return(f1.host < f2.host);
}

int main(){
	int trace1;cin>>trace1;
	int b_num;cin>>b_num;
	bridge B[b_num+1];
	lan L[26];
	string str;int i_b=0;
	while(i_b < b_num+1){
		getline(cin, str);
		B[i_b].read_line(str,i_b);
		for(int k=0;k<B[i_b].adj_lans.size();k++){
			char c = B[i_b].adj_lans[k];
			L[(int)c - 65].id = c;
			L[(int)c - 65].adj_bridges.push_back(i_b);
		}
		i_b++;
	}

	int lans = 0;
	for(int k=0;k<26;k++){
		if(L[k].adj_bridges.size() != 0){
			lans++;
			sort(L[k].adj_bridges.begin(),L[k].adj_bridges.end());
		}
	}

	spanning_protocol(B,L,b_num+1,26,trace1);
	for(int i = 1;i<b_num+1;i++){
		cout<<"B"<<i<<":";
		for(int j=0;j<B[i].adj_lans.size();j++){
			if(B[i].RP.first == B[i].adj_lans[j]){
				cout<<" "<<B[i].adj_lans[j]<<"-"<<"RP";
				B[i].val_lans.push_back(B[i].adj_lans[j]);
				L[(int)B[i].adj_lans[j] - 65].val_bri.push_back(i);
			}
			else if(i == L[(int)B[i].adj_lans[j] - 65].DP){
				cout<<" "<<B[i].adj_lans[j]<<"-"<<"DP";
				B[i].val_lans.push_back(B[i].adj_lans[j]);
				L[(int)B[i].adj_lans[j] - 65].val_bri.push_back(i);
			}
			else{
				cout<<" "<<B[i].adj_lans[j]<<"-"<<"NP";
			}
		}
		sort(B[i].val_lans.begin(),B[i].val_lans.end());
		cout<<'\n';
	}


	
	for(int i=0;i<lans;i++){
		string str2;
		getline(cin,str2);
		readlan(str2,L);
	}

	int maxi  = 0;
	for(int k=0;k<26;k++){
		if(L[k].hosts.size() != 0){
			for(auto i1=L[k].hosts.begin();i1!=L[k].hosts.end();i1++){
				maxi = max(maxi,(*i1));
			}
			sort(L[k].val_bri.begin(),L[k].val_bri.end());
		}
	}

	char H[maxi+1];
	H[0] = 'a';
	for(int k=0;k<26;k++){
		if(L[k].hosts.size() != 0){
			for(auto i1=L[k].hosts.begin();i1!=L[k].hosts.end();i1++){
				H[*i1] = L[k].id;
			}
		}
	}

	string str2;
	getline(cin,str2);
	stringstream geek(str2);int num=0;
	geek >> num;
	data_packet pack[num+1];
	for(int k=1;k<=num;k++){
		getline(cin,str2);
		int l = str2.size();
		int i=1;string s="";
		while(isspace(str2[i]) == 0){
			s = s + string(1,str2[i]);
			i++;
		}
		stringstream geek(s);int x=0;
		geek >> x;
		pack[k].source = x;
		i = i+2;s="";
		while(i < l){
			s = s + string(1,str2[i]);
			i++;
		}
		stringstream geek1(s);int y=0;
		geek1 >> y;
		pack[k].destination = y;
		pack[k].prev = H[pack[k].source];
		//cout<<H[pack[k].source];
		learningbri(pack[k],B,L,H,0);

		for(int o=1;o<=b_num;o++){
			vector<ftable> v3 = B[o].table;
			sort(v3.begin(),v3.end(),comp);
			cout<<'B'<<o<<':'<<'\n';
			cout<<"HOST ID | FORWARDING PORT"<<'\n';
			for(auto k = v3.begin();k != v3.end();k++){
				cout<<'H'<<(*k).host<<" | "<<(*k).fport.id<<'\n';
			}
			//cout<<B[o].table.size()<<' ';
		}
			//if(k != num){
				cout<<'\n';
				//}
	}
	
	//for(int k=1;k<=num;k++){cout<<pack[k].source<<' '<<pack[k].destination<<'\n';}

	

	// for(int i = 1;i<b_num+1;i++){
	// 	cout<<"B"<<i<<":";
	// 	for(int j=0;j<B[i].adj_lans.size();j++){
	// 		if(B[i].RP.first == B[i].adj_lans[j]){
	// 			cout<<" "<<B[i].adj_lans[j]<<"-"<<"RP";
	// 			//B[i].val_lans.push_back(B[i].adj_lans[j]);
	// 			//L[(int)B[i].adj_lans[j] - 65].val_bri.push_back(i);
	// 		}
	// 		else if(i == L[(int)B[i].adj_lans[j] - 65].DP){
	// 			cout<<" "<<B[i].adj_lans[j]<<"-"<<"DP";
	// 			//B[i].val_lans.push_back(B[i].adj_lans[j]);
	// 			//L[(int)B[i].adj_lans[j] - 65].val_bri.push_back(i);
	// 		}
	// 		else{cout<<" "<<B[i].adj_lans[j]<<"-"<<"NP";}
	// 	}
	// 	//sort(B[i].val_lans.begin(),B[i].val_lans.end());
	// 	cout<<'\n';
	// }


}

