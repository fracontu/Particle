#include <math.h>

#include <iostream>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "TStyle.h"

void Main() {
  R__LOAD_LIBRARY(ParticleType_cpp.so);
  R__LOAD_LIBRARY(ResonanceType_cpp.so);
  R__LOAD_LIBRARY(Particle_cpp.so);

  Particle::AddParticleType("Pion+", 0.13957, 1);
  Particle::AddParticleType("Pion-", 0.13957, -1);
  Particle::AddParticleType("Kaon+", 0.49367, 1);
  Particle::AddParticleType("Kaon-", 0.49367, -1);
  Particle::AddParticleType("Proton+", 0.93827, 1);
  Particle::AddParticleType("Proton-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.05);

  gRandom->SetSeed();
  int MaxNumEventParticles = 119;
  Particle EventParticles[MaxNumEventParticles];

  TH1F *Histo_Types =
      new TH1F("Type of Particles", "Type of Particles", 7, 0, 7);
  TH1F *Histo_Phi_Angles = new TH1F("Phi Angle", "Phi Angle", 100, 0, 2 * M_PI);
  Histo_Phi_Angles->GetYaxis()->SetRangeUser(980000, 120000);
  TH1F *Histo_Theta_Angles =
      new TH1F("Theta Angle", "Theta Angle", 100, 0, M_PI);
  Histo_Phi_Angles->GetYaxis()->SetRangeUser(980000, 120000);
  TH1F *Histo_Impulse = new TH1F("Impulse", "Impulse", 100, 0, 7);
  TH1F *Histo_Impulse_Transverse =
      new TH1F("Impulse Transverse", "Impulse Transverse", 100, 0, 4);
  TH1F *Histo_Energy = new TH1F("Energy", "Energy", 100, 0, 3);

  TH1D *Histo_InvMass = new TH1D("InvMass", "Invariant Mass", 100, 0, 5);
  Histo_InvMass->Sumw2();

  TH1D *Histo_InvMass_SameCharge = new TH1D(
      "Invariant Mass Same Charge", "Invariant Mass Same Charge", 200, 0, 3);
  Histo_InvMass_SameCharge->Sumw2();

  TH1D *Histo_InvMass_DifferentCharge =
      new TH1D("Invariant Mass Different Charge",
               "Invariant Mass Different Charge", 200, 0, 3);
  Histo_InvMass_DifferentCharge->Sumw2();

  TH1D *Histo_InvMassDiscordantPionKaon =
      new TH1D("Invariant Mass Discordant Pion Kaon",
               "Invariant Mass Discordant Pion Kaon", 200, 0, 3);
  Histo_InvMassDiscordantPionKaon->Sumw2();

  TH1D *Histo_InvMassConcordantPionKaon =
      new TH1D("Invariant Mass Concordant Pion Kaon",
               "Invariant Mass Concordant Pion Kaon", 200, 0, 3);
  Histo_InvMassConcordantPionKaon->Sumw2();

  TH1D *Histo_InvMassDecadeParticles =
      new TH1D("Invariant Mass Decade Particles",
               "Invariant Mass Decade Particles", 100, 0.6, 1.2);
  Histo_InvMassDecadeParticles->Sumw2();

  int NumOfDecades = 0;
  for (int j = 0; j < 1E5; j++) {
    int DauPosition = 99;

    for (int i = 0; i < 100; i++) {
      double phi = gRandom->Uniform(0, 2 * M_PI);
      Histo_Phi_Angles->Fill(phi);
      double theta = gRandom->Uniform(0, M_PI);
      Histo_Theta_Angles->Fill(theta);
      double p = gRandom->Exp(1);
      EventParticles[i].SetP(p * std::sin(theta) * std::cos(phi),
                             p * std::sin(theta) * std::sin(phi),
                             p * std::cos(theta));
      Histo_Impulse->Fill(EventParticles[i].GetImpulseModule());
      Histo_Impulse_Transverse->Fill(
          EventParticles[i].GetTransverseImpulseModule());
      const double ran = gRandom->Rndm();
      // prova con uno switch
      if (ran < 0.4) {
        EventParticles[i].SetParticle("Pion+");
        Histo_Types->Fill(0.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

      } else if (ran > 0.4 && ran < 0.8) {
        EventParticles[i].SetParticle("Pion-");
        Histo_Types->Fill(1.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

      } else if (ran > 0.8 && ran < 0.85) {
        EventParticles[i].SetParticle("Kaon+");
        Histo_Types->Fill(2.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

      } else if (ran > 0.85 && ran < 0.90) {
        EventParticles[i].SetParticle("Kaon-");
        Histo_Types->Fill(3.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

      } else if (ran > 0.90 && ran < 0.945) {
        EventParticles[i].SetParticle("Proton+");
        Histo_Types->Fill(4.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

      } else if (ran > 0.945 && ran < 0.99) {
        EventParticles[i].SetParticle("Proton-");
        Histo_Types->Fill(5.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

      } else if (ran > 0.99) {
        NumOfDecades += 2;
        EventParticles[i].SetParticle("K*");

        // Quella che dopo decade la metto negli istogrammi?
        Histo_Types->Fill(6.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

        double ran2 = gRandom->Rndm();

        if (ran2 < 0.5) {
          ++DauPosition;
          EventParticles[DauPosition].SetParticle("Pion+");
          ++DauPosition;
          EventParticles[DauPosition].SetParticle("Kaon-");

        } else if (ran2 > 0.5) {
          ++DauPosition;
          EventParticles[DauPosition].SetParticle("Pion-");
          ++DauPosition;
          EventParticles[DauPosition].SetParticle("Kaon+");
        }
        EventParticles[i].Decay2body(EventParticles[DauPosition - 1],
                                     EventParticles[DauPosition]);
        double InvMassDecadeParticles =
            EventParticles[DauPosition - 1].GetInvMass(
                EventParticles[DauPosition]);
        Histo_InvMassDecadeParticles->Fill(InvMassDecadeParticles);
      }
    };

    for (int k = 0; k < DauPosition; k++) {
      if (EventParticles[k].GetfIndex() != 6) {
        for (int m = k + 1; m <= DauPosition; m++) {
          if (EventParticles[m].GetfIndex() != 6) {
            Histo_InvMass->Fill(
                EventParticles[k].GetInvMass(EventParticles[m]));
            if (EventParticles[k].GetfCharge() *
                    EventParticles[m].GetfCharge() >
                0) {
              Histo_InvMass_SameCharge->Fill(
                  EventParticles[k].GetInvMass(EventParticles[m]));

            } else {
              Histo_InvMass_DifferentCharge->Fill(
                  EventParticles[k].GetInvMass(EventParticles[m]));
            }
          }
        }
      }
    }

    for (int t = 0; t < DauPosition;
         t++) {  // secondo me sto pezzo si può fare meglio
      for (int u = t + 1; u < DauPosition; u++) {
        if (EventParticles[t].GetfIndex() == 0 ||
            EventParticles[t].GetfIndex() == 1)  // is a pion
        {
          if (EventParticles[u].GetfIndex() == 2 ||
              EventParticles[u].GetfIndex() == 3)  // is a kaon
          {
            if (EventParticles[t].GetfCharge() *
                    EventParticles[u].GetfCharge() >
                0)  // if same sign
            {
              Histo_InvMassConcordantPionKaon->Fill(
                  EventParticles[t].GetInvMass(EventParticles[u]));

            } else {
              Histo_InvMassDiscordantPionKaon->Fill(
                  EventParticles[t].GetInvMass(EventParticles[u]));
            }
          }

        } else if (EventParticles[u].GetfIndex() == 2 ||
                   EventParticles[u].GetfIndex() == 3)  // is a kaon
        {
          if (EventParticles[t].GetfIndex() == 0 ||
              EventParticles[t].GetfIndex() == 1)  // is a pion
          {
            if (EventParticles[t].GetfCharge() *
                    EventParticles[u].GetfCharge() >
                0)  // if same sign
            {
              Histo_InvMassConcordantPionKaon->Fill(
                  EventParticles[t].GetInvMass(EventParticles[u]));
            } else {
              Histo_InvMassDiscordantPionKaon->Fill(
                  EventParticles[t].GetInvMass(EventParticles[u]));
            }
          }
        }
      }
    };
  };

  gStyle->SetOptStat(112210);

  TFile *Histo_File = new TFile("./ROOT_Files/Histo_File.root", "RECREATE");

  Histo_Types->Write();
  Histo_Phi_Angles->Write();
  Histo_Theta_Angles->Write();
  Histo_Impulse->Write();
  Histo_Impulse_Transverse->Write();
  Histo_Energy->Write();

  Histo_InvMass->Write();
  Histo_InvMass_DifferentCharge->Write();
  Histo_InvMass_SameCharge->Write();
  Histo_InvMassDiscordantPionKaon->Write();
  Histo_InvMassConcordantPionKaon->Write();
  Histo_InvMassDecadeParticles->Write();
  Histo_File->Close();

  std::cout << "------::---DATA_ANALYSIS---::------\n";
  std::cout << '\n' << "1) ---::---HISTO_STATS---::---\n";

  std::cout << "Number of particles:\n";
  std::cout << "Pion+ : " << Histo_Types->GetBinContent(1)
            << " (Expected 0.4*1E6)" << '\n';
  std::cout << "Pion- : " << Histo_Types->GetBinContent(2)
            << " (Expected 0.4*1E6)" << '\n';
  std::cout << "Kaon+ : " << Histo_Types->GetBinContent(3)
            << " (Expected 0.05*1E6)" << '\n';
  std::cout << "Kaon- : " << Histo_Types->GetBinContent(4)
            << " (Expected 0.05*1E6)" << '\n';
  std::cout << "Proton+ : " << Histo_Types->GetBinContent(5)
            << " (Expected 0.045*1E6)" << '\n';
  std::cout << "Proton- : " << Histo_Types->GetBinContent(6)
            << " (Expected 0.045*1E6)" << '\n';
  std::cout << "K* : " << Histo_Types->GetBinContent(7) << " (Expected 0.01)"
            << '\n';

  TF1 *costant_phi = new TF1("costant_phi", "[0]", 0, 2 * M_PI);
  TF1 *costant_theta = new TF1("costant_theta", "[0]", 0, M_PI);
  Histo_Phi_Angles->Fit("costant_phi", "Q");
  Histo_Theta_Angles->Fit("costant_theta", "Q");

  std::cout << '\n' << "Histo_Phi_Angles FIT.\n";
  std::cout << "Costant: " << costant_phi->GetParameter(0) << " +- "
            << costant_phi->GetParError(0) << " (Expected 1E5)" << '\n';
  std::cout << "Chisquare: "
            << (costant_phi->GetChisquare()) / (costant_phi->GetNDF()) << '\n';

  std::cout << '\n' << "Histo_Theta_Angles FIT.\n";
  std::cout << "Costant: " << costant_phi->GetParameter(0) << " +- "
            << costant_phi->GetParError(0) << " (Expected 1E5)" << '\n';
  std::cout << "Chisquare: "
            << (costant_phi->GetChisquare()) / (costant_phi->GetNDF()) << '\n';
  /*
    TF1 *exp = new TF1("exp", "[0]*TMath::Exp(x*[1]) ", 0, 7);
    Histo_Impulse->Fit("exp", "Q");
    std::cout << '\n' << "Histo_Impulse FIT.\n";
    std::cout << "Mean: " << exp->GetParameter(1) << " +- " <<
    exp->GetParError(1)
              << " (Expected -1)" << '\n';
    std::cout << "Chisquare: " << (exp->GetChisquare()) / (exp->GetNDF()) <<
    '\n';
  */
  TF1 *exp2 = new TF1("exp2", "[0]*TMath::Exp(x*[1]) ", 0, 7);
  Histo_Impulse_Transverse->Fit("exp2", "Q");
  std::cout << '\n' << "Histo_Impulse_Transverse FIT.\n";
  std::cout << "Mean: " << exp2->GetParameter(1) << " +- "
            << exp2->GetParError(1) << " (Expected -1)" << '\n';
  std::cout << "Chisquare: " << (exp2->GetChisquare()) / (exp2->GetNDF())
            << '\n';

  Histo_Types->SetFillColor(kYellow - 7);
  Histo_Energy->SetFillColor(kRed - 7);
  Histo_Phi_Angles->SetFillColor(kMagenta - 7);
  Histo_Theta_Angles->SetFillColor(kBlue - 7);
  Histo_Impulse->SetFillColor(kCyan - 7);
  Histo_Impulse_Transverse->SetFillColor(kGreen - 7);

  Histo_Types->SetLineStyle(2);
  Histo_Energy->SetLineStyle(2);
  Histo_Phi_Angles->SetLineStyle(2);
  Histo_Theta_Angles->SetLineStyle(2);
  Histo_Impulse->SetLineStyle(2);
  Histo_Impulse_Transverse->SetLineStyle(2);

  TCanvas *canvas1 = new TCanvas();
  canvas1->Divide(2, 3);
  canvas1->cd(1);
  Histo_Types->Draw();
  canvas1->cd(2);
  Histo_Energy->Draw();
  canvas1->cd(3);
  Histo_Phi_Angles->Draw();
  canvas1->cd(4);
  Histo_Theta_Angles->Draw();
  canvas1->cd(5);
  Histo_Impulse->Draw();
  canvas1->cd(6);
  Histo_Impulse_Transverse->Draw();

  Histo_InvMass->SetFillColor(kYellow - 7);
  Histo_InvMass_SameCharge->SetFillColor(kRed - 7);
  Histo_InvMass_DifferentCharge->SetFillColor(kMagenta - 7);
  Histo_InvMassDiscordantPionKaon->SetFillColor(kBlue - 7);
  Histo_InvMassConcordantPionKaon->SetFillColor(kCyan - 7);
  Histo_InvMassDecadeParticles->SetFillColor(kGreen - 7);

  Histo_InvMass->SetLineStyle(2);
  Histo_InvMass_SameCharge->SetLineStyle(2);
  Histo_InvMass_DifferentCharge->SetLineStyle(2);
  Histo_InvMassDiscordantPionKaon->SetLineStyle(2);
  Histo_InvMassConcordantPionKaon->SetLineStyle(2);
  Histo_InvMassDecadeParticles->SetLineStyle(2);

  TCanvas *canvas2 = new TCanvas();
  canvas2->Divide(2, 3);
  canvas2->cd(1);
  Histo_InvMass->Draw("histo");
  canvas2->cd(2);
  Histo_InvMass_SameCharge->Draw("histo");
  canvas2->cd(3);
  Histo_InvMass_DifferentCharge->Draw("histo");
  canvas2->cd(4);
  Histo_InvMassDiscordantPionKaon->Draw("histo");
  canvas2->cd(5);
  Histo_InvMassConcordantPionKaon->Draw("histo");
  canvas2->cd(6);
  Histo_InvMassDecadeParticles->Draw("histo");

  canvas1->Print("./ROOT_Files/canvas_stats.pdf");
  canvas1->Print("./ROOT_Files/canvas_stats.root");
  canvas1->Print("./ROOT_Files/canvas_stats.C");

  canvas2->Print("./ROOT_Files/canvas_invmass.pdf");
  canvas2->Print("./ROOT_Files/canvas_invmass.root");
  canvas2->Print("./ROOT_Files/canvas_invmass.C");

  TH1F *Histo12 = new TH1F("h1-h2", "h1-h2", 200, 0, 3);
  Histo12->Sumw2();
  Histo12->Add(Histo_InvMass_DifferentCharge, Histo_InvMass_SameCharge, 1, -1);
  TH1F *Histo34 = new TH1F("h3-h4", "h3-h4", 200, 0, 3);
  Histo34->Sumw2();
  Histo34->Add(Histo_InvMassDiscordantPionKaon, Histo_InvMassConcordantPionKaon,
               1, -1);

  TF1 *gaus12 = new TF1("gaus12", "gaus", 0.75, 1.05);
  TF1 *gaus34 = new TF1("gaus34", "gaus", 0.75, 1.05);

  Histo12->Fit("gaus12", "Q");
  Histo34->Fit("gaus34", "Q");

  TH1F *Histo12_Range = new TH1F(*Histo12);
  TH1F *Histo34_Range = new TH1F(*Histo34);
  // Histo12_Range->SetRangeUser(0.5, 1.5); //non so perché non va, da sistemare
  // Histo34_Range->SetRangeUser(0.5, 1.5);

  gStyle->SetOptFit(1011);

  Histo12->SetFillColor(30);
  Histo34->SetFillColor(38);

  Histo12->SetLineWidth(2);
  Histo34->SetLineWidth(2);

  Histo12->SetLineStyle(2);
  Histo34->SetLineStyle(2);

  TCanvas *canvas3 = new TCanvas();
  canvas3->Divide(2, 1);
  canvas3->cd(1);
  Histo12->Draw("histo");
  Histo12->Draw("E,same");
  canvas3->cd(2);
  Histo34->Draw("histo");
  Histo34->Draw("e,same");

  canvas3->Print("./ROOT_Files/canvas_difference.pdf");
  canvas3->Print("./ROOT_Files/canvas_difference.root");
  canvas3->Print("./ROOT_Files/canvas_difference.C");

  std::cout << '\n' << "1) ---::---INVARIANT_MASS---::---\n";

  std::cout << "\nHisto12 FIT.\n";
  std::cout << "Mean : " << gaus12->GetParameter(1)
            << " (Expected mass of K*, so 0.89166)\n";
  std::cout << "RMS : " << gaus12->GetParameter(2)
            << " (Expected width of K*, so 0.05)\n";
  std::cout << "Chisquare : " << (gaus12->GetChisquare()) / (gaus12->GetNDF());

  std::cout << "\nHisto34 FIT.\n";
  std::cout << "Mean : " << gaus34->GetParameter(1)
            << " (Expected mass of K*, so 0.89166)\n";
  std::cout << "RMS : " << gaus34->GetParameter(2)
            << " (Expected width of K*, so 0.05)\n";
  std::cout << "Chisquare : " << (gaus34->GetChisquare()) / (gaus34->GetNDF())
            << '\n';
}