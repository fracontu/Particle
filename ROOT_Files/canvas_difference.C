#ifdef __CLING__
#pragma cling optimize(0)
#endif
void canvas_difference()
{
//=========Macro generated from canvas: c1_n4/c1_n4
//=========  (Fri Nov  4 11:24:20 2022) by ROOT version 6.26/04
   TCanvas *c1_n4 = new TCanvas("c1_n4", "c1_n4",10,31,700,500);
   c1_n4->Range(0,0,1,1);
   c1_n4->SetFillColor(0);
   c1_n4->SetBorderMode(0);
   c1_n4->SetBorderSize(2);
   c1_n4->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c1_n4_1
   TPad *c1_n4_1 = new TPad("c1_n4_1", "c1_n4_1",0.01,0.01,0.49,0.99);
   c1_n4_1->Draw();
   c1_n4_1->cd();
   c1_n4_1->Range(-0.375,-18542.55,3.375,51847.98);
   c1_n4_1->SetFillColor(0);
   c1_n4_1->SetBorderMode(0);
   c1_n4_1->SetBorderSize(2);
   c1_n4_1->SetFrameBorderMode(0);
   c1_n4_1->SetFrameBorderMode(0);
   
   TH1F *h1mIh2__13 = new TH1F("h1mIh2__13","h1-h2",50,0,3);
   h1mIh2__13->SetBinContent(5,3599);
   h1mIh2__13->SetBinContent(6,-2307);
   h1mIh2__13->SetBinContent(7,8277);
   h1mIh2__13->SetBinContent(8,4506);
   h1mIh2__13->SetBinContent(9,6262);
   h1mIh2__13->SetBinContent(10,1505);
   h1mIh2__13->SetBinContent(11,4444);
   h1mIh2__13->SetBinContent(12,-952);
   h1mIh2__13->SetBinContent(13,-3595);
   h1mIh2__13->SetBinContent(14,19131);
   h1mIh2__13->SetBinContent(15,32988);
   h1mIh2__13->SetBinContent(16,38164);
   h1mIh2__13->SetBinContent(17,7902);
   h1mIh2__13->SetBinContent(18,321);
   h1mIh2__13->SetBinContent(19,3305);
   h1mIh2__13->SetBinContent(20,-3525);
   h1mIh2__13->SetBinContent(21,2723);
   h1mIh2__13->SetBinContent(22,16);
   h1mIh2__13->SetBinContent(23,-1748);
   h1mIh2__13->SetBinContent(24,-2703);
   h1mIh2__13->SetBinContent(25,551);
   h1mIh2__13->SetBinContent(26,-4397);
   h1mIh2__13->SetBinContent(27,1888);
   h1mIh2__13->SetBinContent(28,-5066);
   h1mIh2__13->SetBinContent(29,-840);
   h1mIh2__13->SetBinContent(30,2007);
   h1mIh2__13->SetBinContent(31,2025);
   h1mIh2__13->SetBinContent(32,-309);
   h1mIh2__13->SetBinContent(33,3917);
   h1mIh2__13->SetBinContent(34,2437);
   h1mIh2__13->SetBinContent(35,3868);
   h1mIh2__13->SetBinContent(36,1111);
   h1mIh2__13->SetBinContent(37,1047);
   h1mIh2__13->SetBinContent(38,3562);
   h1mIh2__13->SetBinContent(39,539);
   h1mIh2__13->SetBinContent(40,-1352);
   h1mIh2__13->SetBinContent(41,-3319);
   h1mIh2__13->SetBinContent(42,2022);
   h1mIh2__13->SetBinContent(43,-7160);
   h1mIh2__13->SetBinContent(44,492);
   h1mIh2__13->SetBinContent(45,-136);
   h1mIh2__13->SetBinContent(46,-132);
   h1mIh2__13->SetBinContent(47,-3496);
   h1mIh2__13->SetBinContent(48,-1233);
   h1mIh2__13->SetBinContent(49,-2425);
   h1mIh2__13->SetBinContent(50,-1140);
   h1mIh2__13->SetBinContent(51,-3665);
   h1mIh2__13->SetBinError(5,2343.599);
   h1mIh2__13->SetBinError(6,4229.85);
   h1mIh2__13->SetBinError(7,4386.031);
   h1mIh2__13->SetBinError(8,4399.525);
   h1mIh2__13->SetBinError(9,4342.034);
   h1mIh2__13->SetBinError(10,4236.397);
   h1mIh2__13->SetBinError(11,4473.54);
   h1mIh2__13->SetBinError(12,4691.397);
   h1mIh2__13->SetBinError(13,4497.071);
   h1mIh2__13->SetBinError(14,4312.722);
   h1mIh2__13->SetBinError(15,4136.437);
   h1mIh2__13->SetBinError(16,3963.383);
   h1mIh2__13->SetBinError(17,3842.173);
   h1mIh2__13->SetBinError(18,3768.16);
   h1mIh2__13->SetBinError(19,4405.267);
   h1mIh2__13->SetBinError(20,4106.702);
   h1mIh2__13->SetBinError(21,3915.8);
   h1mIh2__13->SetBinError(22,3748.57);
   h1mIh2__13->SetBinError(23,3599.517);
   h1mIh2__13->SetBinError(24,3492.021);
   h1mIh2__13->SetBinError(25,3505.653);
   h1mIh2__13->SetBinError(26,3351.788);
   h1mIh2__13->SetBinError(27,3217.097);
   h1mIh2__13->SetBinError(28,3094.612);
   h1mIh2__13->SetBinError(29,2977.419);
   h1mIh2__13->SetBinError(30,2865.862);
   h1mIh2__13->SetBinError(31,2760.042);
   h1mIh2__13->SetBinError(32,2747.211);
   h1mIh2__13->SetBinError(33,2646.185);
   h1mIh2__13->SetBinError(34,2536.184);
   h1mIh2__13->SetBinError(35,2436.133);
   h1mIh2__13->SetBinError(36,2341.178);
   h1mIh2__13->SetBinError(37,2251.101);
   h1mIh2__13->SetBinError(38,2167.035);
   h1mIh2__13->SetBinError(39,2083.913);
   h1mIh2__13->SetBinError(40,2006.737);
   h1mIh2__13->SetBinError(41,1932.445);
   h1mIh2__13->SetBinError(42,1859.889);
   h1mIh2__13->SetBinError(43,1789.646);
   h1mIh2__13->SetBinError(44,1724.935);
   h1mIh2__13->SetBinError(45,1660.3);
   h1mIh2__13->SetBinError(46,1600.052);
   h1mIh2__13->SetBinError(47,1541.645);
   h1mIh2__13->SetBinError(48,1485.904);
   h1mIh2__13->SetBinError(49,1432.43);
   h1mIh2__13->SetBinError(50,1380.509);
   h1mIh2__13->SetBinError(51,5190.783);
   h1mIh2__13->SetEntries(26.6001);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.655,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("Entries = 27     ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.6592 #pm      0");
   ptstats_LaTex = ptstats->AddText("Std Dev   =      0 #pm      0");
   ptstats_LaTex = ptstats->AddText("Underflow =      0");
   ptstats_LaTex = ptstats->AddText("Overflow  =  -3665");
   ptstats->SetOptStat(112210);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   h1mIh2__13->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h1mIh2__13);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1mIh2__13->SetLineColor(ci);
   h1mIh2__13->GetXaxis()->SetLabelFont(42);
   h1mIh2__13->GetXaxis()->SetTitleOffset(1);
   h1mIh2__13->GetXaxis()->SetTitleFont(42);
   h1mIh2__13->GetYaxis()->SetLabelFont(42);
   h1mIh2__13->GetYaxis()->SetTitleFont(42);
   h1mIh2__13->GetZaxis()->SetLabelFont(42);
   h1mIh2__13->GetZaxis()->SetTitleOffset(1);
   h1mIh2__13->GetZaxis()->SetTitleFont(42);
   h1mIh2__13->Draw("");
   
   TPaveText *pt = new TPaveText(0.4228438,0.94,0.5771562,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("h1-h2");
   pt->Draw();
   c1_n4_1->Modified();
   c1_n4->cd();
  
// ------------>Primitives in pad: c1_n4_2
   TPad *c1_n4_2 = new TPad("c1_n4_2", "c1_n4_2",0.51,0.01,0.99,0.99);
   c1_n4_2->Draw();
   c1_n4_2->cd();
   c1_n4_2->Range(-0.375,-0.13125,3.375,1.18125);
   c1_n4_2->SetFillColor(0);
   c1_n4_2->SetBorderMode(0);
   c1_n4_2->SetBorderSize(2);
   c1_n4_2->SetFrameBorderMode(0);
   c1_n4_2->SetFrameBorderMode(0);
   
   TH1F *h3mIh4__14 = new TH1F("h3mIh4__14","h3-h4",50,0,3);
   
   ptstats = new TPaveStats(0.78,0.655,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   ptstats_LaTex = ptstats->AddText("Entries = 0      ");
   ptstats_LaTex = ptstats->AddText("Mean  =      0 #pm      0");
   ptstats_LaTex = ptstats->AddText("Std Dev   =      0 #pm      0");
   ptstats_LaTex = ptstats->AddText("Underflow =      0");
   ptstats_LaTex = ptstats->AddText("Overflow  =      0");
   ptstats->SetOptStat(112210);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   h3mIh4__14->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h3mIh4__14);

   ci = TColor::GetColor("#000099");
   h3mIh4__14->SetLineColor(ci);
   h3mIh4__14->GetXaxis()->SetLabelFont(42);
   h3mIh4__14->GetXaxis()->SetTitleOffset(1);
   h3mIh4__14->GetXaxis()->SetTitleFont(42);
   h3mIh4__14->GetYaxis()->SetLabelFont(42);
   h3mIh4__14->GetYaxis()->SetTitleFont(42);
   h3mIh4__14->GetZaxis()->SetLabelFont(42);
   h3mIh4__14->GetZaxis()->SetTitleOffset(1);
   h3mIh4__14->GetZaxis()->SetTitleFont(42);
   h3mIh4__14->Draw("");
   
   pt = new TPaveText(0.4228438,0.94,0.5771562,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   pt_LaTex = pt->AddText("h3-h4");
   pt->Draw();
   c1_n4_2->Modified();
   c1_n4->cd();
   c1_n4->Modified();
   c1_n4->cd();
   c1_n4->SetSelected(c1_n4);
}
