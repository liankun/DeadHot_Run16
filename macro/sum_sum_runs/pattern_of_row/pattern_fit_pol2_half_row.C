#include<map>
#include<fstream>
void pattern_fit_pol2_half_row(){
  TFile* ifile = new TFile("work_2016_09_06/Integral_deadhot_deadhot_cut.root");  

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
 
//  ofstream high_out_txt("fit_high_pol2_half_row.txt");
//  ofstream low_out_txt("fit_low_pol2_half_row.txt");
  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int i = 0;i < 192*4*2;i++){
        char fname[500];
	sprintf(fname,"fit_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit = new TF1(fname,fit0,16*i+24576*iarm,i*16+15+24576*iarm,3);
        hhigh_itg[iarm][iitg]->Fit(fit,"QR+");
	double chi2 = fit->GetChisquare();
	int ndf = fit->GetNDF();
	/*
	high_out_txt<<iarm<<" "<<iitg<<" "<<i<<" "
	       <<fit->GetParameter(0)<<" "
	       <<fit->GetParameter(1)<<" "
	       <<fit->GetParameter(2)<<" "
	       <<endl;
        */
	if(ndf>0) hfit_chi2[iarm][iitg]->Fill(chi2/ndf);
	else hfit_chi2[iarm][iitg]->Fill(0);
        sprintf(fname,"fit_low_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit = new TF1(fname,fit0,16*i+24576*iarm,i*16+15+24576*iarm,3);
	hlow_itg[iarm][iitg]->Fit(fit,"QR+");
      	/*
	low_out_txt<<iarm<<" "<<iitg<<" "<<i<<" "
	       <<fit->GetParameter(0)<<" "
	       <<fit->GetParameter(1)<<" "
	       <<fit->GetParameter(2)<<" "
	       <<endl;
        */
      }
    }//iarm
  }//iitg
 

  TFile* ofile = new TFile("work_2016_09_07/output_cut_pol2_half_row.root","RECREATE");
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      hhigh_itg[iarm][iitg]->Write();
      hfit_chi2[iarm][iitg]->Write();
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

