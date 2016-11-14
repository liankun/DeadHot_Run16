void grammy_layer(){
  TFile* ifile = new TFile("Run16Ana_MinBias_NoCMN_Sub-455051-0_nodeadhot.root","READONLY");
  gSystem->Load("libMyMpcEx.so");
  Exogram* hgrammyh[2];
  Exogram* hgrammyl[2];
  hgrammyh[0] = (Exogram*)ifile->Get("hgrammyh0");
  hgrammyh[1] = (Exogram*)ifile->Get("hgrammyh1");
  hgrammyl[0] = (Exogram*)ifile->Get("hgrammyl0");
  hgrammyl[1] = (Exogram*)ifile->Get("hgrammyl1");

  for(int iarm = 0;iarm < 2;iarm++){
    for(int ilayer = 0;ilayer < 8;ilayer++){
      char hname[500];
      sprintf(hname,"hgrammy_high_arm%d_layer%d_nodeadhot",iarm,ilayer);
      TCanvas* c = new TCanvas(hname,hname,800,800);
      c->SetLogz();
      hgrammyh[iarm]->DrawLayer(ilayer,"colz");
      sprintf(hname,"hgrammy_high_arm%d_layer%d_nodeadhot.gif",iarm,ilayer);
      c->Print(hname,"gif");
      delete c;      
      sprintf(hname,"hgrammy_low_arm%d_layer%d_nodeadhot",iarm,ilayer);
      TCanvas* c = new TCanvas(hname,hname,800,800);
      c->SetLogz();
      hgrammyl[iarm]->DrawLayer(ilayer,"colz");
      sprintf(hname,"hgrammy_low_arm%d_layer%d_nodeadhot.gif",iarm,ilayer);
      c->Print(hname,"gif");
      delete c;
    }
  }
}
