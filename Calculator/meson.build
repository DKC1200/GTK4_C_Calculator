project('calculator', 'c')

gtk = dependency('gtk4')

executable('calculator',
  ['main.c', 'calculator_gui.c', 'calculator_logic.c'],
  dependencies: gtk,
  install: true
)