#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

int is_currect(int sudoku[9][9])
{
	int correct=0;
	for (int i = 0; i < 9; ++i)
	{
		int testcase_r[10]={0};
		int testcase_c[10]={0};
		for (int j = 0; j < 9; ++j)
		{
			testcase_r[sudoku[i][j]]++;
			testcase_c[sudoku[j][i]]++;

		}
		for (int k = 1; k < 10; ++k)
		{
			if (testcase_r[k]>1 || testcase_c[k]>1)
			{
				correct=-1;
				break;
			}
		}
		if (correct==-1)
		{
			break;
		}
	}
	if (correct!=-1)
	{
		for (int r = 0; r < 3; ++r)
		{
			for (int c = 0; c < 3; ++c)
			{
				int testcase_b[10]={0};
				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						testcase_b[sudoku[(3*r)+i][(3*c)+j]]++;
					}
				}
				for (int k = 1; k < 10; ++k)
				{
					 if (testcase_b[k]>1)
					 {
					 	correct=-1;
					 	break;
					 }
				}
				if (correct==-1)
				{
					break;
				}
			}
			if (correct==-1)
			{
				break;
			}
		}
	}
	return correct;
	
}

int is_possible(int sudoku[9][9],int k,int l,int guess)
{
	int testcase[10]={0};
	for (int i = 0; i < 9; ++i)
	{
		testcase[sudoku[k][i]]=1;
		testcase[sudoku[i][l]]=1;
	}
	int r=k/3;
	int c=l/3;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			testcase[sudoku[i+(3*r)][j+(3*c)]]=1;
		}
	}
	return testcase[guess];
	
}
int find_possible(int sudoku[9][9],int k,int l)
{
	int count=0;
	int chance;
	int testcase[10]={0};
	for (int i = 0; i < 9; ++i)
	{
		testcase[sudoku[k][i]]=1;
		testcase[sudoku[i][l]]=1;
	}
	int r=k/3;
	int c=l/3;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			testcase[sudoku[i+(3*r)][j+(3*c)]]=1;
		}
	}
	for (int i = 1; i < 10; ++i)
	{
		if(testcase[i]==0)
		{
			chance=i;
			count++;
		}
	}
	if (count==1)
	{
		 count=9+chance;
	}
	return count;

}


