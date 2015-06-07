#ifndef __RAT_ReacIBDgen__
#define __RAT_ReacIBDgen__

#include <RAT/LinearInterp.hh>
#include <CLHEP/Random/Randomize.h>
#include <G4ThreeVector.hh>
#include <G4LorentzVector.hh>

namespace RAT {

// Generate inverse beta decay event
class ReacIBDgen {
public:
  ReacIBDgen();
  
  // Generate random event vectors
  //    Pass in the neutrino direction (unit vector)
  //    Returns 4-momentum vectors for neutrino and resulting positron
  //    and neutron.  Neutrino energy and positron direction drawn from
  //    GenInteraction() distribution.
  void GenEvent(const G4ThreeVector &nu_dir,
		G4LorentzVector &neutrino,
		G4LorentzVector &positron,
		G4LorentzVector &neutron);

  // Generate random inverse beta decay interaction
  //
  //   Selects neutrino energy and cos(theta) of the produced
  //   positron relative to neutrino direction.  They are pulled
  //   from 2D distribution of reactor neutrinos which have interacted
  //   with a proton, so both the incident flux, and the (relative) 
  //   differential cross-section are factored in.
  void GenInteraction(float &E, float &CosThetaLab);

  // Total cross section for inverse beta decay
  static double CrossSection(float x);

  //Creates a probability density spectrum using the sum of the different
  //reactor neutrino probability density spectrums as a function of energy.
  //The function returns a random energy from the PDF based on the weighted
  //probabilities.  This function uses the same method as the CfSource file
  //to produce a random generator based on a probability density function.
  float GetNuEnergy();

  //Probability density functions of reactor neutrinos as a function of 
  //energy.  Parametrization of fluxes for neutrinos from each reactor
  //core isotope from "Determination of the Neutrino Mass Hierarchy at
  //Intermediate Baseline", arxiv:0807.3203v2

  //FIXME: Make the leading coefficients of these spectrums adjustable in
  //the macro file that will call this generator.
  float U235ReacSpectrum(const float& x);
  float Pu239ReacSpectrum(const float& x);
  float U238ReacSpectrum(const float& x);
  float Pu241ReacSpectrum(const float& x);

  //Sum of the reactor spectrums defined above.  the x value in this case is
  //the energy of the neutrino, and the function would return the value of the
  //PDF at that energy.
  float NuReacSpectrum(const float& x);

  //IBDEnergy which is a product of the above spectrums, the cross-section, and a
  //square root factor with the cross section and electron mass.
  double IBDESpectrum(float x);

protected:
  double Emax;
  double Emin;
  double U238Amp;
  double U235Amp;
  double Pu239Amp;
  double Pu241Amp;
};


} // namespace RAT

#endif
