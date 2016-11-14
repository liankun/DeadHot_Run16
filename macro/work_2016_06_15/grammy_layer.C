void grammy_layer(){
  TFile* ifile = new TFile("Run16Ana_MinBias_NoCMN_Sub_All_Triggers-455051_after_deadhot_20cut-0.root","READONLY");
  gSystem->Load("libMyMpcEx.so");
  Exogram* hgrammyh[2];
  Exogram* hgrammyl[2];
  hgrammyh[0] = (Exogram*)ifile->Get("hgrammyh0");
  hgrammyh[1] = (Exogram*)ifile->Get("hgrammyh1");
  hgrammyl[0] = (Exogram*)ifile->Get("hgrammyl0");
  hgrammyl[1] = (Exogram*)ifile->Get("hgrammyl1");

  double maximum[2]={1300,360};

  for(int iarm = 0;iarm < 2;iarm++){
    for(int ilayer = 0;ilayer < 8;ilayer++){
      char hname[500];
      sprintf(hname,"hgrammy_high_arm%d_layer%d_deadhot_20cut",iarm,ilayer);
      TCanvas* c = new TCanvas(hname,hname,800,800);
      c->SetLogz();
      hgrammyh[iarm]->SetAxisRange(ilayer,ilayer,"z");
      TH2D* htemp0 = hgrammyh[iarm]->Project3D("yx");
//      hgrammyh[iarm]->DrawLayer(ilayer,"colz");
      htemp0->SetMaximum(maximum[iarm]);
      htemp0->Draw("colz");
      sprintf(hname,"hgrammy_high_arm%d_layer%d_deadhot_20cut.gif",iarm,ilayer);
      c->Print(hname,"gif");
      delete c;      
      sprintf(hname,"hgrammy_low_arm%d_layer%d_deadhot_20cut",iarm,ilayer);
      TCanvas* c = new TCanvas(hname,hname,800,800);
      c->SetLogz();
      hgrammyl[iarm]->SetAxisRange(ilayer,ilayer,"z");
      TH2D* htemp1 = hgrammyl[iarm]->Project3D("yx");
      htemp1->SetMaximum(maximum[iarm]);
      htemp1->Draw("colz");
//      hgrammyl[iarm]->DrawLayer(ilayer,"colz");
      sprintf(hname,"hgrammy_low_arm%d_layer%d_deadhot_20cut.gif",iarm,ilayer);
      c->Print(hname,"gif");
      delete c;
    }
  }
}
