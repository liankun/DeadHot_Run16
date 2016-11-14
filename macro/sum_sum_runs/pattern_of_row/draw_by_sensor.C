void draw_by_sensor(){
  TFile* ifile = new TFile("work_2016_09_09/Integral_deadhot_deadhot_cut.root");
  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];
  TH1D* hhigh_itg_sensor_odd[2][5][24];
  TH1D* hlow_itg_sensor_odd[2][5][24];
  TH1D* hhigh_itg_sensor_even[2][5][24];
  TH1D* hlow_itg_sensor_even[2][5][24];

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
        sprintf(hname,"hhigh_adc_sensor%d_arm%d_integral%d_even",isensor,iarm,iitg);
	hhigh_itg_sensor_even[iarm][iitg][isensor]=new TH1D(hname,hname,4*128+20,-0.5-10,4*128-0.5+10);
        sprintf(hname,"hlow_adc_sensor%d_arm%d_integral%d_even",isensor,iarm,iitg);
	hlow_itg_sensor_even[iarm][iitg][isensor]=new TH1D(hname,hname,4*128+20,-0.5-10,4*128-0.5+10);
	sprintf(hname,"hhigh_adc_sensor%d_arm%d_integral%d_odd",isensor,iarm,iitg);
	hhigh_itg_sensor_odd[iarm][iitg][isensor]=new TH1D(hname,hname,4*128+20,-0.5-10,4*128-0.5+10);
        sprintf(hname,"hlow_adc_sensor%d_arm%d_integral%d_odd",isensor,iarm,iitg);
	hlow_itg_sensor_odd[iarm][iitg][isensor]=new TH1D(hname,hname,4*128+20,-0.5-10,4*128-0.5+10);
      }//isensor
    }//iitg
  }//iarm

  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      for(int isensor = 0;isensor < 24;isensor++){
        for(int ilayer=0;ilayer<8;ilayer=ilayer+2){
          for(int ich=0;ich<128;ich++){
//            if(ilayer%2==0) continue;
	    int new_ch=isensor*128+24*128*ilayer+ich;
            double content0=hhigh_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    double content1=hlow_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    if(content0>1)hhigh_itg_sensor_even[iarm][iitg][isensor]->Fill(ich+128*ilayer/2,content0);
	    if(content1>1)hlow_itg_sensor_even[iarm][iitg][isensor]->Fill(ich+128*ilayer/2,content1);
	  }//ich
	}//ilayer
        for(int ilayer=1;ilayer<8;ilayer=ilayer+2){
          for(int ich=0;ich<128;ich++){
	    int new_ch=isensor*128+24*128*ilayer+ich;
            double content0=hhigh_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    double content1=hlow_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    if(content0>1)hhigh_itg_sensor_odd[iarm][iitg][isensor]->Fill(ich+128*(ilayer-1)/2,content0);
	    if(content1>1)hlow_itg_sensor_odd[iarm][iitg][isensor]->Fill(ich+128*(ilayer-1)/2,content1);
	  }//ich
        }//ilayer
      
      }//isensor
    }//iarm
  }//iitg

  TFile* ofile = new TFile("work_2016_09_09/output_sensor_cut.root","RECREATE");
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      for(int isensor=0;isensor<24;isensor++){
        hhigh_itg_sensor_even[iarm][iitg][isensor]->Write();
	hlow_itg_sensor_even[iarm][iitg][isensor]->Write();
        hhigh_itg_sensor_odd[iarm][iitg][isensor]->Write();
	hlow_itg_sensor_odd[iarm][iitg][isensor]->Write();
      }
    }
  }

}
