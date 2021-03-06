[Mesh]
  file = simplest_contact_skew.e
[]

[GlobalParams]
  volumetric_locking_correction = false
  displacements = 'disp_x disp_y'
[]

[AuxVariables]
  [./penetration]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Modules/TensorMechanics/Master]
  [./all]
    add_variables = true
    strain = FINITE
  []
[]

[AuxKernels]
  [./penetration]
    type = PenetrationAux
    variable = penetration
    boundary = 2
    paired_boundary = 3
  [../]
[]

[Constraints]
  [./contact_x]
    type = MultiDContactConstraint
    variable = disp_x
    master_variable = disp_x
    component = 0
    slave = 2
    master = 3
    penalty = 1e6
  [../]

  [./contact_y]
    type = MultiDContactConstraint
    variable = disp_y
    master_variable = disp_y
    component = 1
    slave = 2
    master = 3
    penalty = 1e6
  [../]
[]

[BCs]
  [./left_x]
    type = DirichletBC
    variable = disp_x
    boundary = 1
    value = 0.0
  [../]

  [./left_y]
    type = DirichletBC
    variable = disp_y
    boundary = 1
    value = 0.0
  [../]

  [./right_x]
    type = PresetBC
    variable = disp_x
    boundary = 4
    value = -0.0001
  [../]

  [./right_y]
    type = PresetBC
    variable = disp_y
    boundary = 4
    value = 0.0
  [../]
[]

[Materials]
  [./stiffStuff1]
    type = ComputeIsotropicElasticityTensor
    block = '1'
    youngs_modulus = 1e6
    poissons_ratio = 0.3
  [../]
  [./stiffStuff1_stress]
    type = ComputeFiniteStrainElasticStress
    block = '1'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'

  #petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  #petsc_options_value = 'hypre    boomeramg      101'
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'

  line_search = 'none'

  nl_abs_tol = 1e-8

  l_max_its = 100
  nl_max_its = 10
  dt = 1.0
  num_steps = 1
[]

[Outputs]
  [./out]
    type = Exodus
    elemental_as_nodal = true
  [../]
[]
