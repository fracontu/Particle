#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

#include <iostream>

void InvMass_test() {  // sembra funzionare il metodo                 // debug
  Particle::AddParticleType("1", 1, 1);  // PTot = sqrt(3), ETot = 2
  Particle::AddParticleType("2", 2, 2);  // Ptot = sqrt(12), ETot = 4
  Particle p1, p2;
  p1.SetP(1, 1, 1);
  p2.SetP(2, 2, 2);
  p1.SetParticle("1");
  p2.SetParticle("2");
  // debug
  std::cout << "p1.GetInvMass(p2) = " << p1.GetInvMass(p2)
            << " (Expected 3)\n";  // InvMass = 3
  std::cout << "p2.GetInvMass(p1) = " << p2.GetInvMass(p1)
            << " (Expected 3)\n";  // InvMass = 3 (same)

  Particle::AddParticleType("Pion+", 0.13957, 1);
  Particle::AddParticleType("Pion-", 0.13957, -1);
  Particle::AddParticleType("Kaon+", 0.49367, 1);
  Particle::AddParticleType("Kaon-", 0.49367, -1);
  Particle p3, p4;
  p3.SetParticle("Pion+");
  p3.SetP(1, 1, 1);  // PTot = sqrt(3), ETot = 1.737665...
  p4.SetParticle("Kaon-");
  p4.SetP(2, 2, 2);  // PTot = sqrt(12), ETot = 3.49910...
  std::cout << "p3.GetInvMass(p4) = " << p3.GetInvMass(p4)
            << " (Expected 0.650928)\n";  // InvMass = 0.650928
  std::cout << "p4.GetInvMass(p3) = " << p4.GetInvMass(p3)
            << " (Expected 0.650928)\n";  // InvMass = 0.650928 (same)
};

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