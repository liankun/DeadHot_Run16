#include<map>
#include<fstream>
#include<set>

void pattern_fit_pol2_on_nocut(){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);

  MpcExMapper* mapper = MpcExMapper::instance();

  TFile* ifile = new TFile("../work_2016_09_21/Integral_deadhot_deadhot_fit_40p_cut.root");  
  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];

  TH1D* hfit_chi2[2][5];

  ifstream in_bad_high_txt("fitting_over_5chi2_new.txt");
  ifstream in_bad_low_txt("fitting_over_5chi2_new.txt");

  int key;
  set<int> high_set;
  set<int> low_set;

  while(in_bad_high_txt>>key){
    high_set.insert(key);
  }

  while(in_bad_low_txt>>key){
    low_set.insert(key);
  }





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
 
  ifstream high_in_txt("../work_2016_09_21/fit_high_pol2_refit2.txt");
  ifstream low_in_txt("../work_2016_09_21/fit_low_pol2_refit2.txt");

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
 
  
 
  TFile* ofile = new TFile("output_cut_with_refit_curve.root","RECREATE");
  
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      char cname[500];
      sprintf(cname,"c_high_arm%d_itg%d",iarm,iitg);
      TCanvas* c = new TCanvas(cname);
      hhigh_itg[iarm][iitg]->Draw("");
      for(set<int>::iterator it=high_set.begin();it!=high_set.end();++it){
        int key=(*it);
	int arm = mapper->get_arm(key);
        int layer = mapper->get_layer(key);
        int quadrant = mapper->get_quadrant(key);
        int sensor = mapper->get_sensor_in_quadrant(key);
        int index = 6*quadrant+sensor;
        int lx = mapper->get_lx(key);
        int ly = mapper->get_ly(key);
        int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
        if(arm!=iarm) continue;
	double content=hhigh_itg[iarm][iitg]->GetBinContent(new_key+1-iarm*24*128*8);
	TMarker* marker = new TMarker(new_key,content,23);
	c->cd();
	marker->DrawClone("same");
	delete marker;
      }
      c->Write();
      
      sprintf(cname,"c_low_arm%d_itg%d",iarm,iitg);
      TCanvas* c = new TCanvas(cname);
      hlow_itg[iarm][iitg]->Draw("");
      for(set<int>::iterator it=low_set.begin();it!=low_set.end();++it){
        int key=(*it);
	int arm = mapper->get_arm(key);
        int layer = mapper->get_layer(key);
        int quadrant = mapper->get_quadrant(key);
        int sensor = mapper->get_sensor_in_quadrant(key);
        int index = 6*quadrant+sensor;
        int lx = mapper->get_lx(key);
        int ly = mapper->get_ly(key);
        int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
        if(arm!=iarm) continue;
	double content=hlow_itg[iarm][iitg]->GetBinContent(new_key+1);
	TMarker* marker = new TMarker(new_key,content,23);
	c->cd();
	marker->DrawClone("same");
	delete marker;

      }
      c->Write();
    }
  }
}

//linear
Double_t fit0(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
  return result;
}

