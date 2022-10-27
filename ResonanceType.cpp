#include "ResonanceType.hpp"

#include <iostream>  //va bene includerle qui o è meglio negli hpp?

ResonanceType::ResonanceType(const char *name, const double mass,
                             const int charge, const double width)
    : ParticleType(name, mass, charge), fWidth{width} {};
double ResonanceType::GetWidth() const { return fWidth; };
void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "Resonance width : " << fWidth << '\n';
}