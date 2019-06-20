//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MooseRandom.h"

// Fordward declaration
class RandomBoundaryAnisotropyProvider;
class GrainTrackerInterface;

template <>
InputParameters validParams<RandomBoundaryAnisotropyProvider>();

/**
 * Assign anisotropic boundary properties to random grains
 */
class RandomBoundaryAnisotropyProvider
{
public:
  RandomBoundaryAnisotropyProvider(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override {}
  virtual void finalize() override {}
  
  // Function to change the values of the passed in matrix.
  void changeValues(std::vector<std::vector<Real> > &,
                    const std::vector<std::pair<unsigned int, unsigned int> > &,
                    const Real &)
  
  virtual const std::vector<std::vector<Real> > & getProperties(unsigned int, unsigned int) const override;

protected:
  const GrainTrackerInterface & _grain_tracker;
  std::vector<std::vector<Real> > _energies, _mobilities, _qs;
  
  /// Isotropic values
  Real _iso_energy, _iso_mobility, _iso_q;
  
  /// Anisotropic values
  Real _aniso_energy, _aniso_mobility, _aniso_q;
  
  unsigned int _seed; // random number generator seed
  unsigned int _n; // number of grain boundaries to change properties of
  
  Real _fraction; // fraction of grain boundaries to change properties of
  
  MultiMooseEnum _anisotropies; // The properties to assign anisotropic values to
}
