#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	srand(time(NULL));
	
	// Hopfield Network
	cout<<"*** Hopfield Network ***"<<endl<<endl;
	
	// Examples
	// Pattern 1
	vector<int> pat1;
	pat1.push_back(1);
	pat1.push_back(1);
	pat1.push_back(-1);
	pat1.push_back(-1);
	pat1.push_back(1);
	
	// Pattern 2
	vector<int> pat2;
	pat2.push_back(-1);
	pat2.push_back(-1);
	pat2.push_back(-1);
	pat2.push_back(1);
	pat2.push_back(1);
	
	// Pattern 3
	vector<int> pat3;
	pat3.push_back(1);
	pat3.push_back(-1);
	pat3.push_back(1);
	pat3.push_back(-1);
	pat3.push_back(1);
	
	// Pattern 4
	vector<int> pat4;
	pat4.push_back(1);
	pat4.push_back(-1);
	pat4.push_back(-1);
	pat4.push_back(1);
	pat4.push_back(-1);
	
	vector<vector<int> > matrix;
	matrix.push_back(pat1);
	matrix.push_back(pat2);
	matrix.push_back(pat3);
	//matrix.push_back(pat4);
	
	cout<<"Training patterns:"<<endl;
	for(unsigned int k=0;k<matrix.size();k++){
		cout<<"[";
		for(unsigned int l=0;l<matrix[k].size()-1;l++)
			cout<<matrix[k][l]<<", ";
		cout<<matrix[k][matrix[k].size()-1]<<"]"<<endl;
	}
	cout<<endl<<endl;
	
	// Training
	vector<double> x;
	for(unsigned int i=0;i<5;i++)
		x.push_back(0);
	
	vector<vector<double> > W;
	for(unsigned int i=0;i<5;i++)
		W.push_back(x);
	
	double sum;
	
	for(unsigned int i=0;i<W.size();i++)
		for(unsigned int j=i;j<W[i].size();j++){
			// i==j => Wij=0
			if(i==j)
				W[i][j]=0;
			// i!=j
			else{
				sum=0;
				for(unsigned int k=0;k<matrix.size();k++)
					sum=sum+double(matrix[k][i]*matrix[k][j]);
				
				sum=sum/matrix.size();
				
				W[i][j]=sum;
				W[j][i]=W[i][j];
			}
		}
	
	cout<<"W matrix:"<<endl;
	for(unsigned int k=0;k<W.size();k++){
		cout<<"[";
		for(unsigned int l=0;l<W[k].size()-1;l++)
			cout<<W[k][l]<<", ";
		cout<<W[k][W[k].size()-1]<<"]"<<endl;
	}
	cout<<endl<<endl;
	
	// Test
	// Test Pattern
	vector<int> test_pat;
	test_pat.push_back(1);
	test_pat.push_back(1);
	test_pat.push_back(-1);
	test_pat.push_back(-1);
	test_pat.push_back(-1);
	
	vector<int> y, y_last;
	y=test_pat;
	
	int c=9;
	while(c!=0){
		y_last=y;
		
		int j=rand()%5;
		
		double sum=0;
		for(unsigned int i=0;i<y_last.size();i++)
			sum=sum+W[j][i]*y_last[i];
		
		if(sum>=0)
			y[j]=1;
		else
			y[j]=-1;
		
		c=0;
		if(y!=y_last)
			c++;
	}
	
	cout<<"Test pattern:"<<endl;
	cout<<"[";
	for(unsigned int k=0;k<test_pat.size()-1;k++)
		cout<<test_pat[k]<<", ";
	cout<<test_pat[test_pat.size()-1]<<"]";
	cout<<endl<<endl;
	
	cout<<"Returned pattern:"<<endl;
	cout<<"[";
	for(unsigned int k=0;k<y.size()-1;k++)
		cout<<y[k]<<", ";
	cout<<y[y.size()-1]<<"]";
	cout<<endl<<endl;
	
	return 0;
}