int main()
{
	//take sudoku input
	int filled=0;
	int sudoku[9][9];
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			cin>>sudoku[i][j];

			if (sudoku[i][j]!=0)
			{
				filled++;
			//	cout<<filled<<endl;
			}
		}
	}
	cout<<endl<<endl;
	int min=9;
	int t=10;
	while(t>0 && filled<81)
	{
		int prev=filled-1;
		cout<<"entering naive"<<endl;
		while(filled<81 && filled!=prev)
		{
			prev=filled;
			for (int i = 0; i < 9; ++i)
			{
				for (int j = 0; j < 9; ++j)
				{
					if(sudoku[i][j]!=0)continue;
					int possible=find_possible(sudoku,i,j);
					if(possible>9)
					{
						sudoku[i][j]=possible-9;
						filled++;
						cout<<filled<<endl;
					}
					if (filled==81)
					{
						break;
					}
				}
				if (filled==81)
				{
					break;
				}
			}
			cout<<"exiting naive"<<endl;


			cout<<endl<<endl;
	/*
			for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9 ; ++j)
			{
				cout<<sudoku[i][j]<<" ";
				if (j==2 || j==5)
				{
					cout<<"   ";
				}
			}
			cout<<endl;
			if (i==2 || i==5)
			{
				cout<<endl;
			}
		
			
		}
		*/
		cout<<"entering clever"<<endl;
		while(filled<81 && prev!=filled)
		{
			prev=filled;
			int possibl[9][9][10];
			for (int i = 0; i < 9; ++i)
			{
				for(int j =0;j<9;++j)
				{
					if(sudoku[i][j]!=0)
					{
						for (int k = 1; k < 10; ++k)
						{
							if(k==sudoku[i][j])possibl[i][j][k]=0;
							else possibl[i][j][k]=1;
						}
					}
					else
					{
						for(int k=1;k<10;k++)
						{
							possibl[i][j][k]=is_possible(sudoku,i,j,k);
						}
					}
				}
			}
			//rows
			int row_count,column_count,block_count,pos_col,pos_row;
			for (int k = 1; k < 10; ++k)
			{
				
				for(int i=0;i<9;i++)
				{
					row_count=0;
					column_count=0;
					for(int j=0;j<9;j++)
					{
						if(possibl[i][j][k]==0)
						{
							row_count++;
							pos_col=j;
						}
						if (possibl[j][i][k]==0)
						{
							column_count++;
							pos_row=j;
						}

					}
					if (row_count==1)
					{
						sudoku[i][pos_col]=k;
						//filled++;
						//cout<<filled<<endl;
					}
					if (column_count==1)
					{
						sudoku[pos_row][i]=k;
						//filled++;
						//cout<<filled<<endl;
					}
				}
			}
			//blcok
			for (int r = 0; r < 3; ++r)
			{
				for (int c = 0; c < 3; ++c)
				{
					for (int k = 1; k < 10; ++k)
					{
						block_count=0;
						for (int i = 3*r; i < 3*(r+1); ++i)
						{
							for (int j = 3*c; j < 3*(c+1); ++j)
							{
								if(possibl[i][j][k]==0)
								{
									block_count++;
									pos_row=i;
									pos_col=j;
								}
							}
						}
						if(block_count==1)
						{
							sudoku[pos_row][pos_col]=k;
						//	filled++;
						//	cout<<filled<<endl;
						}
					}
				}
			}
		}
		filled=0;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				if (sudoku[i][j]!=0)
				{
					filled++;
				}
			}
		}
		cout<<"exiting clever"<<endl;












		cout<<endl<<endl;


		}
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9 ; ++j)
			{
				cout<<sudoku[i][j]<<" ";
				if (j==2 || j==5)
				{
					cout<<"   ";
				}
			}
			cout<<endl;
			if (i==2 || i==5)
			{
				cout<<endl;
			}
		
			
		}
		t--;
		cout<<filled<<endl;
	}
	//int unfilled=0;
	vector<pair<int,int> > blank;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (sudoku[i][j]==0)
			{
				blank.push_back(make_pair(i,j));
	//			unfilled++;
			}
		}
	}
	cout<<blank.size()<<endl;
	vector<int> *choices=new vector<int>[blank.size()];
	for (int i = 0; i < blank.size(); ++i)
	{
		int a=blank[i].first;
		int b=blank[i].second;
		for (int j = 1; j < 10; ++j)
		{
			if (is_possible(sudoku,a,b,j)==0)
			{
				choices[i].push_back(j);
			}
		}
	}
	long long sum=1;
	for (int i = 0; i < blank.size(); ++i)
	{
		sum=sum*choices[i].size();
	}
	cout<<sum<<endl;
	int original[9][9];
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			 original[i][j]=sudoku[i][j];
		}
	}
	int correct=-1;
	long long counter=1;
	while(correct==-1)
	{
		if(counter%100==0)
			cout<<(((long double)counter/(long double)sum)*100)<<"  %"<<endl;
		counter++;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				sudoku[i][j]=original[i][j];
			}
		}
		for (int i = 0; i < blank.size(); ++i)
		{
			int a=blank[i].first;
			int b=blank[i].second;
			int r=rand()%choices[i].size();
			sudoku[a][b]=choices[i][r];
		}
		correct=is_currect(sudoku);
	}
	cout<<endl<<endl;
	for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9 ; ++j)
			{
				cout<<sudoku[i][j]<<" ";
				if (j==2 || j==5)
				{
					cout<<"   ";
				}
			}
			cout<<endl;
			if (i==2 || i==5)
			{
				cout<<endl;
			}
		
			
		}




	return 0;
}
