#!/usr/bin/env python
# -*- coding: utf-8 -*-


try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

from os.path import join, dirname


from xix-event-mib.config import NAME, VERSION, LICENSE

readme = open(join(dirname(__file__), 'README.rst')).read()
history = open('HISTORY.rst').read().replace('.. :changelog:', '')

requirements = [
    # 'package1', 'package2'
    
]

test_requirements = [
    # 'package1', 'package2'
]

setup(
    name=NAME,
    version=VERSION,
    description='Python interface to XIX-EVENT-MIB.',
    long_description=readme + '\n\n' + history,
    author='Markus Juenemann',
    author_email='markus@juenemann.net',
    url='https://github.com/mjuenema/xix-event-mib',
    packages=[
        'xix-event-mib',
    ],
    package_dir={'xix-event-mib':
                 'xix-event-mib'},
    include_package_data=True,
    install_requires=requirements,
    license=LICENSE,
    zip_safe=False,

    keywords='xix-event-mib',
    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: BSD License',
        'Natural Language :: English',
        "Programming Language :: Python :: 2",
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
    ],
    test_suite='tests',
    tests_require=test_requirements
)


# References
#
# - https://pythonhosted.org/setuptools/index.html
# - http://foobar.lu/wp/2012/05/13/a-comprehensive-step-through-python-packaging-a-k-a-setup-scripts/
