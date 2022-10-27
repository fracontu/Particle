#ifndef PARTICLETYPE
#define PARTICLETYPE

class ParticleType {
 public:
  ParticleType( const char *name, double mass,
               int charge);  // motiva questi const
  const char *GetfName() const;
  double GetfMass() const;
  int GetfCharge() const;
  virtual void Print() const;
  virtual double GetWidth() const;

 private:
  const char *fName;
  const double fMass;
  const int fCharge;
};

#endif