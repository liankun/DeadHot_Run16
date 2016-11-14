#include<fstream>
void read_deadhot_repass(){
  ifstream runlist("MPC-EX_Physics_Run_List.txt");
  TH1D* hhigh_deadhot_key = new TH1D("hhigh_deadhot_key","High Dead hot vs key",49152,-0.5,49152-0.5);
  hhigh_deadhot_key->GetXaxis()->SetTitle("key");

  TH1D* hlow_deadhot_key = new TH1D("hlow_deadhot_key","Low Dead hot vs key",49152,-0.5,49152-0.5);
  hlow_deadhot_key->GetXaxis()->SetTitle("key");

  TH1D* hhigh_deadhot_runNum = new TH1D("hhigh_deadhot_runNum","high dead hot number vs run number",851,454789-0.5,455639-0.5);
  hhigh_deadhot_runNum->GetXaxis()->SetTitle("runNumber");

  TH1D* hlow_deadhot_runNum = new TH1D("hlow_deadhot_runNum","low dead hot number vs run number",851,454789-0.5,455639-0.5);
  hlow_deadhot_runNum->GetXaxis()->SetTitle("runNumber");
 
  if(runlist.is_open()){
    int runNumber;
    while(runlist >> runNumber){
//      cout<<"run Number: "<<runNumber<<endl;
      char path[500];
      int key;
      int new_key;
      sprintf(path,"%d/high_deadhot_repass.txt",runNumber);
      ifstream high_deadhot(path);
      int count=0;
      while(high_deadhot>>key>>new_key){
        count++;
	hhigh_deadhot_key->Fill(key);
      }
      hhigh_deadhot_runNum->Fill(runNumber,count);
      high_deadhot.close();
      sprintf(path,"%d/low_deadhot_repass.txt",runNumber);
      ifstream low_deadhot(path);
      count=0;
      while(low_deadhot>>key>>new_key){
        count++;
	hlow_deadhot_key->Fill(key);
      }
      hlow_deadhot_runNum->Fill(runNumber,count);
      if(count>4000) cout<<runNumber<<endl;
      low_deadhot.close();
    }
  }
  TFile* ofile = new TFile("deadhot_statistic_repass.root","RECREATE");
  hhigh_deadhot_key->Write();
  hlow_deadhot_key->Write();
  hhigh_deadhot_runNum->Write();
  hlow_deadhot_runNum->Write();
}
