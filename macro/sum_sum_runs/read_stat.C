#include<fstream>
void read_stat(){
  TFile* ifile = new TFile("deadhot_statistic_add_discrete_loose_cut.root","READONLY");
  TH1D* hstat_high = new TH1D("hstat_high","High Channel Dead hot",50,-0.5,49.5);
  TH1D* hstat_low = new TH1D("hstat_low","Low Channel Dead hot",50,-0.5,49.5);
  
  TH1D* hhigh_deadhot_key = (TH1D*)ifile->Get("hhigh_deadhot_key");
  TH1D* hlow_deadhot_key = (TH1D*)ifile->Get("hlow_deadhot_key");
//  TH1D* hhigh_deadhot_runNum = (TH1D*)ifile->Get("hhigh_deadhot_runNum");
//  TH1D* hlow_deadhot_runNum = (TH1D*)ifile->Get("hlow_deadhot_runNum");
  ofstream high_deadhot_stat("high_deadhot_stat_add_discrete_loose_cut.txt");
  ofstream low_deadhot_stat("low_deadhot_stat_add_discrete_loose_cut.txt");
  ofstream high_real_deadhot("high_real_deadhot_add_discrete_loose_cut.txt");
  ofstream low_real_deadhot("low_real_deadhot_add_discrete_loose_cut.txt");
  for(int i = 0;i < 49152;i++){
    double content = hhigh_deadhot_key->GetBinContent(i+1);
    if(content > 0){
      hstat_high->Fill(content);
      high_deadhot_stat<<i<<" "<<(int)content<<endl;
      
    }
    if(content > 27) high_real_deadhot<<i<<endl;

    content = hlow_deadhot_key->GetBinContent(i+1);
    if(content > 0){
      hstat_low->Fill(content);
      low_deadhot_stat<<i<<" "<<(int)content<<endl;
    }

    if(content > 27) low_real_deadhot<<i<<endl;
  }
  TFile* ofile = new TFile("statistic_add_discrete_new_loose_cut.root","RECREATE");
  hstat_high->Write();
  hstat_low->Write();
}
