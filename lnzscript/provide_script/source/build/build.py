import sys

sys.path.append('..')
import os

os.chdir('..')

from distutils.core import setup
import py2exe

main_script = 'main.py'

sys.argv.append('py2exe')

setup(
	options={
		"py2exe": {
			"compressed": 1,
			"optimize": 2,
			"ascii": 1,
			'excludes': [],
		}
	},
	zipfile=None,
	console=[main_script],
	py_modules=[
		'urllib_wrapper',
		'zipfile_wrapper',
		'ftplib_wrapper',
	],
	author='Ben Fisher'
)
