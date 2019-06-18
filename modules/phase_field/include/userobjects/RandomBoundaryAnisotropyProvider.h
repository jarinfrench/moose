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

  virtual unsigned int getGrainNum() const override;

protected:
  const GrainTrackerInterface & _grain_tracker;
  std::vector<std::vector<Real> > _energies, _mobilities, _qs;

  MooseRandom _random;
}
