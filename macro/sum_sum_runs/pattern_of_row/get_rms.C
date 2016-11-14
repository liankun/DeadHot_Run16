void get_rms(){
  TFile* ifile = new TFile("work_2016_09_12/Integral_deadhot_deadhot_no_cut.root");
  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];

  

  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hhigh_itg[iarm][iitg])cout<<"get null for hhigh_itg "<<endl;
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hlow_itg[iarm][iitg])cout<<"get null for hlow_itg "<<endl;
    }
  } 
  
  ifstream high_out_txt("fit_high_pol2_new.txt");
  ifstream low_out_txt("fit_low_pol2_new.txt");

  double high_par0[2][5][192*4];
  double high_par1[2][5][192*4];
  double high_par2[2][5][192*4];
  double low_par0[2][5][192*4];
  double low_par1[2][5][192*4];
  double low_par2[2][5][192*4];
  int iarm;
  int iitg;
  int irow;
  double par0;
  double par1;
  double par2;
  
  while(high_out_txt>>iarm>>iitg>>irow>>par0>>par1>>par2){
    high_par0[iarm][iitg][irow]=par0;
    high_par1[iarm][iitg][irow]=par1;
    high_par2[iarm][iitg][irow]=par2;
  }

  while(low_out_txt>>iarm>>iitg>>irow>>par0>>par1>>par2){
    low_par0[iarm][iitg][irow]=par0;
    low_par1[iarm][iitg][irow]=par1;
    low_par2[iarm][iitg][irow]=par2;
  }

  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int i = 0;i < 192*4;i++){
        char fname[500];
        sprintf(fname,"fit_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit = new TF1(fname,fit0,32*i+24576*iarm,i*32+31+24576*iarm,3);
        fit->FixParameter(0,high_par0[iarm][iitg][i]);
        fit->FixParameter(1,high_par1[iarm][iitg][i]);
        fit->FixParameter(2,high_par2[iarm][iitg][i]);
        hhigh_itg[iarm][iitg]->Fit(fit,"QR+");
        sprintf(fname,"fit_low_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit = new TF1(fname,fit0,32*i+24576*iarm,i*32+31+24576*iarm,3);
        fit->FixParameter(0,low_par0[iarm][iitg][i]);
        fit->FixParameter(1,low_par1[iarm][iitg][i]);
        fit->FixParameter(2,low_par2[iarm][iitg][i]);
        hlow_itg[iarm][iitg]->Fit(fit,"QR+");
      }
    }//iarm
  }//iitg

}
