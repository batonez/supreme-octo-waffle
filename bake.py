import os
import importlib.util
bakerModuleSpec = importlib.util.spec_from_file_location("baker", os.path.join(os.environ['HATCHERY_SOURCES'], 'baker', 'baker.py'))
baker = importlib.util.module_from_spec(bakerModuleSpec)
bakerModuleSpec.loader.exec_module(baker)

######################## Dependencies
baker.compileDependencies = [
os.path.join(os.environ['HATCHERY_SOURCES'], 'glade'),
os.path.join(os.environ['HATCHERY_VENDOR'], 'lodepng'),
]

######################## Compiler
baker.compilerOutputDir = os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'obj')

baker.compilerIncludes.extend([
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld'  , 'include'), #wtf
os.path.join(os.environ['HATCHERY_SOURCES'], 'glade' , 'include'), # public includes should be copied to dist and used from there
os.path.join(os.environ['HATCHERY_VENDOR']  , 'OpenGL' , 'include'),
os.path.join(os.environ['HATCHERY_VENDOR'], 'sha1'),
])

baker.compilerSources = [
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'states', 'Play.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Collectable.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'blocks', 'Terrain.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'ResourceManager.cpp'),
os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'src', 'main.cpp'),
os.path.join(os.environ['HATCHERY_VENDOR'], 'sha1',  'sha1.cpp'), # create separate bake file for that
]

######################## Linker
baker.linkerOutputFilename = os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'game.exe')

baker.linkerLibPath.extend([
os.path.join(os.environ['HATCHERY_VENDOR'], 'freetype-windows-binaries', 'win64')
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
# FIXME copy freetype.dll
baker.copyDir(os.path.join(os.environ['HATCHERY_SOURCES'], 'thatworld', 'assets'), os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'assets'))
baker.copyDir(os.path.join(os.environ['HATCHERY_SOURCES'], 'glade', 'res'), os.path.join(os.environ['HATCHERY_BUILDS'], 'thatworld', 'assets'))
