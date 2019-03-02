/************
Function of radixtree struct are:-
Insert(key,val) does nothing if key is already present
Delete(Key,val) does nothing if key not present
getvalue(key) returns -1 if key not found
************/
#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>
#include <climits>
using namespace std;

typedef long long ll;
#define N 64

int t=0;

struct node{
	int numnodes;
	ll fac;
	int id;
	node* childs[N];
	int values[N];
	node(){
		numnodes=0;
		fac=1;
		id=t;
		t++;
		for(int i=0;i<N;i++){
			childs[i]=NULL;
			values[i]=0;
		}
	}
	node(ll f){
		numnodes=0;
		fac=f;	
		id=t;
		t++;	
		for(int i=0;i<N;i++)childs[i]=NULL;
	}
};

struct radixtree{
	node* root;
	radixtree(){
		root=NULL;
	}
	void insert1(ll key, int val, ll curr, node* nd){
		//cout<<"I "<<key<<" "<<curr<<" "<<nd->fac<<" <-\n";
		ll tmp=key-curr;
		nd->numnodes++;
		ll fac=nd->fac;
		if(fac==1){
			nd->values[tmp/fac]=val;
			nd->childs[tmp/fac]=(node*) 1;
			return ;
		}
		if(nd->childs[tmp/fac]==NULL){
			nd->childs[tmp/fac]=new node(fac/N);
		}
		insert1(key,val,curr+(tmp/fac)*(fac),nd->childs[tmp/fac]);
	}
	void Insert(ll key, int val){
		//cout<<key<<" here\n";
		if(getvalue(key)!=-1){
			setvalue(key,val);
			return;
		}
		if(root==NULL){
			root=new node();
		}
		while(true){	
			ll fac=root->fac;
			if(key>=fac*N){
				node* nd=new node(fac*N);
				nd->numnodes=root->numnodes;
				nd->childs[0]=root;
				if(root->numnodes==0){
					nd->childs[0]=NULL;
					delete(root);
				}
				
				root=nd;

			}
			else{
				insert1(key,val,0,root);
				break;
			}
		}
	}

	void delete1(ll key,ll curr,node* nd ){
		ll tmp=key-curr;
		nd->numnodes--;
		ll fac=nd->fac;
		if(fac==1){
			nd->childs[tmp/fac]=NULL;
			if(nd->numnodes==0){
				delete nd;
			}
			return ;
		}
		int t=nd->childs[tmp/fac]->numnodes;
		delete1(key,curr+(tmp/fac)*(fac),nd->childs[tmp/fac]);
		if(t==1){
			nd->childs[tmp/fac]=NULL;
		}
		if(nd->numnodes==0){
			delete nd;
		}
	}
	void Delete(ll key){
		if(getvalue(key)==-1)return;
		int t=root->numnodes;
		delete1(key,0,root);
		if(t==1)root=NULL;
	}

	int getvalue1(ll key, ll curr, node* nd){
		//cout<<key<<" "<<curr<<" "<<nd->fac<<" <-\n";
		//cout<<key<<" here\n";
		if(nd==NULL)return -1;
		ll tmp=key-curr;
		ll fac=nd->fac;
		if(fac==1){
			if(nd->childs[tmp/fac]==NULL)return -1;
			return nd->values[tmp/fac];
		}
		return getvalue1(key,curr+(tmp/fac)*(fac),nd->childs[tmp/fac]);
	}
	int getvalue(ll key){
		if(root==NULL)return -1;
		if(key>=N*root->fac)return -1;
		return getvalue1(key,0,root);
	}
	void setvalue1(ll key, ll curr, node* nd, int v){
		//cout<<key<<" "<<curr<<" "<<nd->fac<<" <-\n";
		//cout<<key<<" here\n";
		if(nd==NULL)return;
		ll tmp=key-curr;
		ll fac=nd->fac;
		if(fac==1){
			if(nd->childs[tmp/fac]==NULL)return;
			nd->values[tmp/fac]=v;
			return;
		}
		setvalue1(key,curr+(tmp/fac)*(fac),nd->childs[tmp/fac],v);
	}
	void setvalue(ll key,int v){
		if(root==NULL)return;
		if(key>=N*root->fac)return;
		setvalue1(key,0,root,v);
	}
	int getht(node* nd,int &n){
		
		int max=INT_MIN;
		//cout<<nd->numnodes<<" ";
		int c=0;
		for(int i=0;i<N;i++) {
			if( nd->childs[i]!=NULL){
				//cout<<"here at "<<i<<" "<<nd->values[i]<<" "<<(nd->childs[i]==NULL)<<endl;
				c++;
			}

			if(nd->childs[i]!=NULL && nd->fac!=1)
				{ 
					n++;
					int h=1+getht(nd->childs[i],n);
					if(h>max)
						max=h;
				}
		}
		cout<<c<<" ";
		if(max<0){
			return 1;
		}
		else
			return max;
	}
	void pt(){
		if(root==NULL)
			cout<<"0 0\n";
		else{
			int n=1;
			cout<<getht(root,n)<<" ";
			cout<<n<<endl;
		}
			
	}
};

int main(){
	radixtree T;
	/*T.Insert(1,2);
	T.Insert(2,3);
	//T.Insert(4,4);
	//T.pt();
	//return 0;
	cout<<T.getvalue(1)<<" "<<T.getvalue(2)<<" "<<T.getvalue(2)<<endl; 
	//return 0;
	T.Delete(1);
	//cout<<T.getvalue(2)<<endl;
	//T.pt();
	//return 0;
	//return 0;
	T.Insert(5,5);
	//return 0;
	T.Delete(4);
	//return 0;
	T.Insert(6,6);
	//T.pt(); return 0;
	//return 0;
	cout<<T.getvalue(6)<<" "<<T.getvalue(5)<<" "<<T.getvalue(2)<<endl;*/
	char ch;
	cin>>ch;
	int a,v;
	while(ch!='e'){
		switch(ch){
			case 'i':
						cin>>a;
						cin>>v;
						T.Insert(a,v);
						break;
			case 'd':	cin>>a;
						T.Delete(a);
						break;
			case 'l':	cin>>a;
						cout<<T.getvalue(a)<<endl;
						break;
			case 'p':	T.pt();
						break;
			default:	cout<<"INVALID OPTION"<<endl;
						exit(0);
		}
		cin>>ch;
	}
	/*
	map<int,int> M;
	srand(time(NULL));
	for(int i=0;i<10000;i++){
		int r=rand()%1999999999;
		int v=rand()%1999999999;
		int t=rand()%3;
		if(t==0){
			M[r]=v;
			T.Insert(r,v);
		}
		if(t==1){
			map<int,int>::iterator it=M.find(r);
			if(it!=M.end())M.erase(it);
			T.Delete(r);
		}
		if(t==2){
			map<int,int>::iterator it=M.find(r);
			if(it==M.end()){
				if(T.getvalue(r)!=-1){
					cout<<"pain\n";
					return 0;
				}
			}
			else{
				if(T.getvalue(r)!=M[r]){
					cout<<"pain\n";
					return 0;
				}
			}
		}
	}*/

	
	return 0;
}
