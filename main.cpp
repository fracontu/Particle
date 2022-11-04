#include <math.h>

#include <iostream>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

// DOMANDE IMPORTANTI:
/*

*/

// roba per compilare in root (non so se serve)
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"
#include "TStyle.h"

// Il codice di prova usato per il Lab1 sta dopo il main

void Main() { /*Da file: Compilazione ed esecuzione programma di generazione*/
              /*Consiglio: creare uno script .sh che automatizzi il tutto.
              Oppure uno script separato per caricare le classi e uno per eseguire il main
              senza dover entrare ogni volta dentro a ROOT.*/ /*Che significa sta cosa */

  R__LOAD_LIBRARY(ParticleType_cpp.so);  // Se le metto fuori non funzionano
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
  Histo_Phi_Angles->GetYaxis()->SetRange(980000, 120000);
  TH1F *Histo_Theta_Angles =
      new TH1F("Theta Angle", "Theta Angle", 100, 0, M_PI);
  Histo_Phi_Angles->GetYaxis()->SetRange(980000, 120000);
  TH1F *Histo_Impulse = new TH1F("Impulse", "Impulse", 100, 0, 7);
  TH1F *Histo_Impulse_Transverse =
      new TH1F("Impulse Transverse", "Impulse Transverse", 100, 0, 5);
  TH1F *Histo_Energy = new TH1F("Energy", "Energy", 100, 0, 10);

  TH1F *Histo_InvMass =
      new TH1F("InvMass", "Invariant Mass", 100, 0, 3);  // ok i range?
  Histo_InvMass->Sumw2();

  TH1F *Histo_InvMass_SameCharge = new TH1F(
      "Invariant Mass Same Charge", "Invariant Mass Same Charge", 50, 0, 3);
  Histo_InvMass_SameCharge->Sumw2();

  TH1F *Histo_InvMass_DifferentCharge =
      new TH1F("Invariant Mass Different Charge",
               "Invariant Mass Different Charge", 50, 0, 3);
  Histo_InvMass_DifferentCharge->Sumw2();

  TH1F *Histo_InvMassDiscordantPionKaon =
      new TH1F("Invariant Mass Discordant Pion Kaon",
               "Invariant Mass Discordant Pion Kaon", 50, 0, 3);
  Histo_InvMassDiscordantPionKaon->Sumw2();

  TH1F *Histo_InvMassConcordantPionKaon =
      new TH1F("Invariant Mass Concordant Pion Kaon",
               "Invariant Mass Concordant Pion Kaon", 20, 0.5, 2.3);
  Histo_InvMassConcordantPionKaon->Sumw2();

  TH1F *Histo_InvMassDecadeParticles =
      new TH1F("Invariant Mass Decade Particles",
               "Invariant Mass Decade Particles", 100, 0.3, 2.3);
  Histo_InvMassDecadeParticles->Sumw2();

  int NumOfDecades = 0;
  // loop dei 1E5 eventi
  for (int j = 0; j < 1E5; j++) {  // metti 10 fa 1E5
    int DauPosition =
        99;  // per il loop, devo poterlo aumentare di 1 la prima volta

    for (int i = 0; i < 100; i++) {  // tutta sta roba è da riscrivere meglio
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
      // prova a fare ste cose con uno switch

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

    // loop per le masse invarianti standard
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

    // loop per le masse invarianti con pioni e kaoni. Sono divisi sennò tutto
    // insieme non si capisce nulla, tanto a livello di implementazione non
    // cambia quasi nulla
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
  Histo_InvMassDecadeParticles->Write();  // Di questo fai anche fit gaussiano

  Histo_File->Close();

  /*START DATA ANALYSIS*/

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

  TF1 *exp = new TF1("exp", "[0]*TMath::Exp(x*[1]) ", 0, 7);
  Histo_Impulse->Fit("exp", "Q");
  std::cout << '\n' << "Histo_Impulse FIT.\n";
  std::cout << "Mean: " << exp->GetParameter(1) << " +- " << exp->GetParError(1)
            << " (Expected -1)" << '\n';
  std::cout << "Chisquare: " << (exp->GetChisquare()) / (exp->GetNDF()) << '\n';

  TF1 *exp2 = new TF1("exp2", "[0]*TMath::Exp(x*[1]) ", 0, 7);
  Histo_Impulse_Transverse->Fit("exp2", "Q");
  std::cout << '\n' << "Histo_Impulse_Transverse FIT.\n";
  std::cout << "Mean: " << exp2->GetParameter(1) << " +- "
            << exp2->GetParError(1) << " (Expected -1)" << '\n';
  std::cout << "Chisquare: " << (exp2->GetChisquare()) / (exp2->GetNDF())
            << '\n';

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

  TCanvas *canvas2 = new TCanvas();
  canvas2->Divide(2, 3);
  canvas2->cd(1);
  Histo_InvMass->Draw();
  canvas2->cd(2);
  Histo_InvMass_SameCharge->Draw();
  canvas2->cd(3);
  Histo_InvMass_DifferentCharge->Draw();
  canvas2->cd(4);
  Histo_InvMassDiscordantPionKaon->Draw();
  canvas2->cd(5);
  Histo_InvMassConcordantPionKaon->Draw();
  canvas2->cd(6);
  Histo_InvMassDecadeParticles->Draw();

  canvas1->Print("./ROOT_Files/canvas_stats.pdf");
  canvas1->Print("./ROOT_Files/canvas_stats.root");
  canvas1->Print("./ROOT_Files/canvas_stats.C");

  canvas2->Print("./ROOT_Files/canvas_invmass.pdf");
  canvas2->Print("./ROOT_Files/canvas_invmass.root");
  canvas2->Print("./ROOT_Files/canvas_invmass.C");

  TH1F *Histo12 =
      new TH1F("h1-h2", "h1-h2", 50, 0, 3);  // sumw2 va anche su questo?
  // Histo12->Sumw2()
  Histo12->Add(Histo_InvMass_DifferentCharge, Histo_InvMass_SameCharge, 1, -1);
  TH1F *Histo34 = new TH1F("h3-h4", "h3-h4", 50, 0, 3);
  // Histo34->Sumw2()
  Histo34->Add(Histo_InvMassDiscordantPionKaon, Histo_InvMassConcordantPionKaon,
               1, -1);

  TCanvas *canvas3 = new TCanvas();
  canvas3->Divide(2, 1);
  canvas3->cd(1);
  Histo12->Draw();
  canvas3->cd(2);
  Histo34->Draw();

  canvas3->Print("./ROOT_Files/canvas_difference.pdf");
  canvas3->Print("./ROOT_Files/canvas_difference.root");
  canvas3->Print("./ROOT_Files/canvas_difference.C");

  TF1 *gaus12 = new TF1();
  TF1 *gaus34 = new TF1();

  /*END DATA ANALYSIS*/

  std::cout << std::endl
            << "----------------------DEBUG---------------------------\n";
  std::cout << "BENCHMARK INSIDE LOOP (Mean and RMS should be 0.89166): \n";
  std::cout << "Mean : " << Histo_InvMassDecadeParticles->GetMean() << '\n';
  std::cout << "RMS : " << Histo_InvMassDecadeParticles->GetRMS() << '\n';

  std::cout << "NUMBER OF DECADES :" << NumOfDecades << '\n';
  std::cout << "---------------------END-DEBUG---------------------------\n";
}