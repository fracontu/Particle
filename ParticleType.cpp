#include "ParticleType.hpp"

#include <iostream>

ParticleType::ParticleType(const char *name, const double mass,
                           const int charge)
    : fName{name}, fMass{mass}, fCharge{charge} {};  // per le cose const, ci va
                                                     // il const al costruttore?
const char *ParticleType::GetfName() const {
  return fName;
}; 
double ParticleType::GetfMass() const { return fMass; };
int ParticleType::GetfCharge() const { return fCharge; };
void ParticleType::Print() const {
  std::cout << "This particle is:\n";
  std::cout << "Name            : " << fName << '\n';
  std::cout << "Mass            : " << fMass << '\n';
  std::cout << "Charge          : " << fCharge << '\n';
};

double ParticleType::GetWidth() const { return 0.; }