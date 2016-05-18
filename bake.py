import os
import baker

######################## Dependencies
baker.compileDependencies = [
os.path.join(os.environ['HATCHERY_SOURCES'], 'glade'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'lodepng'),
]

######################## Compiler
baker.compilerOutputDir = os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'obj')

baker.compilerIncludes.extend([
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld'  , 'include'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'glade' , 'include'),
os.path.join(os.environ['HATCHERY_TOOLS']  , 'OpenGL' , 'include'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'sha1'),
])

baker.compilerSources = [
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'ResourceManager.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'Area.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'states', 'Play.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Terrain.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Collectable.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Gold.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Block.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Character.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Player.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'main.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'sha1',  'sha1.cpp'),
]

######################## Linker
baker.linkerOutputFilename = os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'game.exe')

baker.linkerLibPath.extend([
os.path.join(os.environ['HATCHERY_BUILDS'], 'freetype-2.5.5')
])

baker.linkerObjects = [
'kernel32.lib',
'user32.lib',
'gdi32.lib',
'Opengl32.lib',
'DbgHelp.lib',
'freetype.lib',
os.path.join(os.environ['HATCHERY_BUILDS'], 'glade', '*.obj'),
os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'obj', '*.obj'),
os.path.join(os.environ['HATCHERY_BUILDS'], 'lodepng', '*.obj'),
]

######################## Run
baker.parseCommandLine()
baker.sanitizeBakeInput()
baker.compile()
baker.linkExe()

######################## Copy FIXME baker copy function should copy file-by-file
baker.copyDir(os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'assets'), os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'assets'))
baker.copyDir(os.path.join(os.environ['HATCHERY_SOURCES'], 'glade', 'res'), os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'assets'))
