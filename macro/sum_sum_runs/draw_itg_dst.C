void draw_itg_dst(int group=0){
  char name[500];
  sprintf(name,"%d/Integral.root",group);
  TFile* ifile = new TFile(name,"READONLY"); 
  
  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];

  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=0;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
    }
  }
  
}
