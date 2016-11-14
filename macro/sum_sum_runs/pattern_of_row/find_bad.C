#include<set>
#include<map>


void find_bad(){
  TFile* ifile = new TFile("work_2016_09_12/Integral_deadhot_deadhot_no_cut.root");
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);

  MpcExMapper* mapper = MpcExMapper::instance();
  map<int,int>key_to_key;
  for(int i = 0;i < 49152;i++){
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    int index = 6*quadrant+sensor;
    int lx = mapper->get_lx(i);
    int ly = mapper->get_ly(i);
    int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
    key_to_key.insert(pair<int,int>(new_key,i));
  }

  
  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];

  TH1D* hhigh_diff[2][5];
  TH1D* hlow_diff[2][5];

  TH1D* hhigh_stat[2][5];
  TH1D* hlow_stat[2][5];


  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){      
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hhigh_itg[iarm][iitg])cout<<"get null for hhigh_itg "<<endl;
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hlow_itg[iarm][iitg])cout<<"get null for hlow_itg "<<endl;
      sprintf(hname,"hhigh_diff_arm%d_integral%d",iarm,iitg);
      hhigh_diff[iarm][iitg]=new TH1D(hname,hname,24576,iarm*24576-0.5,(iarm+1)*24576-0.5);
      sprintf(hname,"hlow_diff_arm%d_integral%d",iarm,iitg);
      hlow_diff[iarm][iitg]=new TH1D(hname,hname,24576,iarm*24576-0.5,(iarm+1)*24576-0.5);
      sprintf(hname,"hhigh_stat_arm%d_integral%d",iarm,iitg);
      hhigh_stat[iarm][iitg] = new TH1D(hname,hname,200,-10,10);
      sprintf(hname,"hlow_stat_arm%d_integral%d",iarm,iitg);
      hlow_stat[iarm][iitg] = new TH1D(hname,hname,200,-10,10);
    }//iitg
  }//iarm

  ifstream high_in_txt("fit_high_pol2_refit.txt");
  ifstream low_in_txt("fit_low_pol2_refit.txt");

  double high_par0[2][5][192*4];
  double high_par1[2][5][192*4];
  double high_par2[2][5][192*4];
  double low_par0[2][5][192*4];
  double low_par1[2][5][192*4];
  double low_par2[2][5][192*4];

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
  }
  
  while(low_in_txt>>iarm>>iitg>>irow>>par0>>par1>>par2>>ndf){
    low_par0[iarm][iitg][irow]=par0;
    low_par1[iarm][iitg][irow]=par1;
    low_par2[iarm][iitg][irow]=par2;    
  }

  ofstream high_bad_txt("high_bad_list.txt");
  ofstream low_bad_txt("low_bad_list.txt");

  set<int> high_bad_set;
  set<int> low_bad_set;
  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int i = 0;i < 192*4;i++){
      	char fname[500];
	sprintf(fname,"fit_high_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit0 = new TF1(fname,fit,32*i+24576*iarm,i*32+31+24576*iarm,3);
        fit0->FixParameter(0,high_par0[iarm][iitg][i]);
        fit0->FixParameter(1,high_par1[iarm][iitg][i]);
	fit0->FixParameter(2,high_par2[iarm][iitg][i]);

        sprintf(fname,"fit_low_arm%d_itg%d_row%d",iarm,iitg,i);
        TF1* fit1 = new TF1(fname,fit,32*i+24576*iarm,i*32+31+24576*iarm,3);
	fit1->FixParameter(0,low_par0[iarm][iitg][i]);
        fit1->FixParameter(1,low_par1[iarm][iitg][i]);
	fit1->FixParameter(2,low_par2[iarm][iitg][i]);

        set<int> high_diff_set;
	set<int> low_diff_set;
	for(int j = 32*i;j<32*(i+1);j++){
	  double bin_content0=hhigh_itg[iarm][iitg]->GetBinContent(j+1);
          double eval_content0=fit0->Eval(j+iarm*24576);
          if(bin_content0<10){
	    if(high_bad_set.find(24576*iarm+j)==high_bad_set.end()){
	      high_bad_txt<<key_to_key[24576*iarm+j]<<endl;
	      high_bad_set.insert(24576*iarm+j);
	    }
	    continue;
	  }
	  double diff_ratio0=(bin_content0-eval_content0)/eval_content0;
	  hhigh_diff[iarm][iitg]->Fill(24576*iarm+j,(bin_content0-eval_content0)/eval_content0);
	  hhigh_stat[iarm][iitg]->Fill((bin_content0-eval_content0)/eval_content0);
	  
	  if(fabs((bin_content0-eval_content0)/eval_content0)>0.5){
            if(high_bad_set.find(24576*iarm+j)==high_bad_set.end()){
	      high_bad_txt<<key_to_key[24576*iarm+j]<<endl;
	      high_bad_set.insert(24576*iarm+j);
	    }
	  }
	  
	  double bin_content1=hlow_itg[iarm][iitg]->GetBinContent(j+1);
          double eval_content1=fit1->Eval(j+iarm*24576);
          double diff_ratio1=(bin_content1-eval_content1)/eval_content1;

	  if(bin_content1<10){
	    if(low_bad_set.find(24576*iarm+j)==low_bad_set.end()){
              low_bad_txt<<key_to_key[24576*iarm+j]<<endl;
	      low_bad_set.insert(24576*iarm+j);
	    }
	    continue;
	  }
	  hlow_diff[iarm][iitg]->Fill(24576*iarm+j,(bin_content1-eval_content1)/eval_content1);
          hlow_stat[iarm][iitg]->Fill((bin_content1-eval_content1)/eval_content1);
	  
	  if(fabs((bin_content1-eval_content1)/eval_content1)>0.5){
	    if(low_bad_set.find(24576*iarm+j)==low_bad_set.end()){
              low_bad_txt<<key_to_key[24576*iarm+j]<<endl;
	      low_bad_set.insert(24576*iarm+j);
	    }
	  }
	  
	}
	delete fit0;
        delete fit1; 
      }//i
    }//iarm
  }//iitg

  TFile* ofile = new TFile("work_2016_09_12/diff.root","RECREATE");
  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      hhigh_diff[iarm][iitg]->Write();
      hhigh_stat[iarm][iitg]->Write();
      hlow_diff[iarm][iitg]->Write();
      hlow_stat[iarm][iitg]->Write();
    }
  }
}

Double_t fit(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
  return result;
}

