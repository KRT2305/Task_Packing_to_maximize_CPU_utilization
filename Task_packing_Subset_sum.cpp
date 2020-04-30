#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono; 

#define TIME        cerr << "\nTime elapsed: " << setprecision(5) <<1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";

const int sz=(1<<20)+5;
pair<int,int> dp[sz];
int parent[sz];         //this is helper array which stores sequence of processes to be scheduled.

void printOutput(int no_of_cpu, vector<vector<int>>&cpu)
{
  cout<<"NO. of CPUs: "<<no_of_cpu<<"\n";
  int count=1;
  for(auto i:cpu)
  {
    cout<<"Process index on CPU #"<<count<<" : ";
    for(auto j:i)
      cout<<j<<" ";
    cout<<'\n';
    count++;
  }
}

void subsetSum(int max_limit, int no_of_proc, pair<int,int>process[], int max_sized_proc)
{
  dp[0]={0,0};
  for(int i=0;i<=max_limit;i++)
  {
    for(int j=0;j<no_of_proc;j++)
    {
      if((i&(1<<j))==0)
      {
        int z=dp[i].second+process[j].first;
        int cnt=dp[i].first;
        if(z>max_sized_proc)
        {
          cnt++;
          z=process[j].first;
        }
        else if(z==max_sized_proc)
        {
          cnt++;
          z=0;
        }
        if(dp[i|(1<<j)].first==cnt)
        {
          if(z<dp[i|(1<<j)].second)
          {
            parent[i|(1<<j)]=j;
            dp[i|(1<<j)]=min(dp[i|(1<<j)],{cnt,z});
          }
        }
        else if(dp[i|(1<<j)].first>cnt)
        {
          parent[i|(1<<j)]=j;
          dp[i|(1<<j)]={cnt,z};
        }
      }
    }
  }
}
signed main()
{ 

// -------------------------------------Code starts here---------------------------------------------------------------------     

  int no_of_proc;
  cout<<"No. of process: ";
  cin>>no_of_proc;
  pair<int,int> process[no_of_proc];   //this pair array stores 

  fill_n(dp,sz,make_pair(1e9,0));     //the dp array stores number of CPUs alloted. This is filled with 
                                        //large values for finding minimum CPUs. 

  for(int i=0;i<no_of_proc;i++)
  {
    cout<<"Time taken by process "<<i+1<<": ";
    cin>>process[i].first;
    process[i].second=i+1;                          //processes with their indexes are stored.
  }
  auto start = high_resolution_clock::now(); 
  sort(process,process+no_of_proc);          //processses are sorted and the max iter time is stored.       
  int max_sized_proc=process[no_of_proc-1].first;
  int max_limit=(1<<no_of_proc)-1;
  
   //function for getting sequence through which the processes will be scheduled
  subsetSum(max_limit, no_of_proc, process, max_sized_proc);  

  int ini=max_limit;
  vector<int>arr;                           //has the sequence of processes
  while (ini>0)
  {
    arr.push_back(parent[ini]);
    ini^=(1<<parent[ini]);
  }
  reverse(arr.begin(),arr.end());
  vector<vector<int> >cpu;                  //for storing the CPU which is alloted to the processes.
  int s=0;
  vector<int>temp;
  for(auto i:arr)
  {
    if(s+process[i].first>max_sized_proc)
    {
      cpu.push_back(temp);
      temp.clear();
      temp.push_back(process[i].second);
      s=process[i].first;
    }
    else
    {
      s+=process[i].first;
      temp.push_back(process[i].second);      
    }
  }
  cpu.push_back(temp);
  int no_of_cpu=cpu.size();

  
  auto stop = high_resolution_clock::now(); 

  printOutput(no_of_cpu, cpu);
  

// -------------------------------------Code ends here------------------------------------------------------------------
  auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
  //TIME
  return 0;
}
