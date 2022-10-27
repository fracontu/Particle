#include "Particle.hpp"

#include <cmath>
#include <iostream>

int Particle::fNParticleType = 0;

Particle::Particle(const char* name, const double px = 0, const double py = 0,
                   const double pz = 0)
    : impulse{px, py, pz}, fIndex{FindParticle(name)} {}

ParticleType* Particle::fParticleType[Particle::fMaxNumParticleType];

int Particle::FindParticle(const char* NameParticle) {
  for (int i = 0; i < fNParticleType; i++) {
    if (fParticleType[i]->GetfName() == NameParticle) return i;
  }

  std::cout << "Can't find your particle.\n";
  return -1;
};

int Particle::GetfIndex() const { return fIndex; };

Particle part{"name"};

void Particle::AddParticleType(
    const char* name, const double mass, const int charge,
    const double width) {  // su stack ho visto che non devo mettere il default
                           // di width, perché?
  ParticleType* p;
  ResonanceType* r;
  if (fNParticleType <= 10 &&
      FindParticle(name) < 0) {  // Perché non posso usare this?
    if (width == 0) {
      p = new ParticleType{name, mass, charge};
      fParticleType[fNParticleType] = p;
    } else {
      r = new ResonanceType{name, mass, charge, width};
      fParticleType[fNParticleType] = r;
    }

  } else
    std::cout << "Too many particle types.";
};

void Particle::SetParticle(const char* name) {
  if (FindParticle(name) > -1) {
    fIndex = FindParticle(name);
  } else
    std::cout << "Can't find this particle.\n";
}

void Particle::SetParticle(const int index) {
  if (index < 11 && index > -1)  // metti if con ?
  {
    fIndex = index;
  }
  std::cout << "This index doesn't exists.\n";
}

void Particle::PrintTypes() const {
  std::cout << "Content of array:\n";
  for (int i = 0; i < fNParticleType; i++) {
    fParticleType[i]->Print();
  }
  std::cout << '\n';
}

void Particle::PrintParticle() const {
  std::cout << "This particle is:\n";
  std::cout << "Index: " << fIndex << '\n';
  std::cout << "Name: " << fParticleType[fIndex]->GetfName() << '\n';
  std::cout << "Impulse: ( " << impulse.px_ << " , " << impulse.py_ << " , "
            << impulse.pz_ << " )\n";
  std::cout << '\n';
}

double Particle::GetPx() const { return impulse.px_; }
double Particle::GetPy() const { return impulse.py_; }
double Particle::GetPz() const { return impulse.pz_; }
double Particle::GetMass() const { return fParticleType[fIndex]->GetfMass(); }
double Particle::GetETot() const {
  double mass = fParticleType[fIndex]->GetfMass();
  double p = std::sqrt(impulse.px_ * impulse.px_ + impulse.py_ * impulse.py_ +
                       impulse.pz_ * impulse.pz_);
  double ETot = std::sqrt(mass * mass + p * p);
  return ETot;
};
Impulse Particle::GetImpulse() const { return impulse; }

double Particle::GetInvMass(Particle& p) const {
  double ETot = GetETot() + p.GetETot();  // E1 + E2
  double p1 = std::sqrt(impulse.px_ * impulse.px_ + impulse.py_ * impulse.py_ +
                        impulse.pz_ * impulse.pz_);
  double p2 = std::sqrt(p.GetImpulse().px_ * p.GetImpulse().px_ +
                        p.GetImpulse().py_ * p.GetImpulse().py_ +
                        p.GetImpulse().pz_ * p.GetImpulse().pz_);
  double PTot = p1 + p2;
  return std::sqrt(ETot * ETot - PTot * PTot);
}

void Particle::SetP(double px, double py, double pz) {
  impulse.px_ = px;
  impulse.py_ = py;
  impulse.pz_ = pz;
}