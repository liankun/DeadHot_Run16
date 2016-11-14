#include <set>
#include <map>
void deadhot_diff_norm(int runNumber = 0){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);

//  TFile* file = new TFile("sum_sum0.root","READONLY");
  char path[500];
//  sprintf(path,"%d/sum_sum.root",runNumber);
  TFile* file = new TFile("all_runs.root","READONLY");
    
  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");

  MpcExMapper* mapper = MpcExMapper::instance();

  ifstream bad_high_itg_total("high_deadhot_group44_row_only.txt");
  
  ifstream bad_low_itg_total("low_deadhot_group44_row_only.txt");

  std::set<int> bad_rms_list_h;
  std::set<int> bad_rms_list_l;
  std::set<int> bad_mean_list_h;
  std::set<int> bad_mean_list_l;
  std::set<int> bad_high_itg_list;
  std::set<int> bad_low_itg_list;

  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];
  TH2D* hhigh_rphi_itg[2][8][5];
  TH2D* hlow_rphi_itg[2][8][5];

  TH2D* hhigh_r_itg[2][8][5];
  TH2D* hlow_r_itg[2][8][5];

  //single channel distribution 
  //according to distance
  TH1D* hhigh_r_itg_minipad[2][8][9][5];
  TH1D* hlow_r_itg_minipad[2][8][9][5];

  TH1D* hhigh_itg_globle[2][8][5];
  TH1D* hlow_itg_globle[2][8][5];


  //map them according to phi
  map<int,double> high_r_itg_minipad_map[2][8][9][5];
  map<int,double> low_r_itg_minipad_map[2][8][9][5];

  TH2D* hhigh_nxy[2][8][5];
  TH2D* hlow_nxy[2][8][5];

  double high_itg_begin_type0[2][5]={{0,15,45,80,120},{0,15,30,50,80}};
  double high_itg_end_type0[2][5]={{15,45,80,120,200},{15,30,50,80,150}};
  double high_itg_begin_type1[2][5]={{0,10,40,75,115},{0,10,25,45,75}};
  double high_itg_end_type1[2][5]={{10,40,75,115,195},{10,25,45,75,145}};

  double low_itg_begin[5] = {0,5,15,25,40};
  double low_itg_end[5] = {5,15,25,40,100};

//  double high_range[2][5]={{100000,100000,30000,14000,10000},
//                           {15000,20000,10000,5000,10000}};
//  double low_range[2][5]={{100000,100000,20000,10000,6000},
//                          {10000,20000,4000,2000,1000}};

  double high_range[2][5]={{100000*43,100000*43,30000*43,14000*43,10000*43},
                           {15000*43,20000*43,10000*43,5000*43,10000*43}};
  double low_range[2][5]={{100000*43,100000*43,20000*43,10000*43,6000*43},
                          {10000*43,20000*43,4000*43,2000*43,1000*43}};

  
