#include<set>
#include<map>

void find_bad_by_order(){
  TFile* ifile = new TFile("work_2016_09_06/Integral_deadhot_deadhot_no_cut.root");
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

  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hhigh_itg[iarm][iitg])cout<<"get null for hhigh_itg "<<endl;
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hlow_itg[iarm][iitg])cout<<"get null for hlow_itg "<<endl;
    }//iitg
  }//iarm

  set<int> high_bad_set;
  set<int> low_bad_set;
  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int i = 0;i < 192*4;i++){
        char fname[500];
        for(int j = 32*i;j<32*(i+1);j++){
          double bin_content0=hhigh_itg[iarm][iitg]->GetBinContent(j+1);
	  if(bin_content0<1) continue;
	  high_bad_set.insert(bin_content0);
	}
      }
    }
  }
}
