//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "RandomBoundaryAnisotropyProvider.h"
#include "GrainTrackerInterface"
#include "MultiMooseEnum.h"
#include "MathUtils.h"

registerMooseObject("PhaseFieldApp", RandomBoundaryAnisotropyProvider);

template <>
InputParameters
validParams<RandomBoundaryAnisotropyProvider>()
{
  InputParameters params = validParams<RandomBoundaryAnisotropyProvider>();
  MultiMooseEnum anisotropies("e=0 m=1 q=2", "e");
  params.addClassDescription("Assign anisotropic boundary properties to a polycrystalline system");
  params.addRequiredParam<UserObjectName>("grain_tracker_object",
                                          "The FeatureFloodCount UserObject to get values from");
  params.addParam<Real>("iso_energy", <value for copper>,
                        "Isotropic grain boundary energy that will be assigned to all boundaries");
  params.addParam<Real>("iso_mobility", <value for copper>,
                        "Isotropic grain boundary mobility that will be assigned to all boundaries");
  params.addParam<Real>("iso_q", <value for copper>,
                        "Isotropic activation energy that will be assigned to all boundaries");
  params.addParam<unsigned int>("seed", 0, "Seed value for the random number generator");
  params.addRangeCheckedParam<Real>("fraction", 0.0, "fraction>=0 & fraction<=1",
                                    "The fraction of boundaries that will be assigned anisotropic values");
  params.addParam<unsigned int>("n", "The number of boundaries to assign anisotropic properties to");
  params.addParam<MultiMooseEnum>("anisotropies", anisotropies, "The boundary properties that will be made anisotropic");
  params.addParam<Real>("aniso_energy", "The anisotropic grain boundary energy that will be assigned to the anisotropic boundaries");
  params.addParam<Real>("aniso_mobility", "The anisotropic grain boundary mobility that will be assigned to the anisotropic boundaries");
  params.addParam<Real>("aniso_q", "The anisotropic activation energy that will be assigned to the anisotropic boundaries");

  return params;
}

RandomBoundaryAnisotropyProvider::RandomBoundaryAnisotropyProvider(const InputParameters & params)
  : _grain_tracker(getUserObject<GrainTrackerInterface>("grain_tracker_object")),
    _iso_energy(getParam<Real>("iso_energy")),
    _iso_mobility(getParam<Real>("iso_mobility")),
    _iso_q(getParam<Real>("iso_q")),
    _seed(getParam<unsigned int>("seed")),
    _fraction(getParam<Real>("fraction")),
    _anisotropies(getParam<MultiMooseEnum>("anisotropies")),
    _aniso_energy(getParam<Real>("aniso_energy")),
    _aniso_mobility(getParam<Real>("aniso_mobility")),
    _aniso_q(getParam<Real>("aniso_q"))
{
  _random.seed(0, getParam<unsigned int>("seed"));
}

void RandomBoundaryAnisotropyProvider::initialize()
{
  std::vector<std::pair<unsigned int, unsigned int> > matrix_positions;
  auto grain_num = _grain_tracker.getTotalFeatureCount();
  for (unsigned int i = 0; i < grain_num - 1; ++i)
  {
    for (unsigned int j = i + 1; j < grain_num; ++j)
    {
      matrix_positions.push_back(std::make_pair(i,j));
    }
  }

  if (isParamSetByUser("n"))
  {
    _n = getParam<unsigned int>("n");
  }
  else
  {
    _n = MathUtils::round(_fraction * grain_num);
  }

  if (_n < 1)
  {
    mooseError("The number of grains to assign anisotropic values to must be >= 1");
  }

  if (_n == grain_num) // All values are changed from isotropic values
  {
    for (const auto & anisotropy : _anisotropies)
    {
      auto aniso_id = anisotropy.id();

      switch (aniso_id)
      {
        case 0: // energy
          //  function call with energy values
          break;
        case 1: // mobility
          // function call with mobility values
          break;
        case 2: // activation energy
          // function call with activation energy values
          break;
        default:
          mooseError("Unknown anisotropy type ", aniso_id);
      }
      // do something here to specify the boundary properties - probably a function call
    }
  }

  // Will need something to actually give the values outside of the class... right?  see RandomEulerAngleProvider

  // Is there a way the user can specify which boundaries they want to mark as anisotropic?  addParam<std::string>("vars", "The list of boundaries that are marked as anisotropic")?

}