//  Double_t rbins[10] ={6.5,9,10.5,11.9,13.5,14.8,15.8,16.8,18.0,21.5};
  Double_t rbins[10]={6.5,9,10.5,12.1,13.5,14.4,15.6,16.8,18.1,21.5};

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
  
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=0;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = new TH1D(hname,hname,24576,iarm*24576-0.5,(iarm+1)*24576-0.5);
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = new TH1D(hname,hname,24576,iarm*24576-0.5,(iarm+1)*24576-0.5);
      for(int ilayer = 0;ilayer < 8;ilayer++){
        sprintf(hname,"hhigh_rphi_arm%d_itg%d_layer%d",iarm,iitg,ilayer);
	hhigh_rphi_itg[iarm][ilayer][iitg] = new TH2D(hname,hname,300,0,30,30,-5,5);
	sprintf(hname,"hlow_rphi_arm%d_itg%d_layer%d",iarm,iitg,ilayer);
	hlow_rphi_itg[iarm][ilayer][iitg] = new TH2D(hname,hname,300,0,30,30,-5,5);
      
        sprintf(hname,"hhigh_r_arm%d_itg%d_layer%d",iarm,iitg,ilayer);
	hhigh_r_itg[iarm][ilayer][iitg] = new TH2D(hname,hname,9,rbins,400,0,high_range[iarm][iitg]);
        hhigh_r_itg[iarm][ilayer][iitg]->GetXaxis()->SetTitle("R/cm");
	hhigh_r_itg[iarm][ilayer][iitg]->GetYaxis()->SetTitle("Integrated ADC");
	
	sprintf(hname,"hlow_r_arm%d_itg%d_layer%d",iarm,iitg,ilayer);
	hlow_r_itg[iarm][ilayer][iitg] = new TH2D(hname,hname,9,rbins,400,0,low_range[iarm][iitg]);
        hlow_r_itg[iarm][ilayer][iitg]->GetXaxis()->SetTitle("R/cm");
	hlow_r_itg[iarm][ilayer][iitg]->GetYaxis()->SetTitle("Integrated ADC");

        int Nx = 198*2;
        float ScaleX = 1;
        int Ny = 24*2;
        float ScaleY = 8;
        if(ilayer%2 == 1){
          Nx = 24*2;
          ScaleX = 8;
          Ny = 198*2;
          ScaleY = 1;
        }

        sprintf(hname,"hhigh_nxy_layer%d_arm%d_itg%d",ilayer,iarm,iitg);
        hhigh_nxy[iarm][ilayer][iitg] = new TH2D(hname,hname,Nx,-0.5*ScaleX,(Nx-0.5)*ScaleX,Ny,-0.5*ScaleY,(Ny-0.5)*ScaleY);

        sprintf(hname,"hlow_nxy_layer%d_arm%d_itg%d",ilayer,iarm,iitg);
        hlow_nxy[iarm][ilayer][iitg] = new TH2D(hname,hname,Nx,-0.5*ScaleX,(Nx-0.5)*ScaleX,Ny,-0.5*ScaleY,(Ny-0.5)*ScaleY);
       
        sprintf(hname,"hhigh_itg_globle_arm%d_layer%d_itg%d",iarm,ilayer,iitg);
        hhigh_itg_globle[iarm][ilayer][iitg] =  new TH1D(hname,hname,198*24,-0.5,198*24-0.5);

        sprintf(hname,"hlow_itg_globle_arm%d_layer%d_itg%d",iarm,ilayer,iitg);
        hlow_itg_globle[iarm][ilayer][iitg] =  new TH1D(hname,hname,198*24,-0.5,198*24-0.5);

	for(int ir = 0;ir < 9;ir++){
          sprintf(hname,"hhigh_r_itg_minipad_arm%d_layer%d_r%d_itg%d",iarm,ilayer,ir,iitg);
	  hhigh_r_itg_minipad[iarm][ilayer][ir][iitg] = new TH1D(hname,hname,400,-0.5,400-0.5);
	  sprintf(hname,"hlow_r_itg_minipad_arm%d_layer%d_r%d_itg%d",iarm,ilayer,ir,iitg);
	  hlow_r_itg_minipad[iarm][ilayer][ir][iitg] = new TH1D(hname,hname,400,-0.5,400-0.5);
	}//ir
      }//ilayer
    }//iitg
  }//iarm

  int key;
  int new_key;
  double rms;
  double mean;
  
  while(bad_high_itg_total>>key){
//    cout<<key<<" "<<endl;
//    bad_high_itg_list.insert(key);
  }

   while(bad_low_itg_total>>key){
//    cout<<key<<" "<<endl;
//    bad_low_itg_list.insert(key);
  }
    
    
  int the_minipad_high[2][8][9][5]={{{{0}}}};
  int the_minipad_low[2][8][9][5]={{{{0}}}};

  for(int i = 0;i < 24576*2;i++){
    hhigh_adc_key->SetAxisRange(i,i,"X");
    hlow_adc_key->SetAxisRange(i,i,"X");
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    int index = 6*quadrant+sensor;
    int lx = mapper->get_lx(i);
    int ly = mapper->get_ly(i);
    int nx = mapper->get_nx(i);
    int ny = mapper->get_ny(i);
    int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
    int row = 96*layer+index*4+ly;
    double pos_x = mapper->get_x(i);
    double pos_y = mapper->get_y(i);
    int phi_scale =atan2(pos_y,pos_x)*1800;
    int globle_key=nx+198*ny;
    if(layer%2 == 1) globle_key=ny+198*nx;

    double r = sqrt(pos_x*pos_x+ pos_y*pos_y);
    int n = -1;
    for(int ibin=0;ibin<9;ibin++){
      if(r >=rbins[ibin] && r <rbins[ibin+1]){
	n = ibin;
        break;
      }
    }

    if(n < 0){
      cout<<"bad r "<<r<<endl;
      return;
    }

    
    double phi = atan2(pos_y,pos_x);
    TH1D* htemp0 = hhigh_adc_key->ProjectionY();
    TH1D* htemp1 = hlow_adc_key->ProjectionY();
//    if(htemp0->GetEntries() < 10) continue;
    

    for(int iitg = 1;iitg<5;iitg++){
      char fname[500];
      sprintf(fname,"fit_high_arm%d_itg%d_row%d",arm,iitg,row);
      TF1* fit0 = new TF1(fname,fit,32*row+24576*iarm,row*32+31+24576*iarm,3);
      fit0->FixParameter(0,high_par0[arm][iitg][row]);
      fit0->FixParameter(1,high_par1[arm][iitg][row]);
      fit0->FixParameter(2,high_par2[arm][iitg][row]);
     
      sprintf(fname,"fit_low_arm%d_itg%d_row%d",iarm,iitg,i);
      TF1* fit1 = new TF1(fname,fit,32*i+24576*iarm,i*32+31+24576*iarm,3);
      fit1->FixParameter(0,low_par0[arm][iitg][row]);
      fit1->FixParameter(1,low_par1[arm][iitg][row]);
      fit1->FixParameter(2,low_par2[arm][iitg][row]);

      double rval = fit0->Eval(32*row+24576*arm+16);
      double val = fit0->Eval(new_key);

      double high_begin = high_itg_begin_type0[arm][iitg];
      double high_end = high_itg_end_type0[arm][iitg];
      
      if(layer > 1){
        high_begin = high_itg_begin_type1[arm][iitg];
	high_end = high_itg_end_type1[arm][iitg];
      }
      int high_begin_bin = htemp0->FindBin(high_begin);
      int high_end_bin = htemp0->FindBin(high_end);
      double itegral0 = htemp0->Integral(high_begin_bin,high_end_bin);
      
      if(bad_high_itg_list.find(i) == bad_high_itg_list.end()){
        hhigh_itg[arm][iitg]->Fill(new_key,itegral0*rval/val);
	hhigh_rphi_itg[arm][layer][iitg]->Fill(r,phi,itegral0);
	hhigh_r_itg[arm][layer][iitg]->Fill(r,itegral0);
	hhigh_nxy[arm][layer][iitg]->SetBinContent(2*nx+1+1,2*ny+1+1,itegral0);
        high_r_itg_minipad_map[arm][layer][n][iitg].insert(pair<int,double>(phi_scale,itegral0));
        hhigh_itg_globle[arm][layer][iitg]->Fill(globle_key,itegral0);
      }

      double low_begin = low_itg_begin[iitg];
      double low_end = low_itg_end[iitg];
      int low_begin_bin = htemp1->FindBin(low_begin);
      int low_end_bin = htemp1->FindBin(low_end); 
      double itegral1 = htemp1->Integral(low_begin_bin,low_end_bin);
      
      rval = fit1->Eval(32*row+24576*arm+16);
      val = fit1->Eval(new_key);

      if(bad_low_itg_list.find(i) == bad_low_itg_list.end()){
	hlow_itg[arm][iitg]->Fill(new_key,itegral1*rval/val);
	hlow_rphi_itg[arm][layer][iitg]->Fill(r,phi,itegral1);
	hlow_r_itg[arm][layer][iitg]->Fill(r,itegral1);
        hlow_nxy[arm][layer][iitg]->SetBinContent(2*nx+1+1,2*ny+1+1,itegral1);
        low_r_itg_minipad_map[arm][layer][n][iitg].insert(pair<int,double>(phi_scale,itegral1));
        hlow_itg_globle[arm][layer][iitg]->Fill(globle_key,itegral1);
      }
      delete fit0;
      delete fit1;
    }//iitg
  }//i

  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg = 0;iitg<5;iitg++){
      for(int ilayer = 0;ilayer < 8;ilayer++){
        for(int ir = 0;ir < 9;ir++){
	  int high_count=0;
	  for(map<int,double>::iterator it=high_r_itg_minipad_map[iarm][ilayer][ir][iitg].begin();it!=high_r_itg_minipad_map[iarm][ilayer][ir][iitg].end();++it){
            hhigh_r_itg_minipad[iarm][ilayer][ir][iitg]->Fill(high_count,it->second);
	    high_count++;
	  }
	  int low_count=0;
	  for(map<int,double>::iterator it=low_r_itg_minipad_map[iarm][ilayer][ir][iitg].begin();it!=low_r_itg_minipad_map[iarm][ilayer][ir][iitg].end();++it){
            hlow_r_itg_minipad[iarm][ilayer][ir][iitg]->Fill(low_count,it->second);
	    low_count++;
	  }
	}
      }
    }
  }
  

  TFile* ofile = new TFile("work_2016_09_12/Integral_deadhot_deadhot_no_cut_norm.root","RECREATE");
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg = 1;iitg<5;iitg++){
      hhigh_itg[iarm][iitg]->Write();
      hlow_itg[iarm][iitg]->Write();
      for(int ilayer = 0;ilayer < 8;ilayer++){
//       hhigh_rphi_itg[iarm][ilayer][iitg]->Write();
//       hlow_rphi_itg[iarm][ilayer][iitg]->Write();
//        hhigh_r_itg[iarm][ilayer][iitg]->Write();
//        hlow_r_itg[iarm][ilayer][iitg]->Write();
//        hhigh_nxy[iarm][ilayer][iitg]->Write();
//        hlow_nxy[iarm][ilayer][iitg]->Write();
        hhigh_itg_globle[iarm][ilayer][iitg]->Write();
	hlow_itg_globle[iarm][ilayer][iitg]->Write();
//	for(int ir = 0;ir < 9;ir++){
//          hhigh_r_itg_minipad[iarm][ilayer][ir][iitg]->Write();
//	  hlow_r_itg_minipad[iarm][ilayer][ir][iitg]->Write();
//        }
      }
    }
  }
}

Double_t fit(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
  return result;
}
