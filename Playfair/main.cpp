/*---马昕然16307130347---*/

#include<string>
#include<cstdlib>
#include<iostream>
#include<fstream>

#define N 26

using namespace std;

void decrypt(string key){
	
	/*----------------生成密钥矩阵-------------------*/
	char matrix[5][5];
	int location[N]={0};
	int i=0,j,k;
	for(;i<key.length();i++){//将密钥填进矩阵中
		matrix[i/5][i%5]=key[i];
		location[key[i]-'A']=1;
	}

	j=i/5;
	k=i%5;
	i=0;

	for(;k<5;k++){//完成当前行
		if(i==('J'-'A')) i++;
		while(location[i]!=0) i++;	
		if(i==('J'-'A')) i++;
		matrix[j][k]='A'+i;
		i++;	
	}
	j++;
	for(;j<5;j++){
		for(k=0;k<5;k++){
			if(i==('J'-'A')) i++;
			while(location[i]!=0) i++;
			if(i==('J'-'A')) i++;
			matrix[j][k]='A'+i;		
			i++;
		}
	}

	/*--------------------------------------*/
	
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
			cout<<matrix[i][j]<<' ';
		cout<<endl;
	}
	
	/*-------定位字母在矩阵中的位置---------*/
	k=0;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			location[matrix[i][j]-'A']=k;
			k++;
		}
	}
	/*----------Decryption-------------*/

	cout<<endl;
	ifstream infile("Playfair_2.txt");
	if(!infile.is_open()) cout<<"File opened failed";
	ofstream outfile("Plaintext.txt");
	if(!outfile.is_open()) cout<<"File created failed";

	char c,d;
	int rc,cc,rd,cd;//row&column
	while(!infile.eof()){
		infile>>c;
		infile>>d;

		rc=location[c-'A']/5;
		cc=location[c-'A']%5;
		rd=location[d-'A']/5;
		cd=location[d-'A']%5;

		if(rc==rd){
			c=matrix[rc][(cc+4)%5];
			d=matrix[rd][(cd+4)%5];
		}
		else if(cc==cd){
			c=matrix[(rc+4)%5][cc];
			d=matrix[(rd+4)%5][cd];
		}
		else{
			c=matrix[rc][cd];
			d=matrix[rd][cc];
		}
		outfile<<c<<d<<' ';
		cout<<c<<d<<' ';
	}

	outfile.close();
	infile.close();
}

int main(){
	cout<<"Playfile decrypted:"<<endl;
	string filename="Playfair_2.txt";
	ifstream infile;
	infile.open(filename);
	if(!infile.is_open()) cout<<"File open failed";
	
	char c,d;
	//infile>>noskipws;//读取回车和空格
	int alphabet[N]={0};
	int pair[N][N]={0};
	while(!infile.eof()){
		infile>>c;
		alphabet[c-'A']++;
		infile>>d;
		alphabet[d-'A']++;
		pair[c-'A'][d-'A']++;
	}

	int i,j;
	cout<<endl;
	for(i=0;i<N;i++) cout<<alphabet[i]<<' ';
	cout<<endl;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(pair[i][j]!=0){
				cout<<char('A'+i)<<char('A'+j)<<':';
				cout<<pair[i][j]<<endl;
			}
		}
		//cout<<endl;
	}

	infile.close();

	string key;
	cout<<"Please input key:";
	cin>>key;
	decrypt(key);

	system("pause");
	return 0;
}
