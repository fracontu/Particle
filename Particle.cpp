#include "Particle.hpp"

#include <cmath>    // for M_PI
#include <cstdlib>  //for RAND_MAX
#include <cstring>
#include <iostream>

int Particle::fNParticleType = 0;

Particle::Particle(const char* name, const double px = 0, const double py = 0,
                   const double pz = 0)
    : impulse{px, py, pz}, fIndex{FindParticle(name)} {
  if (fIndex < 0) {
    std::cout << "This particle doesn't exists! ( " << name << " ).\n";
  }
}

Particle::Particle() : impulse{0., 0., 0.}, fIndex{0} {}  // fIndex va bene così

ParticleType* Particle::fParticleType[Particle::fMaxNumParticleType];

int Particle::FindParticle(const char* NameParticle) {
  for (int i = 0; i < fNParticleType; i++) {
    if (std::strcmp(fParticleType[i]->GetfName(), NameParticle) == 0) return i;
  }
  return -1;
};

int Particle::GetfIndex() const { return fIndex; };

void Particle::AddParticleType(
    const char* name, const double mass, const int charge,
    const double width) {  // su stack ho visto che non devo mettere il default
                           // di width, perché?
  ParticleType* p;
  ResonanceType* r;

  // Sistema il modo in cui agiscono questi if

  if (fNParticleType < 10 &&
      FindParticle(name) < 0) {  // Perché non posso usare this?
    if (width == 0) {
      p = new ParticleType{name, mass, charge};
      fParticleType[fNParticleType] = p;
    } else {
      r = new ResonanceType{name, mass, charge, width};
      fParticleType[fNParticleType] = r;
    }
    ++fNParticleType;

  } else if (fNParticleType > 9) {
    std::cout << "Too many particle types!\n";
  } else if (FindParticle(name) >= 0) {
    std::cout << "This particle already exists! ( " << name << " ).\n";
  } else
    std::cout << "Can't create this particle type!\n";
};

void Particle::SetParticle(const char* name) {
  if (FindParticle(name) > -1) {
    fIndex = FindParticle(name);
  } else
    std::cout << "Can't find the particle you want to set. (" << name << " )"
              << '\n';
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
  for (int i = 0; i <= fNParticleType; i++) {
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
double Particle::GetEnergy() const {
  double mass = fParticleType[fIndex]->GetfMass();
  double p = GetImpulseModule();
  return std::sqrt(mass * mass + p * p);
};
Impulse Particle::GetImpulse() const { return impulse; }

double Particle::GetInvMass(Particle& p) const {
  double ETot = GetEnergy() + p.GetEnergy();  // E1 + E2
  double px_tot = impulse.px_ + p.GetImpulse().px_;
  double py_tot = impulse.py_ + p.GetImpulse().py_;
  double pz_tot = impulse.pz_ + p.GetImpulse().pz_;
  double P2 = px_tot * px_tot + py_tot * py_tot + pz_tot * pz_tot;
  return std::sqrt(ETot * ETot - P2);
}

void Particle::SetP(double px, double py, double pz) {
  impulse.px_ = px;
  impulse.py_ = py;
  impulse.pz_ = pz;
}

int Particle::Decay2body(Particle& dau1, Particle& dau2) const {
  if (GetMass() == 0.0) {
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if (fIndex > -1) {  // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += fParticleType[fIndex]->GetWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    printf(
        "Decayment cannot be preformed because mass is too low in this "
        "channel\n");
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy = sqrt(impulse.px_ * impulse.px_ + impulse.py_ * impulse.py_ +
                       impulse.pz_ * impulse.pz_ + massMot * massMot);

  double bx = impulse.px_ / energy;
  double by = impulse.py_ / energy;
  double bz = impulse.pz_ / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz) {
  double energy = GetEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * impulse.px_ + by * impulse.py_ + bz * impulse.pz_;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  impulse.px_ += gamma2 * bp * bx + gamma * bx * energy;
  impulse.py_ += gamma2 * bp * by + gamma * by * energy;
  impulse.pz_ += gamma2 * bp * bz + gamma * bz * energy;
}

double Particle::GetImpulseModule() const {
  return std::sqrt(impulse.px_ * impulse.px_ + impulse.py_ * impulse.py_ +
                   impulse.pz_ * impulse.pz_);
}

double Particle::GetTransverseImpulseModule() const {
  return std::sqrt(impulse.px_ * impulse.px_ + impulse.py_ * impulse.py_);
}

double Particle::GetfCharge() const {
  return fParticleType[fIndex]->GetfCharge();
}