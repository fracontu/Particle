#ifndef RESONANCETYPE
#define RESONANCETYPE

#include "ParticleType.hpp"

class ResonanceType : public ParticleType {
 public:
  ResonanceType(const char *name, const double mass, const int charge,
                const double width);
  double GetWidth() const;
  void Print() const;  // devo cambiare nome o funziona l'overload?
 private:
  const double fWidth;
};

#endif