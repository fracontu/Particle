#ifndef PARTICLE
#define PARTICLE

#include <algorithm>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

struct Impulse {
  double px_;
  double py_;
  double pz_;
};

class Particle {
 public:
  Particle(const char* name, const double px, const double py, const double pz);
  int GetfIndex() const;
  static void AddParticleType(const char* name, const double mass,
                              const int charge, const double width = 0);

  void SetParticle(const char* name);
  void SetParticle(const int index);
  void SetP(double px, double py, double pz);

  void PrintTypes()
      const;  // Non può essere statico perché le particelle nascono al runtime
  void PrintParticle() const;

  double GetPx() const;
  double GetPy() const;
  double GetPz() const;
  double GetMass() const;
  double GetEnergy() const;
  double GetInvMass(Particle& p) const;
  Impulse GetImpulse() const;

  int Decay2body(Particle& dau1, Particle& dau2) const;

 private:
  static int fNParticleType;
  static const int fMaxNumParticleType = 10;
  static ParticleType* fParticleType[fMaxNumParticleType];
  Impulse impulse;

  int fIndex;
  static int FindParticle(
      const char*
          NameParticle);  // altrimenti non lo posso usare, quando scrivo altri
                          // metodi, se non ho prima istanziato altre classi

  void Boost(double bx, double by, double bz);
};

#endif