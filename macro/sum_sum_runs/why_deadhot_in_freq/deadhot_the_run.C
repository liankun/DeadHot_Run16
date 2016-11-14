#include<fstream>
#include<set>
#include<map>
void deadhot_the_run(){
  char high_txt_name[5][100]={"high_want_deadhot_0_10.txt",
                          "high_want_deadhot_10_20.txt",
			  "high_want_deadhot_20_30.txt",
			  "high_want_deadhot_30_40.txt",
			  "high_want_deadhot_40_44.txt"};
  char low_txt_name[5][100]={"low_want_deadhot_0_10.txt",
                          "low_want_deadhot_10_20.txt",
			  "low_want_deadhot_20_30.txt",
			  "low_want_deadhot_30_40.txt",
			  "low_want_deadhot_40_44.txt"};
  
  TH2D* hhigh_freq = new TH2D("hhigh_freq","high dead hot vs the run",44,-0.5,43.5,8000,-0.5,7999.5);
  hhigh_freq->GetXaxis()->SetTitle("The run");
  hhigh_freq->GetYaxis()->SetTitle("dead hot channel");

  TH2D* hlow_freq = new TH2D("hlow_freq","low dead hot vs the run",44,-0.5,43.5,8000,-0.5,7999.5);
  hlow_freq->GetXaxis()->SetTitle("The run");
  hlow_freq->GetYaxis()->SetTitle("dead hot channel");

  map<int,int> bad_high_map;
  map<int,int> bad_low_map;

  int the_bad_high=0;
  int the_bad_low=0;
  for(int i = 0;i < 5;i++){
//    cout<<high_txt_name[i]<<endl;
//    cout<<low_txt_name[i]<<endl;
    ifstream in_high_txt(high_txt_name[i]);
    ifstream in_low_txt(low_txt_name[i]);
    int key;
    while(in_high_txt>>key){
      bad_high_map.insert(pair<int,int>(key,the_bad_high));
      the_bad_high++;
    }
    
    while(in_low_txt>>key){
      bad_low_map.insert(pair<int,int>(key,the_bad_low));
      the_bad_low++;
    }

    in_high_txt.close();
    in_low_txt.close();
  }
  
  for(int i = 0;i < 44;i++){
    char path[500];
    sprintf(path,"../%d/high_deadhot.txt");
    int key;
    int new_key;
    ifstream if_high(path);
    while(if_high>>key>>new_key){
      if(bad_high_map.find(key)!=bad_high_map.end()){
        hhigh_freq->Fill(i,bad_high_map[key]);
      }
    }

    sprintf(path,"../%d/low_deadhot.txt");
    ifstream if_low(path);
    while(if_low>>key>>new_key){
      if(bad_low_map.find(key)!=bad_low_map.end()){
        hlow_freq->Fill(i,bad_low_map[key]);
      }
    }
    if_high.close();
    if_low.close();
  }

  
  TFile* ofile = new TFile("freq.root","RECREATE");
  hhigh_freq->Write();
  hlow_freq->Write();
//  cout<<"Number all high dead hot channel: "<<bad_high_set.size()<<endl;
//  cout<<"Number all low dead hot channel: "<<bad_low_set.size()<<endl;
  
}
