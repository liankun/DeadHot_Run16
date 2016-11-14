#include<fstream>
#include<set>
void draw_deadhot_geom(){
  gSystem->Load("libMyMpcEx.so");
  ifstream runlist("MPC-EX_Physics_Run_List.txt");
  if(runlist.is_open()){
    int runNumber;
    
    Exogram* hgrammyh[2];
    Exogram* hgrammyl[2];
    hgrammyh[0] = new Exogram("hgrammyh0","Exogram high arm 0",900,-24,24,900,-24,24,8,-0.5,7.5);
    hgrammyh[1] = new Exogram("hgrammyh1","Exogram high arm 1",900,-24,24,900,-24,24,8,-0.5,7.5);
    hgrammyl[0] = new Exogram("hgrammyl0","Exogram low arm 0",900,-24,24,900,-24,24,8,-0.5,7.5);
    hgrammyl[1] = new Exogram("hgrammyl1","Exogram low arm 1",900,-24,24,900,-24,24,8,-0.5,7.5);
    int run_count=0;
    while(runlist >> runNumber){
cout<<"process: "<<runNumber<<endl;
      run_count++;
      if(run_count > 5) break;
      char path[500];
      int key;
      int new_key;
      hgrammyh[0]->Reset();
      hgrammyh[1]->Reset();
      hgrammyl[0]->Reset();
      hgrammyl[1]->Reset();
      sprintf(path,"%d/high_deadhot.txt",runNumber);
      ifstream high_deadhot(path);
      set<int>high_deadhot_list;
      while(high_deadhot>>key>>new_key){
        high_deadhot_list.insert(key);
      }

      sprintf(path,"%d/low_deadhot.txt",runNumber);
      ifstream low_deadhot(path);
      set<int>low_deadhot_list;
      while(low_deadhot>>key>>new_key){
        low_deadhot_list.insert(key);
      }
      for(int ich=0;ich<24576*2;ich++){
        int arm = 0;
	if(ich >=24576)arm=1;
	if(high_deadhot_list.find(ich)==high_deadhot_list.end()){
          hgrammyh[arm]->FillEx(ich,1);
	}
	else{
          hgrammyh[arm]->FillEx(ich,2);
	}
	if(low_deadhot_list.find(ich)==low_deadhot_list.end()){
          hgrammyl[arm]->FillEx(ich,1);
	}
	else{
          hgrammyl[arm]->FillEx(ich,2);
	}
      }
      sprintf(path,"%d/Exo_deadhot.root",runNumber);
      TFile* ofile = new TFile(path,"RECREATE");
      for(int iarm = 0;iarm<2;iarm++){
        for(int ilayer=0;ilayer<8;ilayer++){
          hgrammyh[iarm]->SetAxisRange(ilayer,ilayer,"z");
	  char hname[500];
	  sprintf(hname,"hhigh_exo%d_%d",iarm,ilayer);
	  TH2D* htemp0 = hgrammyh[iarm]->Project3D("yx");
	  htemp0->SetName(hname);
	  htemp0->Write();
          hgrammyl[iarm]->SetAxisRange(ilayer,ilayer,"z");
	  sprintf(hname,"hlow_exo%d_%d",iarm,ilayer);
	  TH2D* htemp1 = hgrammyl[iarm]->Project3D("yx");
	  htemp1->SetName(hname);
	  htemp1->Write();
	}
      }
      ofile->Close();
    }//while runNumber
  }//is open
}
