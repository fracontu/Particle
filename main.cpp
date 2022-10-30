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
      new TH1F("Invariant Mass Same Charge", "Invariant Mass Same Charge", 100, 1000, 2500);
  Histo_InvMass_SameCharge->Sumw2();
  TH1F *Histo_InvMass_DifferentCharge =
      new TH1F("Invariant Mass Different Charge", "Invariant Mass Different Charge", 100, 1000, 3000);
  Histo_InvMass_DifferentCharge->Sumw2();

  /* Questo loop dovrebbe essere da 1E5, per ora lo faccio da meno per
   * velocizzare la compilazione*/

  for (int j = 0; j < 1E5; j++) {  // metti 10 fa 1E5

    int DauPosition = 100;

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
        EventParticles[i].SetParticle("K*");

        // Quella che dopo decade la metto negli istogrammi?
        // Histo_Types->Fill(6.5);
        // Histo_Energy->Fill(EventParticles[i].GetEnergy());

        double ran2 = gRandom->Rndm();

        if (ran2 < 0.5) {
          ++DauPosition;
          EventParticles[DauPosition].SetParticle("Pion+");
          Histo_Types->Fill(0.5);
          Histo_Energy->Fill(EventParticles[DauPosition]
                                 .GetEnergy());  // forse conviene accedere con
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
                                     EventParticles[DauPosition]);
      }  // Non metto un caso default, vero? Perché tanto le particelle sono già
         // generate
    };

    double InvMassTot = 0;  // mettile nella posizione giusta dopo
    double InvMassTotSameCharge = 0;
    double InvMassTotDifferentCharge = 0;

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

  }

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

  Histo_File->Close();
}

int ProvaLab1() {
  ////////////////////////////
  //  CODICE DI PROVA LAB 1 //
  ////////////////////////////

  /*
  ParticleType p("Neutron", -27, 0);
  ResonanceType r("Neutron", -27, 0, 0);

  ParticleType *a[2];
  a[0] = new ParticleType("Neutron", -27, 0);
  a[1] = new ResonanceType("Neutron", -27, 0, 0);
  for (ParticleType *particle : a) {
    // particle->Print();
  };

  const ParticleType p2(
      "Neutron", 4,
      5);  // per vedere se funzionano i const. Cosa altro devo fare?
  // std::cout << "- const test:\n";

  const char *name = p2.GetfName();  // il const è obbligatorio
  double mass = p2.GetfMass();
  int charge = p2.GetfCharge();
*/
  /*
  std::cout << "Name: " << name << '\n';
  std::cout << "Mass: " << mass << '\n';
  std::cout << "Charge: " << charge << '\n';
  */

  // const ParticleType p3(p2);
  // const ResonanceType r2(r);
  //  Applico a queste due istanze tutti i metodi per vedere se funzionano.
  //  Funzionano quindi le commento che danno warning
  /*
  p3.GetfCharge();
  p3.GetfMass();
  p3.GetfName();
  p3.GetWidth();
  p3.Print();
  r2.GetfCharge();
  r2.GetfMass();
  r2.GetfName();
  r2.GetWidth();
  r2.Print();
  */
  /*
   Particle::AddParticleType("Neutron", -27, 0, 0);
   Particle::AddParticleType("Electron", -31, -1.6, 0);
   Particle::AddParticleType("Proton", -31, +1.6, 0);

   Particle::AddParticleType("Mela", -31, -1.6, 0);
   Particle::AddParticleType("Pera", -31, -1.6, 0);
   Particle::AddParticleType("Frutta", -31, -1.6, 0);

   Particle::AddParticleType("Melone", -31, -1.6, 0);
   Particle::AddParticleType("Cocomero", -31, -1.6, 0);
   Particle::AddParticleType("Prugna", -31, -1.6, 0);
   Particle::AddParticleType("Pesca", -31, -1.6, 0);

   Particle::AddParticleType("Quella di troppo", -31, -1.6, 0);
   */
  /*
  std::cout << Particle::FindParticle("Proton") << '\n';
  std::cout << Particle::FindParticle("Neutron") << '\n';
  std::cout << Particle::FindParticle("Banana") << '\n';
  */
  // Particle neutron("Neutron", 1, 1, 1);
  //  Particle banana("Banana", 1, 1, 1);
  //  Particle::AddParticleType("Electron", -31, -1.6, 0);
  /*
  std::cout << Particle::FindParticle("Electron") << '\n';
  std::cout << Particle::FindParticle("Cocomero") << '\n';
  std::cout << Particle::FindParticle("Quella di troppo") << '\n';
  */

  /////////////////////////////////
  //         CODICE LAB2         //
  /////////////////////////////////

  // Provo a fare anche la compilazione da terminale?
  return 0;
};