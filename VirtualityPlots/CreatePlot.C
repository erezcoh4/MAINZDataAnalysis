
#define MAX 10000

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TProfile * GetProfile(int hNumber){
    //    20 =  PWBA (RC) - 3, 21 = DWIA+MEC+IC (NR) - 5 , 22 = DWIA (RC) - 6 , 23 = DWIA+MEC+IC (RC) - 7
    TAnalysis ana;
    return ana.GetProfileFromFile("VirtualityModels.root",Form("h%d_pfx",hNumber));
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DrawVirtualityPlot( TString Name, const int N, TProfile ** fp, TString * Names , Int_t * colors , Int_t * styles){

    TPlots plot;
    plot.CreateCanvas(Name);
    
    // declerations
    double  Xmin = -0.11 , Xmax = 0.065 , Ymin = 0.54 , Ymax = 1.31;
    double  vL[N][MAX]  , ratioL[N][MAX] , vR[N][MAX]  , ratioR[N][MAX] , v;
    int     NL[N]       , NR[N];
    TGraph  * gL[N]     , * gR[N] ;
    TH1F    *frame = plot.DrawFrame(Name,100,Xmin,Xmax,Ymin,Ymax,"#nu [GeV ^{2}]","(P_{x}/P_{z})_{^{2}H}/(P_{x}/P_{z})_{H}");
    
    // loop over profiles to divide into left and right graphs (removing the un-smooth part)
    for ( int i = 0 ; i < N ; i++ ) {
        NL[i] = NR[i] = 0;
        for (int bin = 1; bin < fp[i] -> GetNbinsX() ; bin ++ ) {
            v = fp[i] -> GetBinCenter(bin);
            if ( v < -0.03 ) {
                vL[i][NL[i]]       = v;
                ratioL[i][NL[i]]   = fp[i] -> GetBinContent(bin);
                NL[i]++;
            }
            else if ( v > 0.015 ){
                vR[i][NR[i]]       = v;
                ratioR[i][NR[i]]   = fp[i] -> GetBinContent(bin);
                NR[i]++;
            }
        }
        gL[i] = plot.Graph( Form("gL%i",i), NL[i], vL[i], ratioL[i],Name,"#nu [GeV ^{2}]","(P_{x}/P_{z})_{^{2}H}/(P_{x}/P_{z})_{H}", colors[i],0.5 , styles[i], "l same");
        gL[i] -> SetLineWidth(3);
        gR[i] = plot.Graph( Form("gR%i",i), NR[i], vR[i], ratioR[i],Name,"#nu [GeV ^{2}]","(P_{x}/P_{z})_{^{2}H}/(P_{x}/P_{z})_{H}",colors[i],0.5 , styles[i],   "l same");
        gR[i] -> SetLineWidth(3);
    }
    
 
    //change right side axis to have negative valuse
    float v2Label[9] = {-0.10, -0.08 ,-0.06 , -0.04 , -0.02, 0.0, 0.02 , 0.04 , 0.06};
    for (int i = 0; i < 9 ; i++ ) {
        frame -> GetXaxis() -> SetBinLabel((int)frame -> GetXaxis() -> FindBin(v2Label[i]),Form("%.2f",(v2Label[i])?-fabs(v2Label[i]):0));
    }
    frame -> GetXaxis() -> LabelsOption("h");
    frame -> GetXaxis() -> SetLabelSize(0.06);
    
    // add horizontal line and a centeral axis...
    plot.Line(Xmin,1,Xmax,1,1,1,2);
    plot.Axis(0,Ymin,0,Ymax,Ymin,Ymax,510,"-+");
    plot.Axis(Xmin,Ymin,Xmax,Ymin,Xmin,Xmax,510,"+");
    plot.Axis(Xmin,Ymax,Xmax,Ymax,Xmin,Xmax,510,"-");
    plot.Text(-0.06,0.6,"P_{miss} < 0");
    plot.Text(0.015,0.6,"P_{miss} > 0");
    gPad -> SetTicks(1,1);
    
    // add legend...
    plot.AddLegend(N,(TH1 **)gL,Names,"l");
}







void CreatePlot(){
    
    
    gStyle->SetOptStat(0000);
//    TProfile* pModels_RelCor[2] = { GetProfile(24)      , GetProfile(26)        };
//    TString     Names_RelCor[2] = { "DWIA+MEC+IC (NR)"  , "DWIA+MEC+IC (RC)"    };
//    Int_t      colors_RelCor[2] = { 6                   , 2                     };
//    Int_t      styles_RelCor[2] = { 3                   , 1                     };
//    TProfile*    pModels_FSI[3] = { GetProfile(22)      , GetProfile(25)        , GetProfile(26)        };
//    TString        Names_FSI[3] = { "PWBA (RC)"         , "DWIA (RC)"           , "DWIA+MEC+IC (RC)"    };
//    Int_t         colors_FSI[3] = { 4                   , 3                     , 2                     };
//    Int_t         styles_FSI[3] = { 9                   , 10                     , 1                     };
//    DrawVirtualityPlot("Relativistic corrections" , 2 , pModels_RelCor , Names_RelCor , colors_RelCor , styles_RelCor);
//    DrawVirtualityPlot("FSI" , 3 , pModels_FSI , Names_FSI , colors_FSI , styles_FSI);
    

    TProfile*    pModels[4] = { GetProfile(22)      , GetProfile(25)        , GetProfile(26)        , GetProfile(24)      };
    TString        Names[4] = { "PWBA (RC)"         , "DWIA (RC)"           , "DWIA+MEC+IC (RC)"    , "DWIA+MEC+IC (NR)"  };
    Int_t         colors[4] = { 4                   , 3                     , 2                     , 2                   };
    Int_t         styles[4] = { 9                   , 10                    , 1                     , 7                   };
    DrawVirtualityPlot("" , 4 , pModels , Names , colors , styles);

}



