void draw_by_group(){
  TFile* ifile = new TFile("work_2016_09_09/Integral_deadhot_deadhot_cut.root");
  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];
  TH1D* hhigh_itg_group_odd[2][5][7];
  TH1D* hlow_itg_group_odd[2][5][7];
  TH1D* hhigh_itg_group_even[2][5][7];
  TH1D* hlow_itg_group_even[2][5][7];

  int group_south[4][6]={
                         {0,1,2,3,4,5},
		         {6,0,2,3,4,5},
			 {0,1,2,3,4,5},
			 {6,0,2,3,4,5}
		        };

  int group_north[4][6]={
                         {6,0,2,3,4,5},
		         {0,1,2,3,4,5},
		         {6,0,2,3,4,5},
			 {0,1,2,3,4,5}
	                };


 for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hhigh_itg[iarm][iitg])cout<<"get null for hhigh_itg "<<endl;
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)ifile->Get(hname);
      if(!hlow_itg[iarm][iitg])cout<<"get null for hlow_itg "<<endl;
      for(int igroup=0;igroup<7;igroup++){
        sprintf(hname,"hhigh_adc_group%d_arm%d_integral%d_even",igroup,iarm,iitg);
	hhigh_itg_group_even[iarm][iitg][igroup]=new TH1D(hname,hname,16*128+20,-0.5-10,16*128-0.5+10);
        sprintf(hname,"hlow_adc_group%d_arm%d_integral%d_even",igroup,iarm,iitg);
	hlow_itg_group_even[iarm][iitg][igroup]=new TH1D(hname,hname,16*128+20,-0.5-10,16*128-0.5+10);
	sprintf(hname,"hhigh_adc_group%d_arm%d_integral%d_odd",igroup,iarm,iitg);
	hhigh_itg_group_odd[iarm][iitg][igroup]=new TH1D(hname,hname,16*128+20,-0.5-10,16*128-0.5+10);
        sprintf(hname,"hlow_adc_group%d_arm%d_integral%d_odd",igroup,iarm,iitg);
	hlow_itg_group_odd[iarm][iitg][igroup]=new TH1D(hname,hname,16*128+20,-0.5-10,16*128-0.5+10);
      }//igroup
    }//iitg
  }//iarm

  for(int iitg=1;iitg<5;iitg++){
    for(int iarm=0;iarm < 2;iarm++){
      int group_even_ich[7]={0};
      for(int isensor = 0;isensor < 24;isensor++){
        for(int ilayer=0;ilayer<8;ilayer=ilayer+2){
	  for(int ich=0;ich<128;ich++){
	    int new_ch=isensor*128+24*128*ilayer+ich;
            double content0=hhigh_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    double content1=hlow_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    int quarant = (int)(isensor/6);
	    int the_sensor = isensor%6;
	    int group = group_south[quarant][the_sensor];
	    if(iarm==1){
              group = group_north[quarant][the_sensor];  
	    }
	    group_even_ich[group]++;
	    if(content0>1)hhigh_itg_group_even[iarm][iitg][group]->Fill(group_even_ich[group],content0);
	    
	    if(content1>1)hlow_itg_group_even[iarm][iitg][group]->Fill(group_even_ich[group],content1);
	  }//ich
	}//ilayer
        int group_odd_ich[7]={0};
	for(int ilayer=1;ilayer<8;ilayer=ilayer+2){
          for(int ich=0;ich<128;ich++){
	    int new_ch=isensor*128+24*128*ilayer+ich;
            double content0=hhigh_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    double content1=hlow_itg[iarm][iitg]->GetBinContent(new_ch+1);
	    int quarant = (int)(isensor/6);
	    int the_sensor = isensor%6;
	    int group = group_south[quarant][the_sensor];
	    if(iarm==1){
              group = group_north[quarant][the_sensor];  
	    }
	    group_odd_ich[group]++;
	    if(content0>1)hhigh_itg_group_odd[iarm][iitg][group]->Fill(group_odd_ich[group],content0);
	    if(content1>1)hlow_itg_group_odd[iarm][iitg][group]->Fill(group_odd_ich[group],content1);
	  }//ich
        }//ilayer 
      }//isensor
    }//iarm
  }//iitg

  TFile* ofile = new TFile("work_2016_09_11/output_group_cut.root","RECREATE");
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=1;iitg<5;iitg++){
      for(int igroup=0;igroup<7;igroup++){
        hhigh_itg_group_even[iarm][iitg][igroup]->Write();
	hlow_itg_group_even[iarm][iitg][igroup]->Write();
        hhigh_itg_group_odd[iarm][iitg][igroup]->Write();
	hlow_itg_group_odd[iarm][iitg][igroup]->Write();
      }
    }
  }

}
