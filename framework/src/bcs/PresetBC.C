//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PresetBC.h"

registerMooseObject("MooseApp", PresetBC);

defineLegacyParams(PresetBC);

InputParameters
PresetBC::validParams()
{
  InputParameters params = NodalBC::validParams();
  params.addRequiredParam<Real>("value", "Value of the BC");
  params.declareControllable("value");
  params.addClassDescription(
      "Similar to DirichletBC except the value is applied before the solve begins");
  return params;
}

PresetBC::PresetBC(const InputParameters & parameters)
  : PresetNodalBC(parameters), _value(getParam<Real>("value"))
{
}

Real
PresetBC::computeQpValue()
{
  return _value;
}
