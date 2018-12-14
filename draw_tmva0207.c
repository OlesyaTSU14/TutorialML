//#include "/Users/okuchins/Olesya_work/Hmumu/Hmumu/BootRoot/atlasstyle-00-03-03/AtlasUtils.C"
//#include "/Users/okuchins/Olesya_work/Hmumu/Hmumu/BootRoot/atlasstyle-00-03-03/AtlasStyle.C"

TString FilePrefix;
TString VarName;

void draw_tmva0207()
{

//    SetAtlasStyle();
    
    //TFile *f = new TFile("/Users/okuchins/Olesya_work/Hmumu/analysis/TMVA.root");
    TFile *f = new TFile("/Users/okuchins/Olesya_work/Hmumu/analysis/TMVA.root", "UPDATE");
    
    
    if (!f) {
        cout << "/n Error: cannot open file!";
        return;
    }
    
    VarName = "dimuonmass";
    

    
    TTree *testTree = (TTree* ) f->Get("dataset/TestTree");
    TTree *trainTree = (TTree* ) f->Get("dataset/TrainTree");
    
    int nbins = 1;
    double xmin = 110;
    double xmax = 135;

    
    TCanvas* canvas = new TCanvas("Plot", "Canvas: ", 200, 10, 800, 800);
    canvas->SetLeftMargin(0.00);
    canvas->SetRightMargin(0.00);
    canvas->SetTopMargin(0.00);
    canvas->SetBottomMargin(0.00);

    canvas->Divide(5, 2);              
	canvas->cd(1); 
    
    TH1F* hsig_test = new TH1F("hsig_test", "hsig_test", nbins, xmin, xmax);
    TH1F* hbkg_test = new TH1F("hbkg_test", "hbkg_test", nbins, xmin, xmax);
    TH1F* hsig_train = new TH1F("hsig_train", "hsig_train", nbins, xmin, xmax);
    TH1F* hbkg_train = new TH1F("hbkg_train", "hbkg_train", nbins, xmin, xmax);
    //TH1F* hsig_sum = new TH1F("hsig_sum", "hsig_sum", nbins, xmin, xmax);
    
    //TString Selection = Zpt<15
    testTree->Draw("dimuonmass>>hsig_test","((classID==0)*totweight)*36.1*1000","");
    testTree->Draw("dimuonmass>>hbkg_test","((classID==1)*1)","");
    trainTree->Draw("dimuonmass>>hsig_train","((classID==0)*totweight)*36.1*1000","");
    trainTree->Draw("dimuonmass>>hbkg_train","((classID==1)*1)","");
    

    double integral;
    double norm;
    norm = 1;

    double c_bkg = hbkg_train->Integral()/hbkg_test->Integral() +1;
    cout << "\n   c_bkg = " << c_bkg << "  \n  ";

    double c_sig = (hsig_train->Integral()/hsig_test->Integral()) +1;
    cout << "\n   c_sig = " << c_sig << "  \n  ";
    
    integral = hsig_test->Integral();
    cout << "\n   hsig_test = " << integral << "  \n  ";
    //Double_t scale_test_hsig=norm/hsig_test->Integral();
    //hsig_test->Scale(scale_test_hsig);
    //cout << "\n test_scale_hsig = " << scale_test_hsig << " \n";

    
    //hsig->SetName("hsig_test");
    
    //hsig->Write();
    //hsig->Draw();
    
    integral =hbkg_test->Integral();
    cout << "\n   hbkg_test = " << integral << "  \n  ";
    //Double_t scale_test_hbkg=norm/hbkg_test->Integral();
    //hbkg_test->Scale(scale_test_hbkg);
    //cout << "\n test_scale_hbkg = " << scale_test_hbkg << " \n";
    
    //hbkg->SetName("hbkg_test");
    
    //hbkg->Write();
    //hbkg->Draw();

    integral =hsig_train->Integral();
    cout << "\n   hsig_train = " << integral << "  \n  ";
    //Double_t scale_train_hsig= norm / hsig_train->Integral();
    //hsig_train->Scale(scale_train_hsig);
    //cout << "\n train_scale_hsig = " << scale_train_hsig << " \n";
    
    //hsig->SetName("hsig_train");

    
    //hsig->Write();
    //hsig->Draw();
    
    integral =hbkg_train->Integral();
    cout << "\n   hbkg_train = " << integral << "  \n  ";

    //Double_t scale_train_hbkg=norm / hbkg_train->Integral();
    //hbkg_train->Scale(scale_train_hbkg);
    //cout << "\n train_scale_hbkg = " << scale_train_hbkg << " \n";
    
    //hbkg->SetName("hbkg_train");
    
    //hbkg->Write();
    //hbkg->Draw();
    

    //double sum_int_test = hsig_test->Integral() + hbkg_test->Integral();
    //double sum_int_train = hsig_train->Integral() + hbkg_train->Integral();
    //double sum_int_total = sum_int_hsig + sum_int_hbkg;

    //cout << "\n   sum_int_test = " << sum_int_test << "  \n  ";
    //cout << "\n   sum_int_train = " << sum_int_train << "  \n  ";
    

    //double int_total = sum_int_test + sum_int_train;
    //cout << "\n   int_total = " << int_total << "  \n  ";
    



    //hbkg_train->Draw();
    //hsig_train->Draw("same hist");
    //hsig_train->Scale(100); 
    //hbkg_train->SetLineColor(kBlue); 
    //hsig_train->SetLineColor(kRed);

    //hsig_test + hsig_train = sum_int_hsig;
    //hbkg_test + bkg_train = sum_int_hbkg;
    //cout << "\n   sum_int_hsig = " << sum_int_hsig << "  \n  ";
    //cout << "\n   sum_int_hbkg = " << sum_int_hbkg << "  \n  ";
   
    
    TPad* pad1 = new TPad("", "", 0.0, 0.2016 + 0.03, 1.0, 1.00, -1, -1, 0);
    TPad* pad2 = new TPad("", "", 0.0, 0.00,   1.0, 0.28 + 0.027, -1, -1, 0);
    
    pad1->SetLeftMargin(0.13);
    pad2->SetLeftMargin(0.13);

    pad1->SetRightMargin(0.06);
    pad2->SetRightMargin(0.06);

    pad1->SetBottomMargin(0.145);
    pad2->SetTopMargin(0.00);
    pad2->SetBottomMargin(0.3);
    
    pad1->Draw();
    pad2->Draw();
    
    // pad 3
    //TPad* pad3 = new TPad("", "", 0.0, 0.2016 + 0.03, 1.0, 1.00, -1, -1, 0);
    
    //pad3->SetLeftMargin(0.13);
    
    //pad3->SetRightMargin(0.06);
    
//    pad3->SetBottomMargin(0.145);
//    pad3->SetTopMargin(0.00);
//    pad3->SetBottomMargin(0.3);
//
//    pad3->Draw();
    //

    pad1->cd();
    
    //gPad->SetLogy(m_doLog);
    
    //hbkg_test->Add(hbkg_train);
    //hsig_test->Add(hsig_train);
    TH1F* hsig = (TH1F*) hsig_test->Clone();
    TH1F* hbkg = (TH1F*) hbkg_test->Clone();


    hbkg->Draw("hist");
    hsig->Draw("same_hist");

    hbkg->SetTitle("TEST");

    hsig->Scale(100*c_sig);
    hbkg->Scale(1*c_bkg);
    hsig->SetLineColor(kRed);
    hbkg->SetLineColor(kBlue);
    
    //hsig_sum = hsig_test + hsig_train;
    //hsig_sum->Draw();

    
    //hbkg_train->Draw("hist");
    //hsig_train->Draw("same_hist");
    //hsig_train->SetLineColor(kRed);
    //hbkg_train->SetLineColor(kBlue);
    
    //
    
//    pad1->cd(1);
    
    //TH1F* sumHistHsig = (TH1F*) hsig_test->Clone();
    // TH1F* sumHistHbkg = (TH1F*) hbkg_test->Clone();
    
    // sumHistHbkg->Draw("same hist");
    // sumHistHsig->Draw("same hist");
    // sumHistHsig->Add(hsig_train);
    // sumHistHbkg->Add(hbkg_train);
    // sumHistHsig->Scale(100);
    // sumHistHsig->SetLineColor(kBlack);
    // sumHistHbkg->SetLineColor(kGreen);
    
//    legend = new TLegend(0.65, 0.55, 0.9, 0.9);
//    legend->AddEntry(sumHistHsig,"sumHistHsig","l");
//    legend->AddEntry(sumHistHbkg,"sumHistHbkg","l");
//    legend->Draw();
    
//    pad1->Draw();
    
    //


    auto legend = new TLegend(0.65, 0.55, 0.9, 0.9);
    legend->AddEntry(hbkg_test,"bkg_test","l");
    legend->AddEntry(hsig_test,"sig_test*100","l");
    //legend->AddEntry(sumHistHsig,"Hsig_totall","l");
    //legend->AddEntry(sumHistHbkg,"Hbkg_totall","l");
    legend->Draw();


    pad2->cd();
   
    TAxis* rxAxis = 0;
    TAxis* ryAxis = 0;
    
    //TH1F* h_data = new TH1F("hsig_test", "hsig_test", nbins, xmin, xmax);
    
    pad2->SetLeftMargin(0.13);
    
    pad2->SetRightMargin(0.06);
    
    pad2->SetTopMargin(0.00);
    pad2->SetBottomMargin(0.5);
    
    TH1F* hratio = (TH1F*) hsig_test->Clone();
    pad2->GetFrame()->SetFillColor(18);
    hratio->SetFillColor(45);
    //hratio->Draw();
    //TPaveLabel *label1 = new TPaveLabel(-3.5,700,-1,800,"Default option");
    //label1->SetFillColor(42);
    //label1->Draw();
    
    hratio->Divide(hbkg_test);
    hratio->Draw("hist");
    //hsig_test/hbkg_test
    
    double sum_sig = 0.;
    double sum_bkg = 0.;
    double sum_signif = 0.;
    for (int i = 1; i <= hsig_test->GetNbinsX(); i++) {
       double sig = hsig_test->GetBinContent(i);
       double bkg = hbkg_test->GetBinContent(i);
     if (bkg < 10.) continue;
       sum_sig += sig;
       sum_bkg += bkg;
       sum_signif += sig*sig/bkg;
    printf("%d : (sig = %6.1f) / (bkg = %6.1f) : (sig/sqrt(bkg) = %4.3f), (sig/bkg=%4.5f)\n", i, sig, bkg, sig/sqrt(bkg), sig/bkg);
        
    }
    double s1 = sum_sig/sqrt(sum_bkg);
    double s2 = sqrt(sum_signif);
    printf(" (sum_sig/sqrt(sum_bkg) = %5.4f) : (%5.4f =  sqrt(sum_signif)) == %3.2f%% = (s2/s1 - 1.)*100.\n", s1, s2, (s2/s1 - 1.)*100.);
    
    
    hratio->SetLineColor(kBlack);
    hratio->SetFillColor(kBlack);
    hratio->SetFillStyle(1);
    hratio->SetLineWidth(2);
    
    hratio->SetLineColor(kBlack);
    
    rxAxis = hratio->GetXaxis();
    ryAxis = hratio->GetYaxis();
    
    ryAxis->SetTitle("hratio");
    ryAxis->CenterTitle(true);
    
    rxAxis->SetTitleOffset(1.1);
    ryAxis->SetTitleOffset(0.6);
    
    rxAxis->SetTitleSize(0.11);
    ryAxis->SetTitleSize(0.11);
    
    rxAxis->SetLabelSize(0.1);
    ryAxis->SetLabelSize(0.1);
    
    rxAxis->SetTickLength(0.07);
    

//    pad3->cd(1);
//
//    TH1F* sumHistHsig = (TH1F*) hsig_test->Clone();
//        TH1F* sumHistHbkg = (TH1F*) hbkg_test->Clone();
//
//    sumHistHbkg->Draw("sumHistHbkg");
//    pad3->cd(2);
//    sumHistHsig->Draw("sumHistHsig");
////    sumHistHsig->Add(hsig_train);
////    sumHistHbkg->Add(hbkg_train);
//    sumHistHsig->SetLineColor(kBlack);
//    sumHistHbkg->SetLineColor(kBlue);
//
//
//
//    legend = new TLegend(0.65, 0.55, 0.9, 0.9);
//    legend->AddEntry(sumHistHsig,"sumHistHsig","l");
//    legend->AddEntry(sumHistHbkg,"sumHistHbkg","l");
//    legend->Draw();
//
//    pad3->Draw();
    
    
//    TH1F* hsig_test = new TH1F("hsig_test", "hsig_test", nbins, xmin, xmax);
//    TH1F* hbkg_test = new TH1F("hbkg_test", "hbkg_test", nbins, xmin, xmax);
//    TH1F* hsig_train = new TH1F("hsig_train", "hsig_train", nbins, xmin, xmax);
//    TH1F* hbkg_train = new TH1F("hbkg_train", "hbkg_train", nbins, xmin, xmax);

    
    
    //ryAxis->SetRangeUser(0.00001, 0.0029999);
    //ryAxis->SetRangeUser(0.0 + 0.00001, 0.005 - 0.00001);


    //TString nameTestBkg = "bkg_test";
    TString nameTestSig = "hsig_test";
    TString nameTestBkg = "hbkg_test";

    TString nameTitle = "NoName";
    
    TString cutBase_sig = "((classID==0)*totweight)*36.1*1000";
    TString cutBase_bkg= "((classID==1)*1)";

    TString cut_sig;
    TString cut_bkg;

	TString cutCentralLow    = "*( (Zpt < 15) && ((fabs(leadeta) < 1.0) && (fabs(subleadeta) < 1.0)) * (BDT < 0.7))";
    TString cutNonCentralLow = "*( (Zpt < 15) && ((fabs(leadeta) > 1.0) || (fabs(subleadeta) > 1.0)) * (BDT < 0.7))";
    
    TString cutCentralMedium    = "*( (((Zpt > 15) && (Zpt < 50)) && ((fabs(leadeta) < 1.0) && (fabs(subleadeta) < 1.0)) )*(BDT<0.7) )";
    TString cutNonCentralMedium = "*( (((Zpt > 15) && (Zpt<50)) && ((fabs(leadeta) > 1.0) || (fabs(subleadeta) > 1.0)) )*(BDT<0.7) )";

    TString cutCentralHigh    = "*( (Zpt>50) && ((fabs(leadeta) < 1.0) && (fabs(subleadeta) < 1.0))*(BDT<0.7))";
    TString cutNonCentralHigh = "*( (Zpt>50) && ((fabs(leadeta) > 1.0) || (fabs(subleadeta) > 1.0))*(BDT<0.7))";

    TString cutVBFloose = "*(0.7<BDT && BDT<0.9)";
    TString cutVBFtight = "*(BDT>0.9)";


    // double sum_sig = 0.;
    // double sum_bkg = 0.;
    // double sum_signif = 0.;
    // for (int i = 1; i <= hsig_test->GetNbinsX(); i++) {
    //    double sig = hsig_test->GetBinContent(i);
    //    double bkg = hbkg_test->GetBinContent(i);
    //  if (bkg < 10.) continue;
    //    sum_sig += sig;
    //    sum_bkg += bkg;
    //    sum_signif += sig*sig/bkg;
    // printf("%d : (sig = %6.1f) / (bkg = %6.1f) : (sig/sqrt(bkg) = %4.3f), (sig/bkg=%4.5f)\n", i, sig, bkg, sig/sqrt(bkg), sig/bkg);
        
 
 for (int j = 1; j < 9; j++) {
     canvas->cd(1 + j);

    
	cut_sig = cutBase_sig;
    cut_bkg = cutBase_bkg;

    //cutName += cutName;
  if ( j == 1) {
     cut_sig += cutCentralLow;
      cut_bkg += cutCentralLow;
     nameTitle = "CentralLow";

	
 	}
  if ( j == 2) {
 	 cut_sig += cutNonCentralLow;
      cut_bkg += cutNonCentralLow;
 	 nameTitle = "NonCentralLow";

 	}
 
 if (j == 3) {
 	 cut_sig += cutCentralMedium;
      cut_bkg += cutCentralMedium;
 	 nameTitle = "CentralMedium";
 }
 if (j == 4) {
 	 cut_sig += cutNonCentralMedium;
      cut_bkg += cutNonCentralMedium;
 	 nameTitle = "NonCentralMedium";
}
 if (j == 5) {
 	 cut_sig += cutCentralHigh;
      cut_bkg += cutCentralHigh;
 	 nameTitle = "CentralHigh";
 }
 if (j == 6) {
 	 cut_sig += cutNonCentralHigh;
      cut_bkg += cutNonCentralHigh;
     nameTitle = "NonCentralHigh";


 }
 if (j == 7) {
 	cut_sig += cutVBFloose;
     cut_bkg += cutVBFloose;
    nameTitle = "cutVBFloose";


 }
if (j == 8) {
 	cut_sig += cutVBFtight;
     cut_bkg += cutVBFtight;
    nameTitle = "cutVBFtight";

    //  if ( j == 2) {
    //  cut_sig += cutallC;
    //   cut_bkg += cutallC;
    //  nameTitle = "CentralLow";
    // }


    //  if ( j == 3) {
    //  cut_sig += cutallN;
    //   cut_bkg += cutallN;
    //  nameTitle = "CentralLow";
    //}
 }

    testTree->Draw("dimuonmass>>hsig_test",cut_sig,"");
    testTree->Draw("dimuonmass>>hbkg_test",cut_bkg,"");

    

    hsig = (TH1F*) hsig_test->Clone();
    hbkg = (TH1F*) hbkg_test->Clone();


    hbkg->Draw("hist");
    hsig->Draw("same_hist");

    hbkg->SetTitle(nameTitle);

    hsig->Scale(100*c_sig);
    hbkg->Scale(1*c_bkg);
    hsig->SetLineColor(kRed);
    hbkg->SetLineColor(kBlue);

    //canvas->cd();
    //legend->AddEntry(hbkg_test,"bkg_test","");
    //legend->Draw();
    auto legendCut = new TLegend(0.65, 0.55, 0.9, 0.9);
    legendCut->AddEntry(hbkg_test, nameTestBkg,"l");
    legendCut->AddEntry(hsig_test, nameTestSig,"l");
    //legend->AddEntry(sumHistHsig,"Hsig_totall","l");
    //legend->AddEntry(sumHistHbkg,"Hbkg_totall","l");
    legendCut->Draw();


    double sum_sig = 0.;
    double sum_bkg = 0.;
    double sum_signif = 0.;
    for (int i = 1; i <= hsig_test->GetNbinsX(); i++) {
       double sig = hsig_test->GetBinContent(i);
       double bkg = hbkg_test->GetBinContent(i);
     if (bkg < 10.) continue;
       sum_sig += sig;
       sum_bkg += bkg;
       sum_signif += sig*sig/bkg;
    printf("%d : (sig = %6.1f) / (bkg = %6.1f) : (sig/sqrt(bkg) = %4.3f), (sig/bkg=%4.5f)\n", i, sig, bkg, sig/sqrt(bkg), sig/bkg);
        
    }
    double s1 = sum_sig/sqrt(sum_bkg);
    double s2 = sqrt(sum_signif);
    printf(" (sum_sig/sqrt(sum_bkg) = %5.4f) : (%5.4f =  sqrt(sum_signif)) == %3.2f%% = (s2/s1 - 1.)*100.\n", s1, s2, (s2/s1 - 1.)*100.);
    
    
}



    canvas->Modified();
    canvas->Update();
    
    canvas->SetLineColor(kRed);
    canvas->SetLineColor(kBlue);
    
    if (FilePrefix != "") {
        canvas->SaveAs(FilePrefix + VarName + ".pdf");
    }
}


    



