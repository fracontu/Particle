#include <math.h>

#include <iostream>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

// Il codice di prova usato per il Lab1 sta dopo il main

void Main() { /*Da file: Compilazione ed esecuzione programma di generazione*/
              /*Consiglio: creare uno script .sh che automatizzi il tutto.
              Oppure uno script separato per caricare le classi e uno per eseguire il main
              senza dover entrare ogni volta dentro a ROOT.*/ /*Che significa sta cosa */
  R__LOAD_LIBRARY(ParticleType_cpp.so);  // NON FUNZIONANO
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
  TH1F *Histo_Impulse = new TH1F("Impulse", "Impulse", 100, 0, 10);
  TH1F *Histo_Impulse_Transverse =
      new TH1F("Impulse Transverse", "Impulse Transverse", 100, 0, 5);
  TH1F *Histo_Energy = new TH1F("Energy", "Energy", 100, 0, 10);
  TH1F *Histo_InvMass =
      new TH1F("InvMass", "Invariant Mass", 100, 2000, 5000);  // ok i range?
  Histo_InvMass->Sumw2();
  TH1F *Histo_InvMass_SameCharge =
      new TH1F("Invariant Mass Same Charge", "Invariant Mass Same Charge", 100,
               1000, 00);
  Histo_InvMass_SameCharge->Sumw2();
  TH1F *Histo_InvMass_DifferentCharge =
      new TH1F("Invariant Mass Different Charge",
               "Invariant Mass Different Charge", 100, 1000, 3000);
  TH1F *Histo_InvMassDiscordantPionKaon =
      new TH1F("Invariant Mass Discordant Pion Kaon",
               "Invariant Mass Discordant Pion Kaon", 100, 0, 500);
  TH1F *Histo_InvMassConcordantPionKaon =
      new TH1F("Invariant Mass Concordant Pion Kaon",
               "Invariant Mass Concordant Pion Kaon", 100, 0, 500);

  TH1F *Histo_InvMassDecadeParticles =
      new TH1F("Invariant Mass Decade Particles",
               "Invariant Mass Decade Particles", 100, 0, 3);

  TH1F *Histo_InvMassDecadeParticles2 =
      new TH1F("Invariant Mass Decade Particles",
               "Invariant Mass Decade Particles", 100, 0, 3);

  // loop dei 1E5 eventi
  for (int j = 0; j < 100; j++) {  // metti 10 fa 1E5
    int DauPosition =
        99;  // per il loop, devo poterlo aumentare di 1 la prima volta

    // loop che riempe gli array con le 100 particelle
    // double InvMassDecadeParticles = 0;

    int decades = 0;  // debug

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
        decades = 1;  // debug
        EventParticles[i].SetParticle("K*");

        // Quella che dopo decade la metto negli istogrammi?
        Histo_Types->Fill(6.5);
        Histo_Energy->Fill(EventParticles[i].GetEnergy());

        double ran2 = gRandom->Rndm();

        if (ran2 < 0.5) {
          ++DauPosition;
          EventParticles[DauPosition].SetParticle("Pion+");
          // Per ora fillo con K*, va bene?
          // Histo_Types->Fill(0.5);
          /*Histo_Energy->Fill(EventParticles[DauPosition].GetEnergy()); */  // forse conviene accedere con
                                                                             // l'array dei tipi?
          ++DauPosition;
          EventParticles[DauPosition].SetParticle("Kaon-");
          Histo_Types->Fill(3.5);
          Histo_Energy->Fill(EventParticles[DauPosition].GetEnergy());

        } else if (ran2 > 0.5) {
          ++DauPosition;

          EventParticles[DauPosition].SetParticle("Pion-");
          Histo_Types->Fill(1.5);
          Histo_Energy->Fill(EventParticles[DauPosition].GetEnergy());

          ++DauPosition;

          EventParticles[DauPosition].SetParticle("Kaon+");
          Histo_Types->Fill(2.5);
          Histo_Energy->Fill(EventParticles[DauPosition].GetEnergy());
        }
        EventParticles[i].Decay2body(EventParticles[DauPosition - 1],
                                     EventParticles[DauPosition]);  // NOT debug
        double InvMassDecadeParticles = EventParticles[DauPosition].GetInvMass(
            EventParticles[DauPosition - 1]);
        Histo_InvMassDecadeParticles->Fill(InvMassDecadeParticles);
      }
    };

    if (decades == 1) {
      // std::cout << "Decades in loop : " << j << '\n';  // debug
    }

    // Histo_InvMassDecadeParticles->Fill(InvMassDecadeParticles);  // debug

    double InvMassTot = 0;  // mettile nella posizione giusta dopo
    double InvMassTotSameCharge = 0;
    double InvMassTotDifferentCharge = 0;

    // loop per le masse invarianti standard
    for (int k = 0; k < DauPosition; k++) {
      for (int m = k + 1; m < DauPosition; m++) {
        InvMassTot += EventParticles[k].GetInvMass(EventParticles[m]);
        if (EventParticles[k].GetfCharge() * EventParticles[m].GetfCharge() >
            0) {
          InvMassTotSameCharge +=
              EventParticles[k].GetInvMass(EventParticles[m]);
        } else {
          InvMassTotDifferentCharge +=
              EventParticles[k].GetInvMass(EventParticles[m]);
        }
      }
    }
    Histo_InvMass->Fill(InvMassTot);
    Histo_InvMass_DifferentCharge->Fill(InvMassTotDifferentCharge);
    Histo_InvMass_SameCharge->Fill(InvMassTotSameCharge);

    double InvMassDiscordantPionKaon = 0;
    double InvMassConcordantPionKaon = 0;

    // loop per le masse invarianti con pioni e kaoni
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
              InvMassConcordantPionKaon +=
                  EventParticles[t].GetInvMass(EventParticles[u]);
            } else {
              InvMassDiscordantPionKaon +=
                  EventParticles[t].GetInvMass(EventParticles[u]);
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
              InvMassConcordantPionKaon +=
                  EventParticles[t].GetInvMass(EventParticles[u]);
            } else {
              InvMassDiscordantPionKaon +=
                  EventParticles[t].GetInvMass(EventParticles[u]);
            }
          }
        }
      }
    };

    Histo_InvMassDiscordantPionKaon->Fill(InvMassDiscordantPionKaon);
    Histo_InvMassConcordantPionKaon->Fill(InvMassConcordantPionKaon);

    for (int y = 101; y < DauPosition; y += 2) {
      double InvMassDecadeParticles2 = EventParticles[DauPosition].GetInvMass(
          EventParticles[DauPosition + 1]);
      /*
            std::cout << "InvMassDecadeParticles of positions " << y - 1 << "
         and "
                      << y << " is " << InvMassDecadeParticles << '\n';
      */
      Histo_InvMassDecadeParticles2->Fill(InvMassDecadeParticles2);
    }
  };

  gStyle->SetOptStat(112210);

  TFile *Histo_File = new TFile("./ROOT_Files/Histo_File.root", "RECREATE");

  Histo_Types->Write();
  Histo_Phi_Angles->Write();
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

  Histo_InvMassDecadeParticles2->Write();  //debug

  Histo_File->Close();

  std::cout << "BENCHMARK INSIDE LOOP (Mean and RMS should be 0.89166): \n";
  std::cout << "Mean : " << Histo_InvMassDecadeParticles->GetMean() << '\n';
  std::cout << "RMS : " << Histo_InvMassDecadeParticles->GetRMS() << '\n';

  std::cout << "BENCHMARK OUTSIDE LOOP (Mean and RMS should be 0.89166): \n";
  std::cout << "Mean : " << Histo_InvMassDecadeParticles->GetMean() << '\n';
  std::cout << "RMS : " << Histo_InvMassDecadeParticles->GetRMS() << '\n';
}