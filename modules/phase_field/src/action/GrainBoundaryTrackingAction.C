//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* hhtps://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "GrainBoundaryTrackingAction.h"

// MOOSE includes
#include "AddPostprocessorAction.h"
#include "FEProblem.h"

//#include "libmesh/string_to_enum.h"

registerMooseAction("PhaseFieldApp", GrainBoundaryTrackingAction, "add_postprocessor");

template <>
InputParameters
validParams<GrainBoundaryTrackingAction>()
{
  InputParameters params = validParams<Action>();
  params.addClassDescription(
    "Set up the postprocessors for grain boundary tracking in a grain growth simulation");
  params.addRequiredParam<unsigned int>("op_num",
                                        "specifies the number of order parameters to create");
  params.addRequiredParam<std::string>("var_name_base", "specifies the base name of the variables");
  
  return params;
}

GrainBoundaryTrackingAction::GrainBoundaryTrackingAction(const InputParameters & params)
  : Action(params),
    _op_num(getParam<unsigned int>("op_num")),
    _var_name_base(getParam<std::string>("var_name_base"))
{
}

void GrainBoundaryTrackingAction::act()
{
  // Loop over order parameters TODO: This should be over grain num, but I'm not sure if that will work yet.
  for (unsigned int op = 0; op < _op_num - 1; ++op)
  {
    InputParameters params = validParams<Action>();
    // Create the postprocessor name
    std::string pp_name = _var_name_base + Moose::stringify(op) + _var_name_base + Moose::stringify(op + 1);
    
    // Create the coupled variables
    std::string vars = _var_name_base + Moose::stringify(op) + " " + _var_name_base + Moose::stringify(op + 1);
    
    // Specify the grain variables in params
    params.set<std::string>("v") = vars;
    
    // Add postprocessor
    if (_current_task == "add_postprocessor")
    {
      _problem->addPostprocessor("GrainBoundaryArea", pp_name, params);
    }
  }
}