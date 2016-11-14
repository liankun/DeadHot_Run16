#include<map>
void pattern_fit(){
//  gSystem->Load("libMyMpcEx.so");
//  recoConsts* rc = recoConsts::instance();
//  rc->set_IntFlag("RUNNUMBER",430013);

  TFile* ifile = new TFile("work_2016_09_06/Integral_deadhot_deadhot_row_cut.root");  
//  MpcExMapper* mapper = MpcExMapper::instance();
  map<int,int>key_to_key;

  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];

  TH1D* hhigh_itg_sensor[2][5][24];
  TH1D* hlow_itg_sensor[2][5][24];

  
    
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hhigh_itg[iarm][iitg])cout<<"get null for hhigh_itg "<<endl;
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hlow_itg[iarm][iitg])cout<<"get null for hlow_itg "<<endl;
      for(int isensor=0;isensor<24;isensor++){
        sprintf(hname,"hhigh_adc_sensor%d_arm%d_integral%d",isensor,iarm,iitg);
	hhigh_itg_sensor[iarm][iitg][isensor]=new TH1D(hname,hname,8*128,-0.5,8*128-0.5);
        sprintf(hname,"hlow_adc_sensor%d_arm%d_integral%d",isensor,iarm,iitg);
	hlow_itg_sensor[iarm][iitg][isensor]=new TH1D(hname,hname,8*128,-0.5,8*128-0.5);

      }//isensor
    }//iitg
  }//iarm
 
 /*
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
 */ 
  
  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int isensor = 0;isensor < 24;isensor++){
        for(int ilayer=0;ilayer<8;ilayer++){
          for(int ich=0;ich<128;ich++){
//            if(ilayer%2==0) continue;
	    int new_ch=isensor*128+24*128*ilayer+ich;
            double content0=hhigh_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    double content1=hlow_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    if(content0>1)hhigh_itg_sensor[iarm][iitg][isensor]->Fill(ich+128*ilayer,content0);
	    if(content1>1)hlow_itg_sensor[iarm][iitg][isensor]->Fill(ich+128*ilayer,content1);
	  }//ich
	}//ilayer
      }//isensor
    }//iarm
  }//iitg
 
  for(int iitg=1;iitg<3;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int isensor = 0;isensor < 24;isensor++){
        for(int ilayer=0;ilayer<8;ilayer++){
	  for(int irow=0;irow<32;irow++){
            char fname[500];
	    sprintf(fname,"fit_arm%d_layer%d_sensor%d_itg%d_row%d",iarm,ilayer,isensor,iitg,irow);
	    TF1* fit = new TF1(fname,fit0,32*irow,irow*32+31,2);
            hhigh_itg_sensor[iarm][iitg][isensor]->Fit(fit,"QR+");
	  }//irow
	}//ilayer
      }//isensor
    }//iarm
  }//iitg


  TFile* ofile = new TFile("work_2016_09_06/output_row_cut2.root","RECREATE");
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      for(int isensor=0;isensor<24;isensor++){
        hhigh_itg_sensor[iarm][iitg][isensor]->Write();
	hlow_itg_sensor[iarm][iitg][isensor]->Write();
      }
    }
  }
}

//linear
Double_t fit0(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]*x[0]+par[1];
  return result;
}

