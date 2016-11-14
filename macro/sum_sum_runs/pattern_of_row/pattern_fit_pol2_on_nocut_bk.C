#include<map>
#include<fstream>
void pattern_fit_pol2_on_nocut(){
  TFile* ifile = new TFile("work_2016_09_12/Integral_deadhot_deadhot_fit_50p_cut.root");  
  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];

  TH1D* hfit_chi2[2][5];

  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hhigh_itg[iarm][iitg])cout<<"get null for hhigh_itg "<<endl;
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hlow_itg[iarm][iitg])cout<<"get null for hlow_itg "<<endl;
      sprintf(hname,"fit_chi2_arm%d_itg%d",iarm,iitg);
      hfit_chi2[iarm][iitg] = new TH1D(hname,hname,100,0,400);
    }//iitg
  }//iarm
 
  ifstream high_in_txt("fit_high_pol2_new2.txt");
  ifstream low_in_txt("fit_low_pol2_new2.txt");

  double high_par0[2][5][192*4];
  double high_par1[2][5][192*4];
  double high_par2[2][5][192*4];
  int high_ndf[2][5][192*4];
  double low_par0[2][5][192*4];
  double low_par1[2][5][192*4];
  double low_par2[2][5][192*4];
  int low_ndf[2][5][192*4];

  int iarm;
  int iitg;
  int irow;
  int ndf;
  double par0;
  double par1;
  double par2;
  while(high_in_txt>>iarm>>iitg>>irow>>par0>>par1>>par2>>ndf){
    high_par0[iarm][iitg][irow]=par0;
    high_par1[iarm][iitg][irow]=par1;
    high_par2[iarm][iitg][irow]=par2;    
    high_ndf[iarm][iitg][irow]=ndf;
  }
  
  while(low_in_txt>>iarm>>iitg>>irow>>par0>>par1>>par2>>ndf){
    low_par0[iarm][iitg][irow]=par0;
    low_par1[iarm][iitg][irow]=par1;
    low_par2[iarm][iitg][irow]=par2;
    low_ndf[iarm][iitg][irow]=ndf;
  }

  ofstream high_out_txt("fit_high_pol2_refit.txt");
  ofstream low_out_txt("fit_low_pol2_refit.txt");

  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int i = 0;i < 192*4;i++){
        char fname[500];
	sprintf(fname,"fit_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit = new TF1(fname,fit0,32*i+24576*iarm,i*32+31+24576*iarm,3);
        if(high_ndf[iarm][iitg][i]>11){
	  fit->FixParameter(0,high_par0[iarm][iitg][i]);
          fit->FixParameter(1,high_par1[iarm][iitg][i]);
	  fit->FixParameter(2,high_par2[iarm][iitg][i]);
	  hhigh_itg[iarm][iitg]->Fit(fit,"QR+");
	}
	else{
          fit->SetLineColor(kGreen);
	  hhigh_itg[iarm][iitg]->Fit(fit,"QR+");          
	}

        high_out_txt<<iarm<<" "<<iitg<<" "<<i<<" "
                    <<fit->GetParameter(0)<<" "
                    <<fit->GetParameter(1)<<" "
                    <<fit->GetParameter(2)<<" "
                    <<fit->GetNDF()
                    <<endl;

        sprintf(fname,"fit_low_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit = new TF1(fname,fit0,32*i+24576*iarm,i*32+31+24576*iarm,3);
	if(low_ndf[iarm][iitg][i]>11){
	  fit->FixParameter(0,low_par0[iarm][iitg][i]);
          fit->FixParameter(1,low_par1[iarm][iitg][i]);
	  fit->FixParameter(2,low_par2[iarm][iitg][i]);
	  hlow_itg[iarm][iitg]->Fit(fit,"QR+");
	}
	else{
          fit->SetLineColor(kGreen);
	  hlow_itg[iarm][iitg]->Fit(fit,"QR+");
	}
        low_out_txt<<iarm<<" "<<iitg<<" "<<i<<" "
                   <<fit->GetParameter(0)<<" "
                   <<fit->GetParameter(1)<<" "
                   <<fit->GetParameter(2)<<" "
                   <<fit->GetNDF()
                   <<endl;
      }
    }//iarm
  }//iitg
 

  TFile* ofile = new TFile("work_2016_09_12/output_row_cut_pol2_with_cut_refit_ndf_11.root","RECREATE");
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      hhigh_itg[iarm][iitg]->Write();
      hlow_itg[iarm][iitg]->Write();
    }
  }
}

//linear
Double_t fit0(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
  return result;
}

