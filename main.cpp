#include <iostream>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int main() {
  // cambia tutto con new
  char *neutron = (char *)"Neutron";  // Va bene togliere così il warning?
  ParticleType p(neutron, 10, 5);
  ResonanceType r(neutron, 3, 6, 8);

  ParticleType *a[2];
  a[0] = new ParticleType(neutron, 10, 5);
  a[1] = new ResonanceType(neutron, 3, 6, 8);
  for (ParticleType *particle : a) {
    particle->Print();
  };

  const ParticleType p2(
      neutron, 4,
      5);  // per vedere se funzionano i const. Cosa altro devo fare?
  std::cout << "- const test:\n";
  const char *name = p2.GetfName();  // il const è obbligatorio
  double mass = p2.GetfMass();
  int charge = p2.GetfCharge();
  std::cout << "Name: " << name << '\n';
  std::cout << "Mass: " << mass << '\n';
  std::cout << "Charge: " << charge << '\n';

  std::cout << "ciao!\n";
}