from setuptools import find_packages
from setuptools import setup

setup(
    name='camera_stream',
    version='0.0.0',
    packages=find_packages(
        include=('camera_stream', 'camera_stream.*')),
)
