#include<fstream>
void read_pedestal(){
  TFile* ifile = new TFile("deadhot_ped.root","READONLY");
  TH2D* hhigh_ped =(TH2D*)ifile->Get("hhigh_ped");
  TH2D* hlow_ped = (TH2D*)ifile->Get("hlow_ped");

  TH1D* hhigh_ped_rms = new TH1D("hhigh_ped_rms","High Pedestal RMS",200,0,10);
  TH1D* hlow_ped_rms = new TH1D("hlow_ped_rms","low Pedestal RMS",200,0,10);


  for(int i = 0;i < 2000;i++){
    hhigh_ped->SetAxisRange(i,i,"x");
    TH1D* htemp = hhigh_ped->ProjectionY();
    double entries = htemp->GetEntries();
    if(entries < 1) continue;
    double rms = htemp->GetRMS();
    double mean = htemp->GetMean();
    hhigh_ped_rms->Fill(rms);
  }

  for(int i = 0;i < 2000;i++){
    hlow_ped->SetAxisRange(i,i,"x");
    TH1D* htemp = hlow_ped->ProjectionY();
    double entries = htemp->GetEntries();
    if(entries < 1) continue;
    double rms = htemp->GetRMS();
    hlow_ped_rms->Fill(rms);
  }

  TFile* ofile = new TFile("Pedestal_RMS.root","RECREATE");
  hhigh_ped_rms->Write();
  hlow_ped_rms->Write();

}
