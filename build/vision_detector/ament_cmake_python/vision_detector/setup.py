from setuptools import find_packages
from setuptools import setup

setup(
    name='vision_detector',
    version='0.0.0',
    packages=find_packages(
        include=('vision_detector', 'vision_detector.*')),
)
