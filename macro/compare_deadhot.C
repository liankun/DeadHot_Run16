#include<fstream>
#include<set>
void compare_deadhot(){
  ifstream deadhot_db("deadhot_from_db.txt");
  int key;
  int high_deadhot;
  int low_deadhot;
  set<int> high_deadhot_db;
  set<int> low_deadhot_db;
  while(deadhot_db>>key>>high_deadhot>>low_deadhot){
    if(high_deadhot > 0) high_deadhot_db.insert(key);
    if(low_deadhot > 0) low_deadhot_db.insert(key);
  }
 
  
  ifstream high_real_deadhot("high_real_deadhot.txt");
  ifstream low_real_deadhot("low_real_deadhot.txt");
  set<int> high_deadhot_no_db;
  set<int> low_deadhot_no_db;
  
  while(high_real_deadhot>>key){
    high_deadhot_no_db.insert(key);
  }
  while(low_real_deadhot>>key){
    low_deadhot_no_db.insert(key);
  }

  //statistic part
  int count = 0;
  cout<<"high deadhot from DB: "<<high_deadhot_db.size()<<endl;
  cout<<"high deadhot from No DB: "<<high_deadhot_no_db.size()<<endl;
  for(std::set<int>::iterator it=high_deadhot_db.begin(); it!=high_deadhot_db.end(); ++it){
     int ch = (*it);
     if(high_deadhot_no_db.find(ch)!=high_deadhot_no_db.end()) count++;
  }
  cout<<"Same key: "<<count<<endl;
  
  count=0;
  cout<<"low deadhot from DB: "<<low_deadhot_db.size()<<endl;
  cout<<"low deadhot from No DB: "<<low_deadhot_no_db.size()<<endl;
  for(std::set<int>::iterator it=low_deadhot_db.begin(); it!=low_deadhot_db.end(); ++it){
     int ch = (*it);
     if(low_deadhot_no_db.find(ch)!=low_deadhot_no_db.end()) count++;
   }
   cout<<"Same key: "<<count<<endl;
  
  count=0;
  for(std::set<int>::iterator it=low_deadhot_no_db.begin(); it!=low_deadhot_no_db.end(); ++it){
    int ch= (*it);
    if(high_deadhot_no_db.find(ch)!=high_deadhot_no_db.end()) count++;
    
  }
  
  cout<<"both high low deadhot: "<<count<<endl;


   ofstream high_deadhot_db_out("high_deadhot_db.txt");
   for(std::set<int>::iterator it=high_deadhot_db.begin(); it!=high_deadhot_db.end(); ++it){
     high_deadhot_db_out << *it <<endl;
   }

   ofstream low_deadhot_db_out("low_deadhot_db.txt");
   for(std::set<int>::iterator it=low_deadhot_db.begin(); it!=low_deadhot_db.end(); ++it){
     low_deadhot_db_out << *it <<endl;
   }
}
