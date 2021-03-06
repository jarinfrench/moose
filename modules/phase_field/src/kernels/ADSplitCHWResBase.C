//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADSplitCHWResBase.h"

defineADValidParams(
    ADSplitCHWResBase,
    ADKernelGrad,
    params.addClassDescription(
        "Split formulation Cahn-Hilliard Kernel for the chemical potential variable");
    params.addParam<MaterialPropertyName>("mob_name",
                                          "mobtemp",
                                          "The mobility used with the kernel"););
