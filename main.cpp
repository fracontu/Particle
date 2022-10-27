#include <iostream>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int main() {
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

  /*
  std::cout << "Name: " << name << '\n';
  std::cout << "Mass: " << mass << '\n';
  std::cout << "Charge: " << charge << '\n';
  */

  const ParticleType p3(p2);
  const ResonanceType r2(r);
  // Applico a queste due istanze tutti i metodi per vedere se funzionano.
  // Funzionano quindi le commento che danno warning
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
  /*
  std::cout << Particle::FindParticle("Proton") << '\n';
  std::cout << Particle::FindParticle("Neutron") << '\n';
  std::cout << Particle::FindParticle("Banana") << '\n';
  */
  Particle neutron("Neutron", 1, 1, 1);
  // Particle banana("Banana", 1, 1, 1);
  // Particle::AddParticleType("Electron", -31, -1.6, 0);
  /*
  std::cout << Particle::FindParticle("Electron") << '\n';
  std::cout << Particle::FindParticle("Cocomero") << '\n';
  std::cout << Particle::FindParticle("Quella di troppo") << '\n';
  */
}