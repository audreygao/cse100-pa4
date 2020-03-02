subdir('ActorGraph')
subdir('Map')

pathfinder_exe = executable('pathfinder.executable', 
    sources: ['pathfinder.cpp'],
    dependencies: [actorgraph_dep],
    install : true)

map_exe = executable('map.executable', 
    sources: ['map.cpp'],
    dependencies: [map_dep, cxxopts_dep],
    install : true)

linkpredictor_exe = executable('linkpredictor.executable', 
    sources: ['linkpredictor.cpp'],
    dependencies: [actorgraph_dep],
    install : true)
